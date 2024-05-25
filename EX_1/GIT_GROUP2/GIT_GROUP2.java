import java.util.Scanner;
import java.util.Vector;

public class GIT_GROUP2 {

	static Scanner sc = new Scanner(System.in);
	public static void main(String[] args) {
		int choice; 
		System.out.println("Hey you, welcome to our conversion calculator");
		do {
			System.out.println("Please enter a digit (0-2)>"); //present the menu
			System.out.println("0. End Program");
			System.out.println("1. Binary to decimal conversion calculator");
			System.out.println("2. Decimal to binary conversion calculator");
			choice = sc.nextInt();//take an input from the user
			sc.nextLine();
			if (choice == 1) { //binary to decimal conversion calculator
				String binaryNumber;
				boolean ValidBinary = false;
				do {
					System.out.println("Please insert a valid binary number");
					binaryNumber = sc.nextLine(); //take an input from the user
					ValidBinary = isValidBinary(binaryNumber);
				} while (ValidBinary == false);
				double ans = binaryToDecimal(binaryNumber);	
				System.out.println("The decimal number is " + ans);
			}
			if (choice == 2) { //decimal to binary conversion calculator
				String decimalNumber;
				boolean ValidDecimal = false;
				do {
					System.out.println("Please insert a valid decimal number");
					decimalNumber = sc.nextLine(); //take an input from the user
					ValidDecimal = isValidDecimal(decimalNumber); //check if valid
				} while (ValidDecimal == false);
				String ans = decimalToBinary(decimalNumber);
				System.out.println("The binary number is "+ans);
			}
			if (choice == 0) {// end program
				System.out.println("hope to see you soon :)");
			}			 
		} while (choice != 0);
	}//end main

	// check if the binary input is a valid number
	public static boolean isValidBinary(String input) {
		int pointCount = 0;
		if (input.isEmpty() || input.charAt(0) == '.' || input.charAt(input.length() - 1) == '.') {
			return false;
		}
		for (int i=0; i < input.length(); i++) {
			char c = input.charAt(i);
			if (c == '0' || c == '1') { // Check if the character is a valid binary digit
				continue; 
			} else if (c == '.') { // check if the character is a decimal point
				if (pointCount == 0) {
					pointCount++; // only one decimal point is allowed
					continue; 
				} else {
					return false; // if more than one decimal point is found
				}
			} else if (input.isEmpty() || input.charAt(0) == '.' || input.charAt(input.length() - 1) == '.') {
				return false;
			}
			else { 
				return false;
			}
		}
		return true;
	}

	// convert from binary input and return a decimal number
	public static double binaryToDecimal(String binaryNumber) { //1
		String[] parts = binaryNumber.split("\\."); //split the binary number to integer and fractional
		String integerPart = parts[0]; //the integer placed in index 0		
		String fractionalPart;
		if (parts.length > 1 ) { //we have fractional Part
			fractionalPart = parts[1];
		} else {
			fractionalPart = "";
		}
		double decimalIntegerPart = 0; //output
		int power = 0;
		for (int i = integerPart.length() - 1; i >= 0; i--) {// covert the integer part
			int digit = Integer.parseInt(String.valueOf(integerPart.charAt(i))); //Takes the rightmost digit
			decimalIntegerPart += digit * Math.pow(2, power);
			power++;
		}
		double decimalFractionalPart = 0;
		for (int i = 0; i < fractionalPart.length(); i++) {// covert the fractional part
			int digit = Integer.parseInt(String.valueOf(fractionalPart.charAt(i))); //Takes the leftmost digit
			decimalFractionalPart += digit * Math.pow(2, -(i + 1));
		}
		return decimalIntegerPart + decimalFractionalPart; //the output
	}

	// check if the decimal input is a valid number
	public static boolean isValidDecimal(String input) {
		int pointCount = 0;
		if (input.isEmpty() || input.charAt(0) == '.' || input.charAt(input.length() - 1) == '.') {
			return false;
		}
		for (int i=0; i < input.length(); i++) {
			char c = input.charAt(i);
			if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') { // Check if the character is a valid binary digit
				continue; 
			} else if (c == '.') {// check if the character is a decimal point
				if (pointCount == 0) {
					pointCount++; //  only one decimal point is allowed
					continue; 
				} else {
					return false; // if more than one decimal point is found
				}
			} 
			else { 
				return false;
			}
		}
		return true;
	}

	// help function that convert vector to string 
	public static String vectorToString(Vector<Integer> vector) {
		StringBuilder stringBuilder = new StringBuilder();
		for (int i = 0; i < vector.size(); i++) {
			stringBuilder.append(vector.get(i));
		}
		return stringBuilder.toString();
	}

	// convert from decimal input and return a binary number
	public static String decimalToBinary(String decimalNumber) {
		double num0 = Double.parseDouble(decimalNumber);// covert from string to double
		if (num0 == 0) { // exeption case
			return "0";
		}
		String[] parts = decimalNumber.split("\\."); //split the decimal number to integer and fractional
		String integerPart = parts[0]; //the integer placed in index 0
		String fractionalPart;
		if (parts.length > 1 ) { //we have fractional Part
			fractionalPart = "0." + parts[1];
		} else { //for the case of a whole decimal number, without a fraction
			fractionalPart = "0.0";
		}
		Vector<Integer> binaryIntegerPart = new Vector<>();
		Vector<Integer> binaryfractionalPart = new Vector<>();
		int integerPartByInt = Integer.parseInt(integerPart);
		double fractionalPartByDouble = Double.parseDouble(fractionalPart);
		int i = 0;
		while (integerPartByInt > 0)  { //calculations for the integer part
			binaryIntegerPart.add(i,integerPartByInt % 2); 
			integerPartByInt = integerPartByInt / 2; 
			i++; 
		} //end of while		
		Vector<Integer> binaryIntegerPartReversed = new Vector<>();
		for (int j=binaryIntegerPart.size()-1; j>=0; j--) { //creating the result vector - reverse order of the residuals
			binaryIntegerPartReversed.add(binaryIntegerPart.get(j));
		}			
		int j=0;
		while (fractionalPartByDouble > 0 && fractionalPartByDouble != 0) {
			if (binaryfractionalPart.size() >= 5) { // up to 5 digits after the point
				break;
			}
			// calculations for the fractional part
			fractionalPartByDouble = fractionalPartByDouble*2;
			if(fractionalPartByDouble >= 1) {
				binaryfractionalPart.add(j,1);
				fractionalPartByDouble = fractionalPartByDouble-1;
				j++;
			}
			else {
				binaryfractionalPart.add(j,0);
				j++;
			}
		}	
		String IntegerPartResult = vectorToString(binaryIntegerPartReversed);
		String fractionalPartResult = vectorToString(binaryfractionalPart);
		if (fractionalPartResult.equals("")) {// for case of only integer part
			return IntegerPartResult;
		}			
		if (integerPart.equals("0")) {// for case of only fractional part
			IntegerPartResult = "0";
		}	
		return IntegerPartResult + "." + fractionalPartResult;
	}	
}


