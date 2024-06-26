import java.util.Scanner;
import java.util.InputMismatchException;


public class Project1 {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		while (true) {
			try {
				System.out.println("Choose an option:");
				System.out.println("1. Convert binary to decimal");
				System.out.println("2. Convert decimal to binary");
				System.out.println("3. Exit");
				int choice = scanner.nextInt();

				switch (choice) {
				case 1:
					System.out.print("Enter a binary number: ");
					String binaryInput = scanner.next();
					if (isValidBinary(binaryInput)) {
						int decimal = binaryToDecimal(binaryInput);
						System.out.println("Decimal: " + decimal);
					} else {
						System.out.println("Invalid binary number.");
					}
					break;
				case 2:
					System.out.print("Enter a decimal number(Non Negative Integer): ");
					try {
						int decimalInput = scanner.nextInt();
						if (decimalInput >= 0) {
							String binary = decimalToBinary(decimalInput);
							System.out.println("Binary: " + binary);
						} else {
							System.out.println("Invalid input. Accept only positive integer.");
						}
					} catch (InputMismatchException e) {
						System.out.println("Invalid input. Accept only Non Negative Integer.");
						scanner.next(); // Clear the invalid input
					}
					break;
				case 3:
					System.out.println("Exiting...");
					scanner.close();
					return;
				default:
					System.out.println("Invalid choice. Please choose again.");
				}
			} catch (InputMismatchException e) {
				System.out.println("Invalid input. Please choose again.");
				scanner.next(); // Clear the invalid input
			}
		}
	}

	// Check if a string is a valid binary number
	private static boolean isValidBinary(String binary) {
		for (char c : binary.toCharArray()) {
			if (c != '0' && c != '1') {
				return false;
			}
		}
		return true;
	}

	// Convert binary to decimal
	private static int binaryToDecimal(String binary) {
		int decimal = 0;
		int length = binary.length();

		for (int i = 0; i < length; i++) {
			char bit = binary.charAt(length - 1 - i);
			if (bit == '1') {
				decimal += Math.pow(2, i);
			}
		}

		return decimal;
	}

	// Convert decimal to binary
	private static String decimalToBinary(int decimal) {
	    if (decimal == 0) {
	        return "0";
	    }
	    String binary = "";
	    while (decimal > 0) {
	        int remainder = decimal % 2;
	        binary = remainder + binary; // Concatenate the remainder to the front of the binary string
	        decimal = decimal / 2;
	    }
	    return binary;
	}
}

