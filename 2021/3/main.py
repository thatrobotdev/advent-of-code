import sys


def main():
    # Redirect stdout to output file
    sys.stdout = open('output.txt', 'w')

    # Process Inputs
    process_inputs("input-test.txt", 198)
    process_inputs("input.txt", 3148794)

    # Close output file
    sys.stdout.close()


# Find power consumption of the submarine
def process_inputs(filename, expected_power_consumption):
    # Open input file
    with open(filename, 'rt') as inputFile:
        # marks that setup is needed in the bit_frequencies array
        setup_needed = True

        # create empty bit_frequencies array, to eventually become
        # a 2D array of [[numZeroes, numOnes], ...] foe each bit position
        bit_frequencies = []

        # loop through all lines in file
        for line in inputFile:
            line_length = len(line) - 1  # line length

            # first time setup
            if setup_needed:
                # create empty bit_frequencies array with dynamic size
                # depending on number of bits in first line of file
                bit_frequencies = [[0 for _ in range(2)] for _ in range(line_length)]
                setup_needed = False
            # Loop through each character in the line
            for i in range(line_length):
                # Add to frequency array mapping to character position,
                # depending on whether the bit is a 0 or a 1
                if int(line[i]) == 0:
                    bit_frequencies[i][0] += 1
                else:
                    bit_frequencies[i][1] += 1

        # Created using the most common bit in each position
        gamma_rate = ""

        # Created using the least common bit in each position
        epsilon_rate = ""

        # Loop through bit frequency data
        for bit in bit_frequencies:
            # If 0 is the most common frequency,
            if bit[0] > bit[1]:
                # it is the most common bit, so add 0
                # to gamma rate and 1 to epsilon rate
                gamma_rate += '0'
                epsilon_rate += '1'
            else:
                # opposite of above
                gamma_rate += '1'
                epsilon_rate += '0'

        # Convert gamma and epsilon rate to
        # decimal numbers from binary numbers
        gamma_rate = int(gamma_rate, 2)
        epsilon_rate = int(epsilon_rate, 2)

        # Calculate power consumption as gamma rate
        # multiplied by epsilon rate
        power_consumption = gamma_rate * epsilon_rate

        # Throw an error if power consumption does not match expected output
        if power_consumption != expected_power_consumption:
            raise RuntimeError("Expected " + str(expected_power_consumption) + ", got " + str(power_consumption))

        # Print result
        print("Power consumption:", gamma_rate * epsilon_rate)


if __name__ == '__main__':
    main()
