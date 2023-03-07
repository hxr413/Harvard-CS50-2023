# TODO
from cs50 import get_int


def main():
    cardnum = get_int("Number: ")

    # Luhn’s Algorithm
    digitnum, digit, sum = 0, 0, 0

    if cardnum < 0:
        print('Please input your credit card number with no hyphens.')
        main()
    else:
        while cardnum > 0:
            digit2 = digit
            digit = cardnum % 10
            digitnum += 1

            if digitnum % 2 == 0:
                sum += digit * 2 % 10 + digit * 2 // 10
            else:
                sum += digit

            cardnum = cardnum // 10

    # Determine the type of the card
    type = 'INVALID'

    if sum % 10 == 0:
        # American Express: 15 digits, start with 34 or 37
        if digitnum == 15 and digit == 3 and (digit2 == 4 or digit2 == 7):
            type = 'AMEX'
        # MasterCard: 16 digits, start with 51-55
        elif digitnum == 16 and digit == 5 and digit2 <= 5 and digit2 >= 1:
            type = 'MASTERCARD'
        # Visa: 13 or 16 digits, start with 4
        elif digitnum == 13 or digitnum == 16 and digit == 4:
            type = 'VISA'

    print(type)


main()