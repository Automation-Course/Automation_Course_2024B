import java.util.Scanner;

public class Exc1 {
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		boolean continueToCalc = true;
		System.out.println("Welcome to Binary-Decimal Calculator! :)\n");

		while (continueToCalc) {
			String choice = getMode();
		// as long as the user wants to continue calculate numbers
			if (choice.equals("A")) { // binary to decimal
				binaryToDecimal();


			} else { // decimal to binary
				double originalNumber = getDecimalInput();
				sc.nextLine();
				String binaryAns = decimalToBinary(originalNumber);
				printAnswer(originalNumber, binaryAns, choice);

			}
			continueToCalc = anotherGame();

		}

	}

	public static String getMode() {
		// CHOOSING MODE: binary->decimal or decimal->binary

		boolean validChoice = false;
		String choice = "";
		while (!validChoice) {    // input validation
			System.out.println("In order to convert binary number to decimal, please enter A.\n"
					+ "In order to convert decimal number to binary, plese enter B.");
			choice = sc.nextLine().trim();
			if (choice.equals("A") || choice.equals("B")) {
				validChoice = true;
			} else {
				System.out.println("Please enter only A or B! \n");
			}
		}
		return choice;
	}

	public static double getDecimalInput() {
		// ENTERING NUMBER
		System.out.println("Please enter a number to convert:");
		boolean validNumber = false;
		double originalNumber = 0;

		while (!validNumber) {
			if (!sc.hasNextDouble()) { // If input is not a valid double
				System.out.println("That's not a valid number. Please enter a valid decimal number:");
				sc.next(); // Clear the invalid input
			} else { // if the input is a number
				originalNumber = sc.nextDouble();
				if (originalNumber < 0) {
					System.out.println("Sorry. This calculator is only for positive numbers. Please enter a positive decimal number:");
				} else { // positive number - exit the loop
					validNumber = true;
				}
			}
		}
		return originalNumber;
	}

	public static String decimalToBinary(double originalNumber) {
		int integerPart = (int) Math.floor(originalNumber); // separating to 2 parts
		double fractionalPart = originalNumber - integerPart;
		String ans = "";
		if (integerPart == 0 && fractionalPart == 0) {
			ans = "0";
		} else {
			// dealing with the integer part:
			if (integerPart == 0) { // in case the input is like 0.5
				ans = "0";
			}
			while (integerPart > 0) {
				int remain = integerPart % 2;
				ans = remain + ans;  // concatenating the remain to the ans from the left side
				integerPart /= 2;
			}
			if (fractionalPart != 0) {
				ans = ans + ".";
			}
			// dealing with the fractional part:
			int numOfDigits = 0; // precision of the answer
			while (fractionalPart > 0 && numOfDigits < 10) {
				double product = fractionalPart * 2;
				int integer = (int) Math.floor(product);
				ans = ans + integer;  // concatenating the integer part to the ans from the right side
				fractionalPart = product - integer;
				numOfDigits++;
			}
		}
		return ans;
	}

	public static void printAnswer(double originalNumber, String convertedNumber, String choice) {
		// prints the calculated answer
		System.out.println("The decimal number " + originalNumber + " equals to the binary number " + convertedNumber + "\n");
	}

	public static boolean anotherGame() {
		// checks if the user wants to calculate another nunmber
		System.out.println("Would you like to convert another number? \n"
				+ "please enter Y to continue and any other input to finish" );

		String continueInput = sc.nextLine(); // Read the next line
		if (continueInput.equals("Y")) {
			return true;
		}
		else {
			System.out.println("Good Bye");
			return false;
		}
	}

	public static boolean checkCorrectBinary(String num) {
		// checks if the user's binary number input is correct
		int length = num.length();
		int dotNum = 0;
		int dot = findDot(num);
		for (int i = 0; i < length; i++) {
			if (num.charAt(i) == '.') { //checks if there is a . in the input
				dotNum += 1;
				if (dotNum > 1 || dot == 0 || dot == length - 1) {
					return false;
				}
			} else if (num.charAt(i) != '1' && num.charAt(i) != '0') {// if there is chars that aren't binary numbers
				return false;
			}
		}
		return true;
	}

	public static int findDot(String num) {
		//finds the dot's index
		if (num.contains(".")) {
			int length = num.length();
			for (int i = 0; i < length; i++) {
				if (num.charAt(i) == '.') {
					return i;
				}
			}
		}
		return -1; // if there isn't a dot in the user's input
	}

	public static double binaryToDecimal() {
		//converts binary number into a decimal number
		String num = getBinaryInput();
		int length = num.length();
		int dot = findDot(num);
		double ans = 0;
		if (dot == -1) { //if there isn't a dot in the input
			for (int i = length - 1; i >= 0; i--) {
				int numeric = Character.getNumericValue(num.charAt(i));
				double value = Math.pow(2, length - i - 1);
				ans += numeric * value; // calculates the value
			}
			System.out.println("The binary number " + num + " equals to the decimal number " + ans + "\n");
			return ans;
		} else {
			for (int i = dot - 1; i >= 0; i--) {
				//calculates before the dot
				int numeric = Character.getNumericValue(num.charAt(i));
				double value = Math.pow(2, dot - i - 1);
				ans += numeric * value;
			}
			for (int j = dot + 1; j < length; j++) {
				// calculates after the dot
				int numeric = Character.getNumericValue(num.charAt(j));
				double value = Math.pow(2, dot - j);
				ans += numeric * value;
			}
		}
		System.out.println("The binary number " + num + " equals to the decimal number " + ans + "\n"); // prints the answer
		return ans;
	}
	public static String getBinaryInput () {
		// gets the user's  input
		System.out.println("Please enter a binary number to convert:");
		boolean flag = true;
		while (flag) { //as long as the input is incorrect
			String input = sc.nextLine();
			if (checkCorrectBinary(input)) {
				return input;
			}
			else {
				System.out.println("Incorrect input please try again");
			}
		}
		return "bla"; //will never return this because flag will be true as long as the input is incorrect
	}
}


