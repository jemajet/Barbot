
import string

# Prints the enum and array in alphabetical order for the alcohol, mixies,
# and drinks available
alc_and_mixies = ["Vodka", "Pink Whitney", "Doctor", "Tequila", "Gin", "White Rum", "Seltzer", "Coke", "Sprite", "Tonic",
                  "Whiskey", "Beer", "Ginger Beer", "Malibu", "Dark Rum", "Everclear", "Patty O's Hurricane Mix", "Cranberry Juice",
                  "Orange Juice", "Gatorade", "Lemonade", "Margarita Mix", "Pina Colada Mix", "Bloody Mary Mix", "Spiced Rum", "Red Bull",
                  "Cider", "Absinthe", "White Claw", "Pineapple Juice", "Melon Liqueur", "Kahlua", "Baileys", "Milk", "Peppermint Schanpps", "Champagne", "Barefoot", "Triple Sec"]
alc_and_mixies.sort()

drinks = {
}


def print_mixies():
    print("#define NUM_MIXIES {}".format(len(alc_and_mixies) + 1))
    mixies_s = "typedef enum Alc_and_Mixies { NODRINK, "
    mixies_list_s = "char Liquids[NUM_MIXIES][WORD_SIZE] = { \"No Drink\", "
    for drink in alc_and_mixies:
        drink_format = "".join(drink.split(" ")).upper()
        drink_format = drink_format.translate(
            str.maketrans('', '', string.punctuation))
        mixies_s += drink_format + ", "
        mixies_list_s += "\"{}\", ".format(drink)
    mixies_s += "} Liquid;"
    mixies_list_s += "};"
    print(mixies_s)
    print(mixies_list_s)


def print_drinks():
    print("const int NUM_DRINKS = {}\n".format(len(drinks)))
    s = ""
    sorted_drinks = sorted(drinks.values(), key=lambda x: x["name"])
    for i, drink in enumerate(sorted_drinks):
        name = drink["name"].translate(
            str.maketrans('', '', string.punctuation))
        name = "".join(name.split(" "))
        num_ingredients = drink["num_ingredients"]
        ingredients = drink["ingredients"]
        ingredient_names = list(ingredients.keys())
        for j in range(len(ingredient_names)):
            ingredient_names[j] = "".join(
                ingredient_names[j].split(" ")).upper()

        ingredient_values = list(ingredients.values())
        formatted_ingredient_names = repr(ingredient_names).replace(
            "[", "{").replace("]", "}").replace("'", "")
        formatted_ingredient_amounts = repr(ingredient_values).replace(
            "[", "{").replace("]", "}")

        s += "Liquid {}_Ingredients[{}] = {};\n".format(
            name, num_ingredients, formatted_ingredient_names)
        s += "int {}_Amounts[{}] = {};\n".format(
            name, num_ingredients, formatted_ingredient_amounts)
        s += "drinks[{}] = Drink_Create(\"{}\", {}_Ingredients, {}_Amounts, {});\n".format(
            i, drink["name"], name, name, num_ingredients)
        s += "\n"
    print(s)


def add_drink(name, liquids):
    drinks[name] = {"name": name,
                    "num_ingredients": len(liquids),
                    "ingredients": liquids}


def oz_to_closest_ml(oz):
    return round(oz * 29.5735)

add_drink("Screwdriver", {"Orange Juice": 150, "Vodka": 50})
add_drink("Gin & Tonic", {"Gin": 50, "Tonic": 150})
add_drink("Island Special", {"Doctor": 100})
add_drink("Harabedian Special", {"Pink Whitney": 100, "Seltzer": 100})
add_drink("Pina Colada", {"Pina Colada Mix": oz_to_closest_ml(
    5), "White Rum": oz_to_closest_ml(2)})
add_drink("DKE Special", {"Beer": 50})
add_drink("Red Bull Vodka", {"Red Bull": oz_to_closest_ml(8.4), "Vodka": 100})

# print_mixies()
print_drinks()
