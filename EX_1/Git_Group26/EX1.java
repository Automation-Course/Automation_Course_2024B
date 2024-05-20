import java.util.Scanner;


public class calculator {
	static Scanner sc = new Scanner(System.in);
	
	public static boolean isBinary(String binary) {
        for (int i = 0; i < binary.length(); i++) {
            char c = binary.charAt(i);
            if (c != '0' && c != '1') {
                return false;
            }
        }
        return true;
    }
	
	public static int binaryToDecimal(String binary) {
        int decimal = 0;
        int power = 0;
        for (int i = binary.length() - 1; i >= 0; i--) {
            int digit = binary.charAt(i) - '0'; // Convert character to integer
            decimal += digit * Math.pow(2, power);
            power++;
        }
        return decimal;
    }
	
	
	
	public static boolean isDecimal(String decimal) {
        for (int i = 0; i < decimal.length(); i++) {
            char c = decimal.charAt(i);
            if (c < '0' || c > '9') {
                return false;
            }
        }
        return true;
    }

	
	 public static String decimalToBinary(String demicalNumber) {
		 int decimalInt = Integer.parseInt(demicalNumber);
	        if (decimalInt == 0) {
	            return "0";
	        }
	        StringBuilder binary = new StringBuilder();
	        while (decimalInt > 0) {
	            int remainder = decimalInt % 2;
	            binary.insert(0, remainder);
	            decimalInt = decimalInt / 2;
	        }
	        return binary.toString();
	    }


	public static void main(String[] args) {
		// TODO Auto-generated method stub
		boolean fcontinue = true;
		do {		
			System.out.println("0. End Program");
			System.out.println("1. Binary to decimal calculator");
			System.out.println("2. Decimal to binary calculator");
			System.out.println("Please enter a digit (0-2)>");

			int choice = sc.nextInt();//get user choice
			
			switch (choice) {
			
			case 0:{System.out.println("End Program. Goodbye!"); //exit
			fcontinue = false;
			break;}
			
			case 1: {  System.out.println("Enter binary number: "); //user choose 1
            String binaryNumber = sc.next();     
            if (isBinary(binaryNumber)) {
            	System.out.println("Decimal: " + binaryToDecimal(binaryNumber)); }
            else {System.out.println("Error: is'nt a binary number");}
                break;
            }
			
			case 2: {  System.out.println("Enter demical number: "); //user choose 1
            String demicalNumber = sc.next();     
            if (isDecimal(demicalNumber)) {
            	System.out.println("Binary: " + decimalToBinary(demicalNumber)); }
            else {System.out.println("Error: is'nt a demical number");}
                break;
            }
			default: {System.out.println("Invalid menu input"); // The user has selected a digit that is not in the desired range 
			break;}
			}
		} while (fcontinue); 
			
	}

}