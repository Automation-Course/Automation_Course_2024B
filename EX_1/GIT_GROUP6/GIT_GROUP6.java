import java.util.Scanner;

public class GIT_GROUP6 {

	public static boolean checkDec(String d) //check if the number is decimal
	{
		for (int i = 0; i < d.length(); i++) {
			if ((d.charAt(i) < '0') || (d.charAt(i) > '9')) {
				System.out.println("Please enter a valid Decimal Number");
				return false;
			}
		}
		return true;
	}

	public static boolean checkBin(String b) //check if the number is binary
	{
		for (int i = 0; i < b.length(); i++) {
			if ((b.charAt(i) != '0') && (b.charAt(i) != '1')) {
				System.out.println("Please enter a valid Binary Number");
				return false;
			}
		}
		return true;
	}

	public static int calc_BtoD(String binNum) //convert binary to decimal base
	{
		int output = 0;
		for (int i = 0; i < binNum.length(); i++) {
			int power = binNum.length() - 1 - i; //calculates the power of 2 by the position of the binary number
			int digit = Integer.parseInt(String.valueOf(binNum.charAt(i))); // Gets the current digit in the binary number
			                                                               	//and converts it to int
			int temp = (int)Math.pow(2, power); //calculate the value of 2 ^ power
			output = output + (digit * temp);
		}
		return output;
	}

	public static String calc_DtoB(String decNum) //convert decimal to binary base
	{
		int dec = Integer.parseInt(decNum); //convert the decimal number represented as a string to an int
		String output = "";
		while (dec != 0) {
			output = dec % 2 + output; //add the remainder of division of the decimal number by 2 to the binary digits list
			dec = dec / 2; //divide the decimal number by 2 for the next remainder calculation
		}
		return output;
	}

	public static void main(String[] args) { //main menu
		Scanner scanner = new Scanner(System.in);
		boolean continueConversion = true; //continue to convert

		while (continueConversion) { //while the user want continue to convert
			System.out.println("Welcome to the Base Converter");
			System.out.println("Please choose which conversion you would like to execute:");
			System.out.println("1. Binary to Decimal");
			System.out.println("2. Decimal to Binary");
			String choice = scanner.next(); //the user's input

			while ((!choice.equals("1"))  && (!choice.equals("2"))) { //check if input is valid
		        System.out.println("Please enter a valid option (1 or 2):");
		        choice = scanner.next();
		    }
			
			if (choice.equals("1")) { //convert from Binary to Decimal
				System.out.println("Please enter a Binary Number:");
				String inputBin = scanner.next();
				while (!checkBin(inputBin)) { //check if the binary number is valid
					inputBin = scanner.next();
				}
				System.out.println("The decimal number is: " + calc_BtoD(inputBin)); // convert and print answer
			} else {
				System.out.println("Please enter a Decimal Number:");  //convert from Decimal to Binary
				String inputDec = scanner.next();
				while (!checkDec(inputDec)) { //check if the decimal number is valid
					inputDec = scanner.next();
				}
				System.out.println("The Binary number is: " + calc_DtoB(inputDec)); //convert and print answer
			}
			System.out.println("Do you want to continue converting numbers? (yes/no):");
			String continueChoice = scanner.next(); //if the user want to convert more numbers
			while(!(continueChoice.equalsIgnoreCase("yes") || continueChoice.equalsIgnoreCase("no"))) { //check if the answer is valid
				System.out.println("Please enter valid answer");
				continueChoice = scanner.next();
			}
			continueConversion = continueChoice.equalsIgnoreCase("yes"); //update the user's answer
		}
		System.out.println("Thank you for using the Base Converter. Goodbye!");
	}
}
