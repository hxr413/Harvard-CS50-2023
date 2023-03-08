menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}

cost = 0.00

while True:
    try:
        # take orders
        item = input('Item: ')
        order = item.title()

        # avoid keyerror
        if order in menu:
            # calculate cost
            cost += menu.get(order)
            print(f'Total: ${cost}0')

    except EOFError:
        print()
        break



