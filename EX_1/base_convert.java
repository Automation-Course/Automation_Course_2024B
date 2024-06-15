package convertor;

import java.util.Scanner;

public class base_convert
{
    // Method to convert decimal number to binary
	public static String decimalToBinary(double decimalNumber)
	{
	    if (decimalNumber == 0) {
	        return "0";
	    }
	    int beforePoint = (int) decimalNumber;
	    double afterPoint = decimalNumber - beforePoint;
	    StringBuilder integralBinary = new StringBuilder();
	    // Convert before part to binary
	    while (beforePoint > 0) {
	        int remainder = beforePoint % 2;
	        integralBinary.insert(0, remainder); 
	        beforePoint /= 2;
	    }
	    // If no before part, insert a '0' at the beginning
	    if(integralBinary.length()==0)
	    {
	    	integralBinary.insert(0,0);
	    }
	    StringBuilder fractionalBinary = new StringBuilder();
	    // Convert after part to binary
	    while (afterPoint> 0)
	    {
	        afterPoint *= 2;
	        if (afterPoint >= 1)
	        {
	            fractionalBinary.append('1');
	            afterPoint -= 1;
	        } else {
	            fractionalBinary.append('0');
	        }
	    }
	    StringBuilder binary = new StringBuilder(integralBinary);
	    // If after part exists, append it to the binary
	    if (fractionalBinary.length() > 0)
	    {
	        binary.append('.'); 
	        binary.append(fractionalBinary); 
	    }
	    return binary.toString();
	}
	// Method to convert binary number to decimal
	public static double binaryToDecimal(String binary)
	{
        int indexOfDecimalPoint = binary.indexOf('.');
        int beforPint = 0;
        double afterPoint = 0;
        int end;
        // Determine the end index based on the presence of a decimal point
        if (indexOfDecimalPoint == -1)
        {
            end = binary.length();
        } else 
        {
            end = indexOfDecimalPoint;
        }
        // Convert before part of binary to decimal
        for (int i = end - 1, j = 0; i >= 0; i--, j++)
        {
        	beforPint += (binary.charAt(i) - '0') * Math.pow(2, j);
        }
        // Convert after part of binary to decimal
        if (indexOfDecimalPoint != -1) {
            for (int i = indexOfDecimalPoint + 1, j = -1; i < binary.length(); i++, j--)
            {
            	afterPoint += (binary.charAt(i) - '0') * Math.pow(2, j);
            }
        }
        return beforPint + afterPoint;
    }
	// Method to check if a string represents a valid decimal number
	public static boolean isValidDecimalNumber(String number) {
	    if (number.isEmpty()) {
	        return false;
	    }
	    int countDecimalPoint = 0;
	    for (int i = 0; i < number.length(); i++) {
	        char isNum = number.charAt(i);
	        if (isNum == '.')
	        {
	            countDecimalPoint++;
	            if (countDecimalPoint > 1) 
	            {
	                return false;
	            }
	        } 
	        else if (!Character.isDigit(isNum))
	        {
	            return false;
	        }
	    }
	    return true;
	}
	 // Method to check if a string represents a valid binary number
	public static boolean isValidBinary(String binaryNumber)
	{
	    if (binaryNumber.isEmpty()) {
	        return false;
	    }
	    for (int i = 0; i < binaryNumber.length(); i++)
	    {
	        char valid = binaryNumber.charAt(i);
	        if (valid != '0' && valid != '1' && valid != '.')
	        {
	            return false;
	        }
	    }
	    int countDecimalPoint = 0;
	    for (int i = 0; i < binaryNumber.length(); i++)
	    {
	        if (binaryNumber.charAt(i) == '.')
	        {
	            countDecimalPoint++;
	            if (countDecimalPoint > 1) 
	            {
	                return false; 
	            }
	        }
	    }
	    return true;
	}
	 // Main method
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		boolean exit = false;

		while (!exit) 
		{
			System.out.println("Base Conversion Menu:");
			System.out.println("1. Decimal to Binary");
			System.out.println("2. Binary to Decimal");
			System.out.println("3. Exit");

			System.out.print("Choose an option: ");
			String choice = scanner.nextLine();
			switch (choice) 
			{
			case "1":
				System.out.print("Enter decimal number: ");
				String decimalNumber = scanner.nextLine();
				 if(!isValidDecimalNumber(String.valueOf(decimalNumber)))
				{
					System.out.println("Invalid input.");
				}
				 else
				 {
					String binaryResult = decimalToBinary(Double.parseDouble(decimalNumber));
					System.out.println("Binary: " + binaryResult);
				 }
				break;
			case "2":
				System.out.print("Enter binary number: ");
				String binaryNumber = scanner.nextLine();
				
				if (!isValidBinary(binaryNumber)) 
				{
					System.out.println("Invalid input. Binary number must contain only 0s and 1s.");
					
				} else
				{
					double decimalResult = binaryToDecimal(binaryNumber);
					System.out.println("Decimal: " + decimalResult);
				}
				break;
			case "3":
				exit = true;
				System.out.println("Exiting...");
				break;
			default:
				System.out.println("Invalid option. Please choose again.");
			}
		}
		scanner.close();
	}
}


