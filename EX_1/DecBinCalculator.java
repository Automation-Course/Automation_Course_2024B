import java.util.Scanner;
public class DecBinCalculator {


	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in); // Setting up a scanner to read user input
		int sys = 1; // Variable to control the main loop

		// Main loop to keep the calculator running until the user chooses to exit
		while (sys != 0) {
			System.out.println();
			System.out.println("To convert decimal to binary press 1");
			System.out.println("To convert binary to decimal press 2");
			System.out.println("To exit press 0");

			// Getting user choice
			int x = getValidIntInput(sc);

			if (x == 1) {
				System.out.println("Please enter a decimal number:");
				int input = getValidIntInput(sc);
				decToBin(input); // Convert decimal to binary
			} else if (x == 2) {
				System.out.println("Please enter a binary number:");
				int input = getValidBinaryInput(sc);
				binToDec(input); // Convert binary to decimal
			} else if (x == 0) {
				sys = x; // Exiting the calculator
				System.out.println("Goodbye!");
			} else {
				System.out.println("Invalid choice. Please try again."); // Handling invalid input
			}
		}

		sc.close(); // Closing the scanner object to use less memory
	}

	// Function to convert binary to decimal
	public static void binToDec(int input) {
		int decimal = 0; // Initialize the decimal number
		int base = 1; // Initialize the base value

		// Converting binary to decimal
		while (input > 0) {
			int lastDigit = input % 10;
			input = input / 10;
			decimal += lastDigit * base;
			base = base * 2;
		}
		System.out.println("The decimal number is: " + decimal); // Printing the result
	}

	// Method to convert decimal to binary
	public static void decToBin(int input) {
		if (input == 0) {
			System.out.println("The binary number is: 0");
			return;
		}

		// StringBuilder is a class in Java that is used to create mutable sequences of characters.
		StringBuilder binary = new StringBuilder();

		// Converting decimal to binary
		while (input > 0) {
			binary.insert(0, input % 2);
			input /= 2;
		}
		System.out.println("The binary number is: " + binary.toString()); // Printing the result
	}

	// Method to get valid integer input from the user
	public static int getValidIntInput(Scanner sc) {
		while (true) {
			String input = sc.next();
			if (input.matches("\\d+")) { //makes sure that the inputs chars are only "0" to "9"
				try {
					return Integer.parseInt(input);  //converts a String input into an int
				} catch (NumberFormatException e) { // makes sure that the number is in int format (in the range of int)
					System.out.println("Input is too large, please enter a valid integer:");
				}
			} else {
				System.out.println("Invalid input, please enter a valid integer:");
			}
		}
	}

	// Method to get valid binary input from the user
	public static int getValidBinaryInput(Scanner sc) {
		while (true) {
			String input = sc.next();
			if (input.matches("[01]+")) { //makes sure that the inputs chars are only "0" and "1"
				try {
					return Integer.parseInt(input);    //converts a String input into an int
				} catch (NumberFormatException e) {   // makes sure that the number is in int format (in the range of int)
					System.out.println("Input is too large, please enter a valid binary number:");
				}
			} else {
				System.out.println("Invalid binary input, please enter a valid binary number:");
			}
		}
	}
}