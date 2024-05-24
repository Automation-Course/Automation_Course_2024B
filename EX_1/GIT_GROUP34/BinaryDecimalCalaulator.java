import java.util.Scanner;

public class BinaryDecimalCalaulator {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Welcome to our calculator :)");

		while (true) {
			System.out.println("Please select an option:"); // menu
			System.out.println("1. Convert Binary to Decimal");
			System.out.println("2. Convert Decimal to Binary");
			System.out.println("3. End the program");
			Double choice = scanner.nextDouble();
			String Input;

			if (choice == 1) {
				System.out.println("Please enter a binary number:");
				Input = scanner.next();
				if (isBinary(Input)) { // check if binary
					double decimalOutput = binaryToDecimal(Input); // convert
					System.out.println("The Decimal Is: " + decimalOutput);
				} else {
					System.out.println("Invalid input. Please enter a number containing only 0/1/.");
				}
			} else if (choice == 2) {
				System.out.println("Please enter a decimal number:");
				Input = scanner.next();
				if (isDecimal(Input)) { // check if decimal
					double decimalValue = Double.parseDouble(Input);
					String binaryOutput = decimalToBinary(decimalValue); // convert
					System.out.println("The Binary Is: " + binaryOutput);
				} else {
					System.out.println("Invalid input. Please enter a number containing only 0-9/.");
				}
			} else if (choice == 3) {
				System.out.println("Thank you! Goodbye");
				break;
			} else {
				System.out.println("Invalid selection. Please choose 1/2/3");
			}

			while (true) {
				System.out.println("Do you wish to calculate another number?"); // check if the user wants to continue

				System.out.println("1. Yes");
				System.out.println("2. No");
				choice = scanner.nextDouble();

				if (choice == 1) {
					break;
				} else if (choice == 2) {
					System.out.println("Thank you! Goodbye");
					scanner.close();
					return;
				} else {
					System.out.println("Invalid selection. Please choose 1/2");
				}
			}
		}
	}

	public static boolean isBinary(String binary) { // checks if the input is a binary number
		int dotCount = 0;

		for (int i = 0; i < binary.length(); i++) {
			char c = binary.charAt(i);
			if (c != '0' && c != '1' && c != '.') {
				return false;
			}
			if (c == '.') { // check for maximum 1 dot
				dotCount++;
				if (dotCount > 1) {
					return false;
				}
			}
		}

		if (binary.startsWith(".") || binary.endsWith(".")) { // check the dot is not in the beginning\end
			return false;
		}

		return true;
	}

	public static boolean isDecimal(String decimal) { // check that the input is a decimal number
		int dotCount = 0;

		for (int i = 0; i < decimal.length(); i++) {
			char c = decimal.charAt(i);
			if ((c < '0' || c > '9') && c != '.') { // checks that the input is only numbers / .
				return false;
			}
			if (c == '.') { // check there is maximum 1 dot
				dotCount++;
				if (dotCount > 1) {
					return false;
				}
			}
		}

		if (decimal.startsWith(".") || decimal.endsWith(".")) { // check the dot is not in the beginning\end
			return false;
		}

		return true;
	}

	public static double binaryToDecimal(String binary) { // method to convert from binary to decimal number
		int dot = binary.indexOf('.');
		if (dot == -1) {
			dot = binary.length();
		}

		double decimal = 0;
		for (int i = 0; i < dot; i++) { // convert the number before the dot
			char binaryChar = binary.charAt(dot - 1 - i);
			if (binaryChar == '1') {
				decimal += Math.pow(2, i);
			}
		}

		for (int i = dot + 1; i < binary.length(); i++) { // convert the number after the dot
			char binaryChar = binary.charAt(i);
			if (binaryChar == '1') {
				decimal += Math.pow(2, dot - i);
			}
		}

		return decimal;
	}

	public static String decimalToBinary(double decimal) {
		if (decimal == 0) {
			return "0";
		}

		String binary = "";
		int intPart = (int) decimal;
		if (intPart == 0) {
			binary = "0";
		}
		while (intPart > 0) { // Convert the int part
			int remainder = intPart % 2;
			binary = remainder + binary;
			intPart /= 2;
		}

		double fractionalPart = decimal - (int) decimal;
		if (fractionalPart > 0) { // Convert the fractional part
			binary += ".";
			int place = 1;
			while (fractionalPart > 0 && place <= 10) {
				double placeValue = Math.pow(2, -place);
				if (fractionalPart >= placeValue) {
					binary += "1";
					fractionalPart -= placeValue;
				} else {
					binary += "0";
				}
				place++;
			}
		}
		return binary;
	}

}