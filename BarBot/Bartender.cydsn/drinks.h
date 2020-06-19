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
#include "project.h"
#include <stdio.h>
#include <stdlib.h>

#define NUM_MIXIES 39
#define WORD_SIZE 50
extern char Liquids[NUM_MIXIES][WORD_SIZE];
extern const int NUM_DRINKS;

typedef enum Alc_and_Mixies { NODRINK, ABSINTHE, BAILEYS, BAREFOOT, BEER, BLOODYMARYMIX, CHAMPAGNE, CIDER, COKE, CRANBERRYJUICE, DARKRUM, DOCTOR, EVERCLEAR, GATORADE, GIN, GINGERBEER, KAHLUA, LEMONADE, MALIBU, MARGARITAMIX, MELONLIQUEUR, MILK, ORANGEJUICE, PATTYOSHURRICANEMIX, PEPPERMINTSCHANPPS, PINACOLADAMIX, PINEAPPLEJUICE, PINKWHITNEY, REDBULL, SELTZER, SPICEDRUM, SPRITE, TEQUILA, TONIC, TRIPLESEC, VODKA, WHISKEY, WHITECLAW, WHITERUM, } Liquid;

typedef struct Ingredients {
    Liquid liquid;
    int amount; // in mL!
} Ingredient;

typedef struct Drinks {
    char name[50];
    Ingredient** ingredients;
    int num_ingredients;
} Drink;

//Drink drinks[] = {SCREWDRIVER};

Ingredient* Ingredient_Create(Liquid liquid, int amount);
Drink* Drink_Create(char* name, Liquid* liquids, int* amounts, int num_ingredients);
Drink** generate_drinks();

/* [] END OF FILE */
