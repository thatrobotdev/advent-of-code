#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <queue>

using namespace std;

int countNumIncreases(const string &filename);

int countThreeMeasurementSlidingWindowsIncrease(const string &filename);

int sumOfQueue(queue<int> q);

void processInputPart1(const string &filename, int expectedNumIncrease);

void processInputPart2(const string &filename, int expectedNumIncrease);

int main() {
    // Redirect cout to output file (https://stackoverflow.com/a/10151286)
    ofstream out("output.txt");
    cout.rdbuf(out.rdbuf());

    // Process Part 1
    cout << "Part 1:" << "\n";
    processInputPart1("test-input.txt", 7);
    processInputPart1("input.txt", 1228);
    cout << "\n";

    // Process Part 2
    cout << "Part 2: " << "\n";
    processInputPart2("test-input.txt", 5);
    processInputPart2("input.txt", 1257);

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

/*
 * Counts the number of times the sum of measurements in three-measurement sliding windows
 * increases from the previous sum. Stops when there aren't enough measurements to create
 * a new three-measurement sum.
*/
int countThreeMeasurementSlidingWindowsIncrease(const string &filename) {
    int numIncreases = 0; // total number of increases between sliding windows
    int currentInput; // current input being read from the file

    // Open stream for input file
    ifstream input(filename);
    if (input.is_open()) {
        // File can be read

        // Create two queues for the previous and current sliding window
        queue<int> previousSlidingWindow;
        queue<int> currentSlidingWindow;

        // Loop through all inputs until the end of the file, with a counter variable
        for (int i = 0; input >> currentInput; i++) {
            // Create offset for currentSlidingWindow from previousSlidingWindow
            if (i >= 1) {
                // If the current sliding window already has 3 elements
                if (currentSlidingWindow.size() > 2) {
                    // Remove from back of queue
                    currentSlidingWindow.pop();
                }
                // Add input to front of queue
                currentSlidingWindow.push(currentInput);
            }

            // If the previous sliding window already has 3 elements
            if (previousSlidingWindow.size() > 2) {

                // Calculate the sum of each window
                const int previousSum = sumOfQueue(previousSlidingWindow);
                const int currentSum = sumOfQueue(currentSlidingWindow);

                // If current sliding window has a greater sum than the previous sliding window
                if (currentSum > previousSum) {
                    // Add 1 to the number of increases
                    numIncreases++;
                }

                // Remove from back of queue
                previousSlidingWindow.pop();
            }
            // Add input to front of queue
            previousSlidingWindow.push(currentInput);
        }

        // Close the file
        input.close();
    } else {
        // File couldn't be read, throw exception
        throw runtime_error("Could not open file");
    }

    return numIncreases;
}

// Find the sum of a queue
int sumOfQueue(queue<int> q) {
    int sum = 0;

    // While the queue is not empty
    while (!q.empty()) {
        // Add the front element of the queue to sum and remove it from the queue
        sum += q.front();
        q.pop();
    }
    return sum;
}

// Test input, taking a filename and an expected number of increases
void processInputPart1(const string &filename, const int expectedNumIncreases) {
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

void processInputPart2(const string &filename, const int expectedNumIncreases) {
    cout << "Testing " << filename << "..." << "\n";

    // Get the actual number of increases from the input
    const int actualNumIncreases = countThreeMeasurementSlidingWindowsIncrease(filename);

    // Print results
    cout << "Number of sums larger than the previous sum: " << actualNumIncreases << "\n";

    // Check if the results don't match what we expect
    if (actualNumIncreases != expectedNumIncreases) {
        // Results don't match, throw a logic error exception
        throw logic_error("Expected " + to_string(expectedNumIncreases) + " increases.");
    }
}
