# This code takes a sequence of DNA and a CSV file containing STR counts for a list of individuals
# and then output to whom the DNA (most likely) belongs.

import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error: usage file.csv dna.txt")
        return 1

    # TODO: Read database file into a variable
    # Open file
    with open(sys.argv[1], 'r') as database:
        # Read file into a dictionary
        buffer = csv.DictReader(database)

        # Creates 2 list: one for headers, one for information
        header = buffer.fieldnames

        source_dict = []
        for row in buffer:
            source_dict.append(row)

    # Done creating database

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as unsub:
        person = unsub.read()

    # TODO: Find longest match of each STR in DNA sequence
    # Define how many STRs types are being analyzed, header (expect the name field)
    strs_types = []
    i = 1
    while i < len(header):
        strs_types.append(header[i])
        i += 1

    # Find how many times those sequences repeat in person
    # Create a list with those numbers
    p = {}
    for i in range(len(strs_types)):
        p[strs_types[i]] = longest_match(person, strs_types[i])

    # TODO: Check database for matching profiles
    # Go through each row and break if it is a match

    for r in range(len(source_dict)):
        if compare_row(p, source_dict[r]) == True:
            print(source_dict[r]['name'])
            return

    # If there isn't a match print 'No Match'
    print("No Match")
    return


def compare_row(person, database):
    # Look at a row, see if p[TEXT] number matches with row [TEXT] number
    # If yes, see if strs_types[TEXT2] number matches with row [TEXT2] number
    for key in person:
        if person[key] == int(database[key]):
            pass
        else:
            return False

    return True


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


if __name__ == "__main__":
    main()
