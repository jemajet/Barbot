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
#include "drinks.h"
#include <string.h>

const int NUM_DRINKS = 7;
char Liquids[NUM_MIXIES][WORD_SIZE] = { "No Drink", "Absinthe", "Baileys", "Barefoot", "Beer", "Bloody Mary Mix", "Champagne", "Cider", "Coke", "Cranberry Juice", "Dark Rum", "Doctor", "Everclear", "Gatorade", "Gin", "Ginger Beer", "Kahlua", "Lemonade", "Malibu", "Margarita Mix", "Melon Liqueur", "Milk", "Orange Juice", "Patty O's Hurricane Mix", "Peppermint Schanpps", "Pina Colada Mix", "Pineapple Juice", "Pink Whitney", "Red Bull", "Seltzer", "Spiced Rum", "Sprite", "Tequila", "Tonic", "Triple Sec", "Vodka", "Whiskey", "White Claw", "White Rum", };

Ingredient* Ingredient_Create(Liquid liquid, int amount) {
    Ingredient* ingredient_ptr = malloc(sizeof(Ingredient));
    
    ingredient_ptr->liquid = liquid;
    ingredient_ptr->amount = amount;
    
    return ingredient_ptr;
};

/*
    Ingredient* ing = Ingredient_Create(VODKA, 50);
    GUI_DispDecAt(drinks[0]->num_ingredients, 20, 20, 2);
    for (i=0; i< drinks[0]->num_ingredients; i++) {
        //GUI_DispStringAt(Liquids[drinks[0]->ingredients[i]->liquid], 20, 60+20*i);
        //GUI_DispDecAt(drinks[0]->ingredients[i]->amount, 20, 120+20*i, 3);
        GUI_DispStringAt(Liquids[ing->liquid], 20, 60+20*i);
        GUI_DispDecAt(ing->amount, 20, 120+20*i, 3);
    }
*/
Drink* Drink_Create(char* name, Liquid* liquids, int* amounts, int num_ingredients) {
    Drink* drink = malloc(sizeof(Drink));
    
    strcpy(drink->name, name);
    drink->num_ingredients = num_ingredients;
    drink->ingredients = malloc(num_ingredients * sizeof(*drink->ingredients));
    int i;
    for (i = 0; i < num_ingredients; i++) {
        drink->ingredients[i] = Ingredient_Create(liquids[i], amounts[i]); 
    }
    return drink;
}


Drink** generate_drinks() {

    Drink** drinks = malloc(NUM_DRINKS * sizeof(*drinks));
    
    Liquid DKESpecial_Ingredients[1] = {BEER};
    int DKESpecial_Amounts[1] = {50};
    drinks[0] = Drink_Create("DKE Special", DKESpecial_Ingredients, DKESpecial_Amounts, 1);

    Liquid GinTonic_Ingredients[2] = {GIN, TONIC};
    int GinTonic_Amounts[2] = {50, 150};
    drinks[1] = Drink_Create("Gin & Tonic", GinTonic_Ingredients, GinTonic_Amounts, 2);

    Liquid HarabedianSpecial_Ingredients[2] = {PINKWHITNEY, SELTZER};
    int HarabedianSpecial_Amounts[2] = {100, 100};
    drinks[2] = Drink_Create("Harabedian Special", HarabedianSpecial_Ingredients, HarabedianSpecial_Amounts, 2);

    Liquid IslandSpecial_Ingredients[1] = {DOCTOR};
    int IslandSpecial_Amounts[1] = {100};
    drinks[3] = Drink_Create("Island Special", IslandSpecial_Ingredients, IslandSpecial_Amounts, 1);

    Liquid PinaColada_Ingredients[2] = {PINACOLADAMIX, WHITERUM};
    int PinaColada_Amounts[2] = {148, 59};
    drinks[4] = Drink_Create("Pina Colada", PinaColada_Ingredients, PinaColada_Amounts, 2);

    Liquid RedBullVodka_Ingredients[2] = {REDBULL, VODKA};
    int RedBullVodka_Amounts[2] = {248, 100};
    drinks[5] = Drink_Create("Red Bull Vodka", RedBullVodka_Ingredients, RedBullVodka_Amounts, 2);

    Liquid Screwdriver_Ingredients[2] = {ORANGEJUICE, VODKA};
    int Screwdriver_Amounts[2] = {150, 50};
    drinks[6] = Drink_Create("Screwdriver", Screwdriver_Ingredients, Screwdriver_Amounts, 2);

    return drinks;
}
/* [] END OF FILE */
