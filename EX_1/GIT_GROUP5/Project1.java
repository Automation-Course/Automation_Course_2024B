
import java.util.Scanner;
public class Project1 {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String input;

		while (true) {
			System.out.println("Hello! I am a calculator. Please choose a conversion base:");
			System.out.println("0 - Exit");
			System.out.println("1 - From decimal to binary");
			System.out.println("2 - From binary to decimal");
			input = sc.nextLine();
			switch (input) {
			case "0":
				System.out.println("Goodbye");
				sc.close();
				return;
			case "1":
				System.out.println("Enter a decimal number:");
				String decimalInput = sc.nextLine();
				if (checkDecimalNumber(decimalInput)) {
					returnBinary(decimalInput);
				} 
				else {
					System.out.println("Invalid decimal number. Please enter a valid number.");
				}
				break;
			case "2":
				System.out.println("Enter a binary number:");
				String binaryInput = sc.nextLine();
				if (isBinary(binaryInput)) {
					returnDecimal(binaryInput);
				} else {
					System.out.println("Invalid binary number. Please enter a valid binary number.");
				}
				break;
			default:
				System.out.println("Wrong input, please try again");
				break;
			}
		}
	}

	// check if the number is decimal, positive, without leading zeros and more than 1 dot
	public static boolean checkDecimalNumber(String input) {
		if (input.isEmpty()) {
			System.out.println("Error: empty input");
			return false;
		}    
		if (input.charAt(0) == '.' || input.charAt(input.length() - 1) == '.') {
			System.out.println("Error - unexpected dot");
			return false;
		}    
		if (input.startsWith("0") && !input.startsWith("0.") && input.length() > 1) {
			System.out.println("Error - unexpected 0 prefix");
			return false;
		}
		// check only positive numbers
		int dotCount = 0;
		for (char c : input.toCharArray()) {
			int ascii = (int) c;    
			if (!(ascii >= 48 && ascii <= 57) && ascii != 46) {
				System.out.println("Error - must enter a digit 0-9 or .");
				return false; 
			}
			// check no more than one dot
			if (ascii == 46) {
				dotCount++;    
				if (dotCount > 1) {
					System.out.println("Error - more than one dot");
					return false;
				}
			}
		}
		return true;
	}

	// check if the number is binary and has only one dot
	public static boolean isBinary (String number) {
		if (number.isEmpty()) {
			return false;
		}
		if (number.charAt(0) == '.' || number.charAt(number.length() - 1) == '.') {
			System.out.println("Error - unexpected dot");
			return false;
		}    
		int dotCount = 0;
		for (int i = 0; i < number.length(); i++) {
			if (number.charAt(i) != '0' && number.charAt(i) != '1' && number.charAt(i) != '.'){
				return false;
			}
			if (number.charAt(i) == '.') {
				dotCount++;    
				if (dotCount > 1) {
					System.out.println("Error - more than one dot");
					return false;
				}
			}
		}
		return true;
	}

	// getting binary number and return the decimal converted number
	public static void returnDecimal(String number) {
		int newNumber1 = 0;
		double newNumber2 = 0;
		int index1 = 0;
		int index2= -1;
		int indexOfPoint = number.indexOf(".");
		if (indexOfPoint > 0) {
			// before decimal dot
			for (int i = indexOfPoint-1; i >= 0; i--) {
				int n = (int)number.charAt(i) - 48; // n is 0 or 1 digit 
				newNumber1 += n*(Math.pow(2, index1));
				index1++;
			}
			// after decimal dot
			for (int j = indexOfPoint+1; j < number.length(); j++) {
				int n = (int)number.charAt(j) - 48; // n is 0 or 1 digit
				newNumber2 += n*(Math.pow(2, index2));
				index2--;
			}
			double result = newNumber1 + newNumber2 ; 
			System.out.println("Decimel representation of " + number + " is: " + result);
		}
		else {
			System.out.println(number);
			for (int k = number.length()-1; k >=0; k--) {
				int n = (int)number.charAt(k) - 48; 
				newNumber1+= n*(Math.pow(2, index1));
				index1++;
			}
			System.out.println("Decimel representation of " + number + " is: " + newNumber1);
		}
	}

	public static void returnBinary(String decimalNumber) {
		int indexOfPoint = decimalNumber.indexOf(".");
		if (indexOfPoint > 0) {
			String integerPart = decimalNumber.substring(0, indexOfPoint);
			String fractionalPart = decimalNumber.substring(indexOfPoint);
			// Convert integer part to binary
			String binaryIntegerPart = decimalToBinary(integerPart);
			// Convert fractional part to binary
			String binaryFractionalPart = decimalFractionalToBinary(fractionalPart);
			// Print the result
			System.out.println("Binary representation of " + decimalNumber + " is: "
			+ binaryIntegerPart + "." + binaryFractionalPart);
		}
		else {
			String binaryIntegerPart = decimalToBinary(decimalNumber);
			System.out.println("Binary representation of " + decimalNumber + " is: " + binaryIntegerPart);
		}
	}

	// Method to convert integer part of decimal number to binary string
	public static String decimalToBinary(String decimalNumber) {
		// Check if the decimal number is 0
		if (decimalNumber.equals("0")) {
			return "0";
		}
		StringBuilder binary = new StringBuilder();
		// Convert decimal number to binary
		while (Integer.parseInt(decimalNumber) != 0) {
			int newDecimalNumber = Integer.parseInt(decimalNumber);
			int remainder = newDecimalNumber % 2;
			binary.insert(0, remainder); // Prepend the remainder to the binary string
			newDecimalNumber /= 2; // Update the decimal number by dividing it by 2
			decimalNumber = String.valueOf(newDecimalNumber); // update for the loop
		}
		return binary.toString();
	}

	// Method to convert fractional part of decimal number to binary string
	public static String decimalFractionalToBinary(String fractionalPart) {
		StringBuilder binary = new StringBuilder();
		double fractionalNumber = Double.parseDouble("0" + fractionalPart); // Convert fractional part to a double
		int precision = 8; // Number of digits after the decimal point
		// Convert fractional part to binary
		for (int i = 0; i < precision; i++) {
			fractionalNumber *= 2;
			int bit = (int) fractionalNumber; // Extract the integer part (0 or 1)
			binary.append(bit);
			fractionalNumber -= bit; // Remove the integer part to keep the fractional part
		}
		return binary.toString();
	}
}
