package Automation;
import java.util.Scanner;

public class Ex1 {

	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		System.out.println("Please insert a decimal number");
		String decimal = sc.nextLine();

		System.out.println("Decimal To Binary: " + decimalToBinary(decimal));

		System.out.println("\n"+"Please insert a binary number");
		String binary = sc.nextLine();

		System.out.println("Binary To Decimal: " + binaryToDecimal(binary));
	}

	public static String decimalToBinary(String decimal) {
		// Checking valid input
		while(!checkDecimalInput(decimal)) {
			System.out.println("Incorrect Input! Please insert a decimal number again");
			decimal = sc.nextLine();		
		}
		long dec = Long.parseLong(decimal); // creating a 'long' variable to be used in the function
		if (dec == 0)
			return "0"; // Special case: decimal 0 is binary 0

		String binary = ""; // Initialize an empty string for binary representation

		while (dec > 0) {
			long bit = dec % 2; // Returns the remainder of a division
			binary += bit; // Adding bit to the binary string
			dec /= 2;
		}

		return binary;
	}

	public static String binaryToDecimal(String binary) {
		// Checking valid input
		while(!checkBinaryInput(binary)) {
			System.out.println("Incorrect Input! Please insert a binary number again");
			binary = sc.nextLine();		
		}
		long decimal = 0; // Initializing the decimal number 
		int n = binary.length(); // Begins with the length in the input's number

		for (int i = 0; i < n; i++) {
			int digit = binary.charAt(i) - '0'; // Getting the exact digit, from left to right each time
			long power = n - 1 - i; // Reducing the highest power by 1
			decimal += digit * Math.pow(2, power); // adding digit * 2^power
		}
		return String.valueOf(decimal);
	}

	private static boolean checkDecimalInput(String str) {
		for(int i = 0; i < str.length(); i++) {
			if(str.charAt(i) > '9' || str.charAt(i) < '0')
				return false;
		}
		return true;
	}

	private static boolean checkBinaryInput(String str) {
		for(int i = 0; i < str.length(); i++) {
			if(str.charAt(i) != '1' && str.charAt(i) != '0')
				return false;
		}
		return true;
	}



}
