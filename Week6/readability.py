# TODO
from cs50 import get_string


def main():
    # Prompt the user for a string of text
    text = get_string("Text: ")

    # Count the number of letters, words, and sentences
    l = count_letter(text)
    w = count_word(text)
    s = count_sentence(text)

    # Calculate Coleman-Liau index
    L = l / w * 100
    S = s / w * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print results
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def count_letter(text):
    letter = 0

    for c in text:
        if c.isalpha():
            letter += 1

    return letter


def count_word(text):
    word = 1

    for c in text:
        if c.isspace():
            word += 1

    return word


def count_sentence(text):
    sentence = 0

    for c in text:
        if c == '.' or c == '!' or c == '?':
            sentence += 1

    return sentence


main()

