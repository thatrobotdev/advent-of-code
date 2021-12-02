#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int countNumIncreases(const string &filename);

void processInput(const string &filename, int expectedNumIncrease);

int main() {
    // Redirect cout to output file (https://stackoverflow.com/a/10151286)
    ofstream out("out.txt");
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    // Process inputs
    processInput("test-input.txt", 7);
    processInput("input.txt", 1228);

    return 0;
}

/*
 * Counts the number of time a depth measurement increases from the previous measurement,
 * given a file with a list of depth measurements.
*/
int countNumIncreases(const string &filename) {
    int currentMeasurement; // current measurement
    int numIncreases = 0; // total number of increases between measurements

    // Open stream for input file
    ifstream input(filename);
    if (input.is_open()) {
        // File can be read

        int previousMeasurement; // previous measurement

        // Set the first input to previousMeasurement, to be compared to the next in the list
        input >> previousMeasurement;

        // Loop through all the other measurements, setting their value to currentMeasurement
        while (input >> currentMeasurement) {
            // Check if the current measurement is an increase over the previous measurement
            if (currentMeasurement > previousMeasurement) {
                // Increase, so add one to numIncreases
                numIncreases++;
            }
            // Setup previous measurement for the next loop
            previousMeasurement = currentMeasurement;
        }

        // Close the file
        input.close();
    } else {
        // File couldn't be read, throw exception
        throw runtime_error("Could not open file");
    }

    return numIncreases;
}

// Test input, taking a filename and an expected number of increases
void processInput(const string &filename, int expectedNumIncreases) {
    cout << "Testing " << filename << "..." << "\n";

    // Get the actual number of increases from the input
    const int actualNumIncreases = countNumIncreases(filename);

    // Print results
    cout << "Number of measurements larger than the previous measurement: " << actualNumIncreases << "\n";

    // Check if the results don't match what we expect
    if (actualNumIncreases != expectedNumIncreases) {
        // Results don't match, throw a logic error exception
        throw logic_error("Expected " + to_string(expectedNumIncreases) + " increases.");
    }
}
