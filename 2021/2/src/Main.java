import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws FileNotFoundException {

        // Redirect System.out to output file
        System.setOut(new PrintStream("output.txt"));

        // Process input
        processInput("test-input.txt", 150);
        processInput("input.txt", 1855814);
    }


    // Given a series of commands, finds the final horizontal position multiplied by the final depth of the submarine.
    private static void processInput(final String filename, final int expectedOutput) throws FileNotFoundException {
        // Open a scanner to read input file
        Scanner input = new Scanner(new File(filename));

        // Variables for horizontal position and depth of the submarine
        int horizontalPosition = 0;
        int depth = 0;

        // While not at the end of the file
        while(input.hasNext()) {
            // Variables for command given, and the parameter associated with the command
            final String command = input.next();
            final int parameter = input.nextInt();

            // Adjust variables based on command
            switch (command) {
                // `forward X` increases the horizontal position by `X` units
                case "forward" -> horizontalPosition += parameter;
                // `down X` increases the the depth by `X` units
                case "down" -> depth += parameter;
                // `up X` decreases the depth by `X` units
                case "up" -> depth -= parameter;
                // Command not found, throw exception
                default -> throw new RuntimeException("Invalid command read: " + command);
            }
        }
        // Close the scanner
        input.close();

        // Calculate the final horizontal position multiplied by the final depth
        final int horizontalPositionMultipliedByDepth = horizontalPosition * depth;

        // Check if we are expecting the output
        if(horizontalPositionMultipliedByDepth != expectedOutput) {
            // Did not get expected output, throw an exception
            throw new RuntimeException("Expected: " + expectedOutput + ", got " + expectedOutput);
        } else {
            // Success! Print results
            System.out.println("Multiplied final horizontal position by final depth: " + (horizontalPosition * depth));
        }


    }
}
