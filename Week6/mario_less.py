# TODO

from cs50 import get_int


def main():
    # ask user to input height
    height = get_int('Height: ')

    if height < 1 or height > 8:
        print('Please input a positive integer between 1 and 8, inclusive.')
        # restart the function, so that if user input a valid height, the program will continue to print
        main()
    else:
        # print the pyramid from i = 1 to height
        for i in range(1, height + 1):
            # there should be j spaces where j = height - i
            for j in range(height - i):
                print(" ", end="")
            for k in range(i):
                print("#", end="")
            print()


main()