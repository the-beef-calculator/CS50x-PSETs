import csv
import sys


def main():

    # TODO: Check for command-line usage

    if (len(sys.argv) != 3):
        print("Usage: dna.py data.csv sequence.txt")
        return 1



    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        # Reading data from csv into a dictionary, while converting the values from strings to integers.
        databaseDNA = []
        headers = []

        for row in reader:
            convertedRow = {key: int(value) if value.isdigit() else value for key, value in row.items()}
            databaseDNA.append(convertedRow)

        headers = reader.fieldnames

        #removes "name" field from list, since this info is irrelevant
        del headers[0]


    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        person = file.readline()

    sequenceAmount = []

    # TODO: Find longest match of each STR in DNA sequence
    for i in range(len(headers)):
        sequenceAmount.append(longest_match(person,headers[i]))

    sampleDNA = {"name": "unknown"}

    #adding values into sample dictionary
    for i in range(len(headers)):
        sampleDNA[headers[i]] = sequenceAmount[i]



    # TODO: Check database for matching profiles

    print(compareTo(databaseDNA,sampleDNA,headers))


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


def compareTo(databaseDNA, sampleDNA, fields):

    for record in databaseDNA:
        match = True
        for field in fields:
            if field != 'name' and record[field] != sampleDNA[field]:
                match = False
                break
        if match:
            return record['name']

    return "No match"

main()


