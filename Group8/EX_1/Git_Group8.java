
import java.util.Scanner;

 class NumberConverter
{
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome our Number Converter!!!");

       while (true)
       {
            int choice; // input
            do
            {
                System.out.println("Choose conversion:"); //////////////// main menu ////////////////
                System.out.println("1. Binary to Decimal");
                System.out.println("2. Decimal to Binary");
                while (!scanner.hasNextInt())     //check if the next input represents an integer value
                {
                    System.out.println("Invalid choice! Please enter 1 or 2:");
                    scanner.next();
                    System.out.println("Choose conversion:");
                System.out.println("1. Binary to Decimal");
                System.out.println("2. Decimal to Binary");
                }
                choice = scanner.nextInt();
                if (choice != 1 && choice != 2) {
                    System.out.println("Invalid choice! Please enter 1 or 2:");
                }
            } while (choice != 1 && choice != 2);
          
            switch (choice) //options :
            {
                case 1: ////////////////////////// Change Binary to Decimal option ////////////////////////
                    System.out.print("Enter positive binary number (or 'M' to return to menu): ");
                    String binaryStr; //The binary input
                    boolean isValidBinary;
                    do {
                        binaryStr = scanner.next();
                        if (binaryStr.equalsIgnoreCase("M")) //return to menu
                        {
                            break;
                        }
                        isValidBinary = isBinary(binaryStr);
                        if (!isValidBinary || !containsNonZeroOrOne(binaryStr)) 
                        	// Checks that the binary input is indeed binary (functions)
                        {
                            System.out.println("Invalid binary number! Please enter a binary number consisting of 0s and 1s only.");
                            System.out.print("Enter a valid binary number (or 'M' to return to menu): ");
                        }
                       }
                    while (!isValidBinary || !containsNonZeroOrOne(binaryStr)); // good input
                    if (!binaryStr.equalsIgnoreCase("M"))
                    {
                        double decimalIrrational = binaryToDecimalIrrational(binaryStr); //The conversion (function)
                        if (Math.abs(decimalIrrational) < 1e-6) // if the convert output is close to 0
                        {
                            System.out.println("Decimal equivalent: 0"); // return 0
                        } else if (Math.abs(decimalIrrational - (int) decimalIrrational) < 1e-6) 
                        	//Checks whether the decimal part of the convert output is close to 0
                        {
                            System.out.println("Decimal equivalent: " + (int) decimalIrrational); 
                            // If so, will return the number rounded down
                        }
                        else{
                            System.out.printf("Decimal equivalent: %.6f\n", decimalIrrational); 
                            // If neither of the above conditions is met, prints the convert output with six decimal places
                        }
                        System.out.println(" ");

                    }
                    break;
                   
                case 2: ////////////////////////// Change Decimal to Binary option ////////////////////////
                    System.out.print("Enter positive decimal number (or 'M' to return to menu): ");
                    double decimalInput;  //The decimal input
                    boolean flag =true;
                    while (flag)
                    {
                    	while (!scanner.hasNextDouble() ) // Checks that the decimal input is indeed decimal
                        {
                            System.out.println("Invalid input! Please enter a valid decimal number:");
                            scanner.next();
                        }
                    	 decimalInput = scanner.nextDouble();
                         String binaryOutput = decimalToBinaryIrrational(decimalInput); //The conversion (function)
                         if(binaryOutput.charAt(0) == '-') // Checks that the decimal input is not negative
                         {
                         	System.out.println("Invalid input! Please enter a valid decimal number:");
                         	flag = true; // not good input, try again
                         }
                         else
                         {
                        	 System.out.println("Binary equivalent: " + binaryOutput); // print good input
                        	 flag = false;
                         }  
                    }
                default:
                    System.out.println("Invalid choice!");
            }
        }
    }
/////////////////////////////////////////////////////  functions:  /////////////////////////////////////////////////
 
//////// A function that converts a number in binary representation to a number in decimal representation ////////
    public static double binaryToDecimalIrrational(String binaryStr)
    {
        double decimal = 0;
        int sign = 1;
        if (binaryStr.charAt(0) == '-') 
        {
            sign = -1;
            binaryStr = binaryStr.substring(1); // Remove the '-' sign
        }
        int dotIndex = binaryStr.indexOf('.');
        String integerPart;
        String fractionalPart = "";
        if (dotIndex != -1)
        {
            integerPart = binaryStr.substring(0, dotIndex);
            fractionalPart = binaryStr.substring(dotIndex + 1);
        }
        else{
            integerPart = binaryStr;
        }
        for (int i = 0; i < integerPart.length(); i++)
        {
            int digit = integerPart.charAt(i) - '0';
            decimal += digit * Math.pow(2, integerPart.length() - i - 1);
        }
        for (int i = 0; i < fractionalPart.length(); i++)
        {
            int digit = fractionalPart.charAt(i) - '0';
            decimal += digit * Math.pow(2, -(i + 1));
        }
        return sign * decimal;
    }

////////A function that converts a number in decimal representation to a number in binary representation ////////
    public static String decimalToBinaryIrrational(double decimal)
    {
        StringBuilder binary = new StringBuilder();
        if (decimal < 0) // Situation where the input is negative
        {
            binary.append("-");
            decimal = -decimal; // Convert to positive for conversion
        }
        int integerPart = (int) decimal; //the whole part
        double fractionalPart = decimal - integerPart; //the decimal part

    // Convert integer part to binary
    StringBuilder integerBinary = new StringBuilder();
    while (integerPart > 0) {
        int remainder = integerPart % 2;
        integerBinary.insert(0, remainder); // Insert the remainder at the beginning of the string
        integerPart /= 2;
    }
       
        StringBuilder fractionalBinary = new StringBuilder();
        int count = 0;
        while (fractionalPart != 0 && count < 6) //up to 6 binary digits for the fractional part
        {
            fractionalPart *= 2;
            int bit = (int) fractionalPart; 
            //This line casts the fractional part to an integer, effectively truncating it to get the next binary digit (0 or 1).
            fractionalBinary.append(bit);
            if (fractionalPart >= 1)
            {
                fractionalPart -= 1;
            }
            count++;
        }
        return binary.append(integerBinary).append('.').append(fractionalBinary).toString();
    }
   
//////// A function that checks that the binary input is indeed binary - consists of 0 or 1 or a decimal point ////////
    public static boolean isBinary(String str)
    {
        for (char c : str.toCharArray())
        {
            if (c != '0' && c != '1' && c != '.')
            {
                return false; // not binary input
            }
        }
        return true; // binary input
    }

////////A function that checks that the binary input does indeed make sense - does not contain only dots ////////
    public static boolean containsNonZeroOrOne(String str)
    {
        for (char c : str.toCharArray())
        {
            if (c == '0' || c == '1')
            {
                return true; // Good input
            }
        }
        return false; // Not good input
    }
   
   
}
       