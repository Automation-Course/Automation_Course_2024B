
import java.util.Scanner;

public class CalculatorBD {
	static Scanner sc = new Scanner(System.in); 

	public static void main(String[] args) { // calculator main

		System.out.println("Welcome to the Calculator!");

		while (true) {
			System.out.println("\nChoose an option:");
			System.out.println("1. Decimal to Binary");
			System.out.println("2. Binary to Decimal");
			System.out.println("3. Exit");
			System.out.print("Enter your choice: ");
			// Input validation to ensure user enters an integer
            while (!sc.hasNextInt()) {
                System.out.println("Invalid input. Please enter an integer.");
                sc.next(); // consume the invalid input
                System.out.print("Enter your choice: ");
            }
            int choice = sc.nextInt();
			switch (choice) {
			case 1:
				decimalToBinary(); // convert decimal to binary
				break;
			case 2:
				binaryToDecimal(); // convert binary to decimal
				break;
			case 3:
				System.out.println("Exiting the Calculator. Goodbye!");
				System.exit(0);
			default:
				System.out.println("Invalid choice. Please try again.");
			}
		}
	}

	public static void decimalToBinary() {
		System.out.print("Enter a decimal number: ");
		String decimal = sc.next(); // user's input

		if(!isValidNumber(decimal)) // check if user's input is valid
			System.out.println("Invalid Input");
		else {

			if (checkIfDouble(decimal)) { // checking if the input contains "."
				String[] parts=decimal.split("\\."); // spliting the string before and after the "."
				int numA=Integer.parseInt(parts[0]);
				double numB=Double.parseDouble("0."+parts[1]);
				//System.out.println("A: "+numA +" B: "+numB);
				String binary1="";
				String binary3="";

				while(numA>0) { // finding the reverse binary number of the integer
					int digit= numA%2;
					numA= numA/2;
					//System.out.println("number: "+numA+ " digit: "+digit);
					binary1=binary1+digit;			
				}
				String binary2="";
				for(int i=0;i<=binary1.length()-1; i++) { // reversing the binary number
					binary2=binary1.charAt(i)+binary2;
				}
				int c=0;
				while(numB != 0&& c<10) { // finding the binary number of the fraction
					numB = numB*2 ;
					int digit= (int) numB;
					numB = numB- digit ;
					//System.out.println("number: "+numB+ " digit: "+digit);
					binary3=binary3+digit;	
					c++;
				}

				System.out.println("Binary equivalent: " + binary2+"."+binary3);


			}
			else { // non double input
				int decimal1=Integer.parseInt(decimal);
				String binary="";
				while(decimal1>0) { // finding the reverse binary number of the integer
					int digit= decimal1%2;
					decimal1= decimal1/2;
					//System.out.println("number: "+decimal1+ " digit: "+digit);

					binary=binary+digit;			
				}
				String binary2="";
				for(int i=0;i<=binary.length()-1; i++) { // reversing the binary number
					binary2=binary.charAt(i)+binary2;
				}
				System.out.println("Binary equivalent: " + binary2);
			}
			//String binary = Integer.toBinaryString(decimal);

		}
	}

	public static void binaryToDecimal() {
		System.out.print("Enter a binary number: ");
		String binary = sc.next();

		if(!isValidBinary(binary)) // non valid binary number
			System.out.println("Invalid");


		else { // user's input is valid
			if (checkIfDouble(binary)) { // check if user's input is valid
				double decimalA=0, decimalB = 0;
				int index = binary.indexOf(".");
				int countA = 0 , countB= -1;
				for (int i = index - 1; i >= 0; i--) { // converting the integer part of the input
					int digit = (binary.charAt(i))- '0';
					double plus = digit * Math.pow(2,countA); 
					decimalA = decimalA + plus;
					countA++;
				}
				for (int i = index + 1; i <= binary.length()-1; i++) { // converting the double part of the input
					int digit = (binary.charAt(i))- '0';
					double plus = digit * Math.pow(2,countB);
					decimalB = decimalB + plus;
					countB--;
				}		
				double decimal= decimalA + decimalB;
				System.out.println("Decimal equivalent: " + decimal);
			}

			else { // user's input does not contains "."
				double decimal = 0;
				int count = 0;
				for (int i = binary.length() - 1; i >= 0; i--) { // converting the integer part of the input
					int digit = (binary.charAt(i))- '0';
					double plus = digit * Math.pow(2,count);
					decimal = decimal + plus;
					count++;
				}
				System.out.println("Decimal equivalent: " + (int)decimal);
			}
		}

	}

	public static boolean checkIfDouble(String number) { 
		return number.contains(".");
	}

	public static boolean isValidNumber(String input) { // check if the decimal input is valid
		int count=0;
		for (int i = 0; i <= input.length()-1; i++) 
		{
			if (input.charAt(i)=='.' ) {
				count++; // counting the number of "."
				if(i==0 || i==input.length()-1) // assumption that the "." cannot be at the start or the end 
					return false;
			}

			if(((input.charAt(i)<'0' || input.charAt(i)>'9') && input.charAt(i)!='.')||count >1)
				return false;
		}
		return true;
	}
	
	public static boolean isValidBinary(String input) { // check if the binary input is valid
		int count=0;
		for (int i = 0; i <= input.length()-1; i++) 
		{
			if (input.charAt(i)=='.' ) {
				count++; // counting the number of "."
				if(i==0 || i==input.length()-1) // assumption that the "." cannot be at the start or the end
					return false;
			}

			if(((input.charAt(i)<'0' || input.charAt(i)>'1') && input.charAt(i)!='.')||count >1)
				return false;
		}
		return true;
	}
}

