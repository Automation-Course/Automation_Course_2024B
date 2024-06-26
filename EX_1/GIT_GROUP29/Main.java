import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args)
    {
        Scanner scanner = new Scanner(System.in);
        int choice;

        do {
            System.out.println("Choose an option:");
            System.out.println("1. Convert from binary to decimal");
            System.out.println("2. Convert from decimal to binary");
            System.out.println("0. Exit");

            System.out.print("Enter your choice: ");
            choice = scanner.nextInt();

            switch (choice) {
                case 1:
                    convertFromBinaryToDecimal();
                    break;
                case 2:
                    convertFromDecimalToBinary();
                    break;
                case 0:
                    System.out.println("Exiting the program...");
                    break;
                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        } while (choice != 0);
    }

    public static void convertFromBinaryToDecimal() {
        String number = getBinaryNumber();
        String Decimalnumber = binaryToDecimal(number);
        System.out.println("Decimal value is "+Decimalnumber);
    }
    public static void convertFromDecimalToBinary() {
        long number = getDecimalNumber();
        String Binarynumber = decimalToBinary(number);
        System.out.println("binary value is "+Binarynumber);
    }

    public static String getBinaryNumber() {
        Scanner scanner = new Scanner(System.in);
        String binaryStr;
        // Get the binary number from the user
        do {
            System.out.print("Enter a binary number: ");
            binaryStr = scanner.nextLine();
            if (!isNumeric(binaryStr)) {
                System.out.println("That's not a number!");
                continue;
            }
            if (binaryStr.contains(".")) {
                System.out.println("Fractional numbers are not allowed. Please enter an integer.");
                continue;
            }
            if (binaryStr.charAt(0) == '-') {
                System.out.println("Negative numbers are not allowed. Please enter a non-negative binary number.");
                continue;
            }
            if (!isBinary(binaryStr)) {
                System.out.println("Input is not a binary number. Please enter a valid binary number.");
                continue;
            }
            return binaryStr; // Return the valid binary number
        } while (true); // Keep looping until valid input is received
    }

    public static boolean isNumeric(String str) {
        // Check if the string represents a numeric value
        if (str == null || str.isEmpty()) {
            return false;
        }
        // Allow for a single leading negative sign
        if (str.charAt(0) == '-') {
            str = str.substring(1);
        }
        boolean hasDecimalPoint = false;
        for (char c : str.toCharArray()) {
            if (!Character.isDigit(c)) {
                if (c == '.' && !hasDecimalPoint) {
                    hasDecimalPoint = true;
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    public static boolean isBinary(String str) {
        // Check if the string represents a binary number
        for (char c : str.toCharArray()) {
            if (c != '0' && c != '1') {
                return false;
            }
        }
        return true;
    }




    public static String binaryToDecimal(String binary) {
        long decimal = 0;
        int position = 0;
        for (int i = binary.length() - 1; i >= 0; i--) {
            // Get the digit at the current position
            int digit = binary.charAt(i) - '0';
            // Add the digit multiplied by 2 raised to its position
            decimal += digit * Math.pow(2, position);
            // Move to the next position
            position++;
        }
        return Long.toString(decimal);
    }


    public static long getDecimalNumber() {
        Scanner scanner = new Scanner(System.in);
        long decimalNumber;
        // Get the decimal number from the user
        do {
            System.out.print("Enter a decimal number: ");
            while (!scanner.hasNextLong()) {
                System.out.println("That's not a valid");
                System.out.print("Enter a decimal number: ");
                scanner.next(); // Clear the invalid input
            }
            decimalNumber = scanner.nextLong();
            if (decimalNumber < 0) {
                System.out.println("Negative numbers are not allowed. Please enter a non-negative decimal number.");
            }
        } while (decimalNumber < 0);
        return decimalNumber; // Return the entered decimal number
    }



    public static String decimalToBinary(long decimal) {
        // Check if the input decimal number is zero
        if (decimal == 0) {
            return "0";
        }

        StringBuilder binary = new StringBuilder();

        // Convert the decimal number to its binary equivalent
        while (decimal > 0) {
            // Get the remainder when dividing by 2 (binary digit)
            long digit = decimal % 2;
            // Append the binary digit to the result
            binary.insert(0, digit);
            // Divide the decimal number by 2 for the next iteration
            decimal /= 2;
        }

        return binary.toString(); // Return the binary representation as a string
    }
}