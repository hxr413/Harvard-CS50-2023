# TODO
from cs50 import get_float


def main():
    # Ask how many dollars the customer is owed
    dollars = get_dollars()

    int_dollars = int(dollars * 100)

    # Calculate the number of quarters to give the customer
    quarters = int_dollars // 25
    int_dollars = int_dollars - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = int_dollars // 10
    int_dollars = int_dollars - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = int_dollars // 5
    int_dollars = int_dollars - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = int_dollars // 1
    int_dollars = int_dollars - pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies
    print(f'{coins}')


def get_dollars():
    dollars = get_float('Change owed: ')

    if dollars < 0:
        print('Please input the number of dollars (non-negative) owed.')
        main()
    else:
        return dollars


main()
