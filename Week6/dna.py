import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit('Usage: python dna.py data.csv sequence.txt')

    # TODO: Read database file into a variable
    # produce a list of dictionaries
    database = []
    with open(sys.argv[1], 'r') as file1:
        reader = csv.DictReader(file1)

    # the following 3 lines refer to the code in this video(https://www.youtube.com/watch?v=buYRzIURjnY)
        for row in reader:
            database.append(row)
    # database = [{'name': 'Alice', 'AGAT': '28', 'AATG': '42', 'TATC': '14'}, {...}, {...}, ...]

    subsequences = list(database[0].keys())[1:]

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file2:
        dna = file2.read()

    # TODO: Find longest match of each STR in DNA sequence
    # a dictionary with pairs of 'subsequence': 'longest_match'
    dict_subseq = {}

    # the syntax of the following 2 lines refers to the code in this video(https://www.youtube.com/watch?v=buYRzIURjnY)
    for subsequence in subsequences:
        dict_subseq[subsequence] = longest_match(dna, subsequence)

    # TODO: Check database for matching profiles
    # the syntax of this TODO refers to the code in this video(https://www.youtube.com/watch?v=buYRzIURjnY)
    for dict_person in database:
        match_count = 0
        for subsequence in subsequences:
            if int(dict_person[subsequence]) == dict_subseq[subsequence]:
                match_count += 1
        if match_count == len(subsequences):
            print(dict_person['name'])
            return

    print('No match')


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
