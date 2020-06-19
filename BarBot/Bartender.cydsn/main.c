/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>
#include "GUI.h"
#include "tft.h"
#include "drinks.h"

// Function Defintions
void create_config_rects(); // Creates and stores the rectangles for stat display on GUI
void clear_config(); // Clears the configuration menu
void display_config(); // Displays sent stats on the GUI
void draw_active_config(int new_motor, int old_motor, int color);
void draw_new_mixie(int motor, int drink_number, int color);
void redraw_config_text(char* text, int motor, int color);
void MainTask(void);
int clean_number(int num, int count);
void relay_flip(int button_num);
void change_config_color(int motor, int color);
void display_dispenser();
void push_to_list(int* list, int value, int size);
int compare_lists(int* list1, int* list2, int size);
void clean_tubing();
void create_dispenser_rects();
void update_dispenser_text();
void prime_pump(int motor);
void relay_on(int motor);
void relay_off(int motor);
void generate_menu();
int check_availability(Drink* drink);
void dispense_drink(int drink_number);
void get_required_motors(Drink* drink);
int ms_to_dispense(int amount);

// Constants
#define MARGIN 10 // 10 from the edge to look nice
#define Y_INC 90 // go down by 90 pixels when y is incremented
#define SCREEN_X 320
#define SCREEN_Y 240
#define PRESS_SEQUENCE 8
#define CONFIG_RECTS 8 //
#define MOTOR_COUNT 6
#define PUMP_RATE 400.0 // mL / min
#define PRIME_TIME 6 // TODO calculate this for real
#define SHOWN_DRINKS 3

#define BABYBLUE 0x03fcf8
#define WHITE    0xFFFFFF
#define RED      0xFF0000
#define GREEN    0x00FF00
#define BLUE     0x0000FF
#define CYAN     0x00FFFF
#define ORANGE   0xFF9933
#define MAGENTA  0xFF00FF
#define YELLOW   0xFFFF00
#define BLACK    0x000000
#define PINK     0xF670E3
#define LIGHTGRAY 0xD3D3D3
// Enums and Structs
enum Buttons { UP, DOWN, SUBMIT };
typedef enum Modes {CONFIG, DISPLAY, SELECTMIXIE, CLEANING} Modes;


// Global Variables
GUI_RECT rects[CONFIG_RECTS]; // predefined rectangles to store in
GUI_RECT dispenser_rects[SHOWN_DRINKS + 1];
//char config_data[CONFIG_RECTS][WORD_SIZE] = {"Configuration Menu", "Pink Whitney", "Tequila", "Doctor", "No Drink", "No Drink", "No Drink"}; // stores the sent data to display
static const uint8 CYCODE eeprom_config_data[MOTOR_COUNT] = {255, 255, 255, 255, 255, 255};
uint8 config_data[MOTOR_COUNT] = {0, 0, 0, 0, 0, 0}; // Vodka, Tonic, Beer, Gin, Seltzer, Pink Whit

extern const int NUM_DRINKS;
extern char Liquids[NUM_MIXIES][WORD_SIZE];

Drink** drinks;
Drink** menu;
int previous_presses[PRESS_SEQUENCE] = {0, 0, 0, 0, 0, 0, 0, 0};
int special_sequence[PRESS_SEQUENCE] = {UP, DOWN, UP, DOWN, UP, UP, DOWN, DOWN};
int required_motors[MOTOR_COUNT] = {0, 0, 0, 0, 0, 0};
int dispense_amount[MOTOR_COUNT] = {0, 0, 0, 0, 0, 0};
int button_number = 0;
int mixie_scroll = 0;
int motor_scroll = 0;
int drink_scroll = 0;
int timer_count = 0;
int menu_length = 1;
uint8* menu_indices;
Modes current_display;


const GUI_POINT UpArrowPoints[] = {
 { 30, 20},
 { 10, 20},
 { 20, 0}
};
const GUI_POINT DownArrowPoints[] = {
 { 30, 0},
 { 20, 20},
 { 10, 0}
};
CY_ISR ( Down_Button_Handler ) {

    if (current_display == CONFIG) {
        int old_motor = motor_scroll;
        motor_scroll--;
        motor_scroll = clean_number(motor_scroll, MOTOR_COUNT+1);
        if (motor_scroll == MOTOR_COUNT) {
            redraw_config_text("Clean Tubing", 7, BABYBLUE);
            draw_active_config(old_motor, old_motor, WHITE); // clear the old motor still
        } else if (old_motor == MOTOR_COUNT) {
            redraw_config_text("Clean Tubing", 7, WHITE);
            draw_active_config(motor_scroll, motor_scroll, PINK);
        } else {
            draw_active_config(motor_scroll, old_motor, PINK);
        }
    } else if (current_display == SELECTMIXIE) {
        redraw_config_text(Liquids[mixie_scroll], motor_scroll, BLACK);
        mixie_scroll--;
        mixie_scroll = clean_number(mixie_scroll, NUM_MIXIES);
        redraw_config_text(Liquids[mixie_scroll], motor_scroll, ORANGE);
    } 
    else if (current_display == DISPLAY) {
        drink_scroll--;
        drink_scroll = clean_number(drink_scroll, menu_length);
        update_dispenser_text();
    }
    push_to_list(previous_presses, DOWN, PRESS_SEQUENCE);
}

CY_ISR ( Up_Button_Handler ) {
    if (current_display == CONFIG) {
        int old_motor = motor_scroll;
        motor_scroll++;
        motor_scroll = clean_number(motor_scroll, MOTOR_COUNT+1);
        if (motor_scroll == MOTOR_COUNT) {
            redraw_config_text("Clean Tubing", 7, BABYBLUE);
            draw_active_config(old_motor, old_motor, WHITE); // clear the old motor still
        } else if (old_motor == MOTOR_COUNT) {
            redraw_config_text("Clean Tubing", 7, WHITE);
            draw_active_config(motor_scroll, motor_scroll, PINK);
        } else {
            draw_active_config(motor_scroll, old_motor, PINK);  
        }
    } else if (current_display == SELECTMIXIE) {
        redraw_config_text(Liquids[mixie_scroll], motor_scroll, BLACK);
        mixie_scroll++;
        mixie_scroll = clean_number(mixie_scroll, NUM_MIXIES);
        redraw_config_text(Liquids[mixie_scroll], motor_scroll, ORANGE);
    } 
    else if (current_display == DISPLAY) {
        drink_scroll++;
        drink_scroll = clean_number(drink_scroll, menu_length);
        update_dispenser_text();
    }
    push_to_list(previous_presses, UP, PRESS_SEQUENCE);
}

CY_ISR ( Submit_Button_Handler ) {
    if (compare_lists(previous_presses, special_sequence, PRESS_SEQUENCE)) {
        // Sequence entered, switch configuration
        if (current_display == CONFIG) {
            display_dispenser(); 
            push_to_list(previous_presses, SUBMIT, PRESS_SEQUENCE);    
            return;
        } else if (current_display == DISPLAY) {
            display_config(); 
            push_to_list(previous_presses, SUBMIT, PRESS_SEQUENCE);
            return;
        }
    } 
    if (current_display == CONFIG) {
        if (motor_scroll == MOTOR_COUNT) {
            redraw_config_text("Clean Tubing", 7, GREEN);
            clean_tubing();
        } else {
            change_config_color(motor_scroll, ORANGE);
            mixie_scroll = config_data[motor_scroll];
            current_display = SELECTMIXIE;
        }
    } else if (current_display == SELECTMIXIE) {     
        current_display = CONFIG;
        config_data[motor_scroll] = mixie_scroll;
        change_config_color(motor_scroll, GREEN);
        Em_EEPROM_Write(config_data, eeprom_config_data, sizeof(config_data));
        prime_pump(motor_scroll);
        display_config();
    } 
    else if (current_display == DISPLAY) {
        dispense_drink(menu_indices[drink_scroll]);
    }
    push_to_list(previous_presses, SUBMIT, PRESS_SEQUENCE);
}


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    SPIM_1_Start();
    Em_EEPROM_Start();
    uint8 eeprom_i = 0;
    for (eeprom_i=0; eeprom_i<MOTOR_COUNT; eeprom_i++) {
        if (eeprom_config_data[eeprom_i] != 255) {
            config_data[eeprom_i] = eeprom_config_data[eeprom_i];
        }
    }
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    menu_indices = malloc(NUM_DRINKS * sizeof(uint8));
    drinks = generate_drinks();
    Submit_Int_StartEx( Submit_Button_Handler );
    Up_Int_StartEx( Up_Button_Handler );
    Down_Int_StartEx( Down_Button_Handler );
    
    MainTask();
    for(;;)
    {
        /* Place your application code here. */
    }
}
void MainTask()
{
    GUI_Init();                             // initilize graphics library
    //GUI_SetOrientation(GUI_SWAP_XY | GUI_MIRROR_X);
    GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
    create_config_rects();
    create_dispenser_rects();
    GUI_Clear();
    GUI_SetFont(&GUI_Font8x16);
    display_dispenser();

}

// Sequence Functions
void push_to_list(int* list, int value, int size) {
    int i;
    for (i = 0; i < size-1; i++) {
        list[i] = list[i+1];   
    }
    list[size-1] = value;
}

int compare_lists(int* list1, int* list2, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (list1[i] != list2[i]) {
            return 0;    
        }
    }
    return 1;
}

// Drawing Functions

void draw_active_config(int new_motor, int old_motor, int color) {
    // Makes the old motor white again
    change_config_color(old_motor, WHITE);
    // Makes the active motor pink
    change_config_color(new_motor, color);
}

void change_config_color(int motor, int color) {
    GUI_SetColor(color);
    GUI_RECT rect = rects[motor];
    // Top Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x1, rect.y0);
    // Left Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x0, rect.y1);
    // Right Line
    GUI_DrawLine(rect.x1, rect.y0, rect.x1, rect.y1);
    // Bottom Line
    GUI_DrawLine(rect.x0, rect.y1, rect.x1, rect.y1);
    GUI_DispStringInRectWrap(Liquids[config_data[motor]], &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
}

void redraw_config_text(char* text, int motor, int color) {
    GUI_SetColor(color);
    GUI_DispStringInRectWrap(text, &rects[motor], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);    
}

void display_cleaning() {
    GUI_Clear();
    GUI_SetColor(BABYBLUE);
    GUI_DispStringAt("Cleaning... Please wait 2 minutes", SCREEN_X/2, SCREEN_Y/2);
    current_display = CLEANING;
}

int check_availability(Drink* drink) {
    GUI_Clear();
    int available = 1;
    int i, j;
    for (i = 0; i < drink->num_ingredients; i++) {
        Ingredient* ingredient = drink->ingredients[i];
        int ingredient_check = 0;
        for (j = 0; j < MOTOR_COUNT; j++) {
            int liquid_check = config_data[j];
            if ( ingredient->liquid == liquid_check ) {
                ingredient_check = 1;   
            }
        }
        if (ingredient_check == 0) {
            available = 0;    
        }
    }
    return available;
}

void generate_menu() {
    // Generates the menu based on what drinks are configured
    menu_length = 0;
    int i;
    for (i = 0; i < NUM_DRINKS; i++) {
        int available = check_availability(drinks[i]);
        if (available) {
            menu_indices[menu_length] = i;
            menu_length++;
        }
    }
}

void update_dispenser_text() {
    if (menu_length != 0) {
        GUI_SetColor(LIGHTGRAY); // Show two inactive  
        
        GUI_DispStringInRectWrap("                   ", &dispenser_rects[2], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
        GUI_DispStringInRectWrap(drinks[menu_indices[clean_number(drink_scroll-1, menu_length)]]->name, &dispenser_rects[2], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
        
        GUI_DispStringInRectWrap("                   ", &dispenser_rects[0], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
        GUI_DispStringInRectWrap(drinks[menu_indices[clean_number(drink_scroll+1, menu_length)]]->name, &dispenser_rects[0], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
        
        GUI_SetColor(WHITE); // Active one
        
        GUI_DispStringInRectWrap("                   ", &dispenser_rects[1], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
        GUI_DispStringInRectWrap(drinks[menu_indices[drink_scroll]]->name, &dispenser_rects[1], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
    }
}

void display_dispenser() {
    current_display = DISPLAY;
    generate_menu();
    GUI_Clear();
    if (menu_length == 0) {
        GUI_DispStringInRectWrap("Mork or Chungie, set this bitch up", &dispenser_rects[1], GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
    } else {

    GUI_SetColor(WHITE);
    GUI_FillCircle(20, SCREEN_Y/2, 10); // Submit Symbol
    GUI_SetColor(GREEN);
    GUI_FillCircle(20, SCREEN_Y/2, 5);
    GUI_SetColor(WHITE);
    GUI_FillPolygon(UpArrowPoints, GUI_COUNTOF(UpArrowPoints), 280, 40);
    GUI_FillPolygon(DownArrowPoints, GUI_COUNTOF(DownArrowPoints), 280, 180);
    GUI_RECT rect = dispenser_rects[SHOWN_DRINKS];
    GUI_DispStringInRectWrap("Welcome to Mork and Chungus's Bar Bot!", &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
    rect = dispenser_rects[1];
    // Top Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x1, rect.y0);
    // Left Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x0, rect.y1);
    // Right Line
    GUI_DrawLine(rect.x1, rect.y0, rect.x1, rect.y1);
    // Bottom Line
    GUI_DrawLine(rect.x0, rect.y1, rect.x1, rect.y1);
    update_dispenser_text();
    }
}



void display_config() {
    GUI_Clear();
    GUI_SetColor(WHITE);
    // Configuration Menu at top
    GUI_RECT rect = rects[6];
    // Top Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x1, rect.y0);
    // Left Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x0, rect.y1);
    // Right Line
    GUI_DrawLine(rect.x1, rect.y0, rect.x1, rect.y1);
    // Bottom Line
    GUI_DrawLine(rect.x0, rect.y1, rect.x1, rect.y1);    
    GUI_DispStringInRectWrap("Configuration Menu", &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
    
    // Clean tubes at bottom
    rect = rects[7];
    // Top Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x1, rect.y0);
    // Left Line
    GUI_DrawLine(rect.x0, rect.y0, rect.x0, rect.y1);
    // Right Line
    GUI_DrawLine(rect.x1, rect.y0, rect.x1, rect.y1);
    // Bottom Line
    GUI_DrawLine(rect.x0, rect.y1, rect.x1, rect.y1);    
    GUI_DispStringInRectWrap("Clean Tubing", &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);    
    int i = 0;     
    for (i = 0; i < MOTOR_COUNT; i++) {
        GUI_RECT rect = rects[i];
        // Top Line
        GUI_DrawLine(rect.x0, rect.y0, rect.x1, rect.y0);
        // Left Line
        GUI_DrawLine(rect.x0, rect.y0, rect.x0, rect.y1);
        // Right Line
        GUI_DrawLine(rect.x1, rect.y0, rect.x1, rect.y1);
        // Bottom Line
        GUI_DrawLine(rect.x0, rect.y1, rect.x1, rect.y1);
        
        GUI_DispStringInRectWrap(Liquids[config_data[i]], &rect, GUI_TA_HCENTER | GUI_TA_VCENTER, GUI_WRAPMODE_WORD);
    }
    current_display = CONFIG;
    draw_active_config(0, 0, PINK);
}
// Setup Display Functions
void create_dispenser_rects() {
    int i;
    int x_padding = 60;
    int y_padding = 75;
    int y_inc = 30;
    int y = 0;
    GUI_RECT title_rect = {MARGIN, MARGIN, SCREEN_X-MARGIN, MARGIN+y_inc};
    dispenser_rects[SHOWN_DRINKS] = title_rect;
    for (i = 0; i < SHOWN_DRINKS; i++) {
        GUI_RECT new_rect = {x_padding, (y*y_inc)+y_padding, (SCREEN_X-x_padding), ((y+1)*y_inc)+ y_padding};
        dispenser_rects[i] = new_rect;      
        y++;
    }
}
void create_config_rects() {
    // Creates the rectangles needed to display our data, creates two full width
    // rectangles then pairs the rest of the way down.
    int x = 0;
    int y = 0;
    uint i;
    int config_inc = 20;
    GUI_RECT title_rect = {MARGIN, MARGIN, SCREEN_X-MARGIN, MARGIN+config_inc};
    rects[6] = title_rect;
    GUI_RECT clean_rect = {MARGIN, SCREEN_Y-MARGIN-config_inc, SCREEN_X-MARGIN, SCREEN_Y-MARGIN};
    rects[7] = clean_rect;

    for (i = 0; i < MOTOR_COUNT; i++) {
        if (x == 0) {
            // left
            GUI_RECT new_rect = {MARGIN, MARGIN+(y*Y_INC)+config_inc, (SCREEN_X-MARGIN) /3, MARGIN+ ((y+1)*Y_INC)+ config_inc};
            rects[i] = new_rect;
        } else if (x == 1) {
            // middle
            GUI_RECT new_rect = {(SCREEN_X-MARGIN) /3, MARGIN+(y*Y_INC)+config_inc, (SCREEN_X-MARGIN)*2 /3, MARGIN+ ((y+1)*Y_INC)+ config_inc};
            rects[i] = new_rect;
        }
        else {
            // right
            GUI_RECT new_rect = {(SCREEN_X-MARGIN)*2 /3, MARGIN+(y*Y_INC)+config_inc, SCREEN_X-MARGIN, MARGIN+((y+1)*Y_INC)+config_inc};
            rects[i] = new_rect;
        }
        if (x == 2) {
            y++; // go to next line if end of this line
        }
        x++; // increment the side for the next one
        x %= 3;
    }
}

// Utility Functions

int clean_number(int num, int count) {
    return (num + count) % count;
}

int ms_to_dispense(int amount) {
    return (amount / PUMP_RATE) * 60 * 1000;
    
}
int comp (const void * elem1, const void * elem2) 
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

// Motor Functions
void get_required_motors(Drink* drink) {
    int i, j;
    for (i = 0; i < MOTOR_COUNT; i++) {
        required_motors[i] = 0;
        dispense_amount[i] = 0;
    }
    for (i = 0; i < MOTOR_COUNT; i++) {
        for (j = 0; j < drink->num_ingredients; j++) {
            if (config_data[i] == drink->ingredients[j]->liquid) {
                required_motors[i] = 1;
                dispense_amount[i] = ms_to_dispense(drink->ingredients[j]->amount);
            }
        }
    }
}

void dispense_drink(int drink_number) {
    Drink* drink = drinks[drink_number];
    get_required_motors(drink); // now have which motors and which amounts
    int i;
    for (i = 0; i < MOTOR_COUNT; i++) {
        if (required_motors[i]) {
            relay_on(i);
            CyDelay(dispense_amount[i]);
            relay_off(i);
        }
    }
    display_dispenser();
    // qsort(dispense_amount, sizeof(dispense_amount)/sizeof(*dispense_amount), sizeof(*dispense_amount), comp);

}

void relay_flip(int button_num) {
    if (button_num == 0) {
        Relay_1_Write(~Relay_1_Read());
    } else if (button_num == 1) {
        Relay_2_Write(~Relay_2_Read());
    } else if (button_num == 2) {
        Relay_3_Write(~Relay_3_Read());
    } else if (button_num == 3) {
        Relay_4_Write(~Relay_4_Read());
    } else if (button_num == 4) {
        Relay_5_Write(~Relay_5_Read());
    } else if (button_num == 5) {
        Relay_6_Write(~Relay_6_Read());
    }
}
void relay_on(int motor) {
     if (motor == 0) {
        Relay_1_Write(0);
    } else if (motor == 1) {
        Relay_2_Write(0);
    } else if (motor == 2) {
        Relay_3_Write(0);
    } else if (motor == 3) {
        Relay_4_Write(0);
    } else if (motor == 4) {
        Relay_5_Write(0);
    } else if (motor == 5) {
        Relay_6_Write(0);
    }   
}

void relay_off(int motor) {
     if (motor == 0) {
        Relay_1_Write(1);
    } else if (motor == 1) {
        Relay_2_Write(1);
    } else if (motor == 2) {
        Relay_3_Write(1);
    } else if (motor == 3) {
        Relay_4_Write(1);
    } else if (motor == 4) {
        Relay_5_Write(1);
    } else if (motor == 5) {
        Relay_6_Write(1);
    }   
}
void prime_pump(int motor) {
    relay_on(motor);
    CyDelay(1000 * PRIME_TIME);
    relay_off(motor);
}

void clear_config_data() {
    // clears all the words we've used to prepare for next data send
    int i;
    for (i = 0; i < MOTOR_COUNT; i++) {
        config_data[i] = 0;
    }
}

void clean_tubing() {
    // TODO this
    clear_config_data();
    display_cleaning();
    int i;
    for (i = 0; i < MOTOR_COUNT; i++) {
        relay_on(i);
    }
    CyDelay(1000 * 120);
    for (i = 0; i < MOTOR_COUNT; i++) {
        relay_off(i);
    }
    display_config();
}



/* [] END OF FILE */
