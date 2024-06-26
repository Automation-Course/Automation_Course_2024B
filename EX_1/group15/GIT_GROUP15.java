import java.util.Scanner;

public class Group15 {

    // Function to check if a string represents a valid binary number
    public static boolean isValidBinary(String binary) {
        boolean hasDot = false;
        for (char c : binary.toCharArray()) {
            if (c != '0' && c != '1') { // Check if character is not '0' or '1'
                if (c == '.' && !hasDot) { // Allow only one dot in the string
                    hasDot = true;
                } else {
                    return false; // Return false for any other characters
                }
            }
        }
        return true; // Return true if all characters are valid
    }

    // Function to check if a string represents a valid decimal number (including floating-point and fractions)
    public static boolean isValidDecimal(String decimal) {
        boolean hasDot = false;
        boolean hasSlash = false;
        for (char c : decimal.toCharArray()) {
            if (!Character.isDigit(c)) { // Check if character is not a digit
                if (c == '.' && !hasDot) { // Allow only one dot
                    hasDot = true;
                } else if (c == '/' && !hasSlash) { // Allow only one slash for fractions
                    hasSlash = true;
                } else {
                    return false; // Return false for any other characters
                }
            }
        }
        return true; // Return true if all characters are valid
    }

    // Function to convert binary to decimal (floating-point)
    public static double binaryToDecimal(String binary) {
        int pointIndex = binary.indexOf('.'); // Find the position of the dot
        if (pointIndex == -1) { // If no dot, set pointIndex to the length of the string
            pointIndex = binary.length();
        }
        double decimal = 0;
        int power = 0;
        // Convert the part before the dot
        for (int i = pointIndex - 1; i >= 0; i--) {
            if (binary.charAt(i) == '1') {
                decimal += Math.pow(2, power);
            }
            power++;
        }
        power = -1;
        // Convert the part after the dot
        for (int i = pointIndex + 1; i < binary.length(); i++) {
            if (binary.charAt(i) == '1') {
                decimal += Math.pow(2, power);
            }
            power--;
        }
        return decimal; // Return the computed decimal value
    }

    // Function to convert decimal to binary (floating-point)
    public static String decimalToBinary(double decimal) {
        long wholePart = (long) decimal; // Get the whole number part
        double fractionalPart = decimal - wholePart; // Get the fractional part
        String wholePartBinary = Long.toBinaryString(wholePart); // Convert whole part to binary
        StringBuilder fractionalPartBinary = new StringBuilder();
        // Convert fractional part to binary
        while (fractionalPart != 0) {
            fractionalPart *= 2;
            if (fractionalPart >= 1) {
                fractionalPartBinary.append('1');
                fractionalPart -= 1;
            } else {
                fractionalPartBinary.append('0');
            }
            // Limit the length of the fractional part to avoid infinite loop
            if (fractionalPartBinary.length() > 10) {
                break;
            }
        }
        return wholePartBinary + (fractionalPartBinary.length() > 0 ? "." + fractionalPartBinary : ""); // Return the binary equivalent
    }

    // Function to convert a fraction string to a decimal value
    public static double fractionToDecimal(String fraction) {
        String[] parts = fraction.split("/"); // Split the fraction string at the slash
        if (parts.length == 2) {
            double numerator = Double.parseDouble(parts[0]); // Parse the numerator
            double denominator = Double.parseDouble(parts[1]); // Parse the denominator
            return numerator / denominator; // Return the decimal value of the fraction
        } else {
            return Double.parseDouble(fraction); // If no slash, parse the whole string as a decimal
        }
    }

    // Function to check if a string represents a valid whole number
    public static boolean isValidOption(String option) {
        return option.equals("0") || option.equals("1") || option.equals("2"); // Check if option is 0, 1, or 2
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String number = "";
        while (!number.equals("0")) { // Loop until the user chooses to end the program
            System.out.println("0. End Program");
            System.out.println("1. Binary to Decimal");
            System.out.println("2. Decimal to Binary");
            System.out.print("Choose an option: ");
            number = scanner.nextLine();

            if (!isValidOption(number)) { // Validate the menu option input
                System.out.println("Invalid option. Try again.");
                continue; // Skip to the next iteration to re-display the menu
            }

            switch (number) {
                case "0":
                    System.out.println("Exiting program...");
                    break;
                case "1":
                    System.out.print("Enter a binary number: ");
                    String binary = scanner.nextLine();
                    if (!isValidBinary(binary)) { // Validate binary input
                        System.out.println("Invalid binary number.");
                    } else {
                        double decimal = binaryToDecimal(binary); // Convert binary to decimal
                        System.out.println("Decimal equivalent: " + decimal);
                    }
                    break;
                case "2":
                    System.out.print("Enter a decimal number: ");
                    String decimalStr = scanner.nextLine();
                    if (!isValidDecimal(decimalStr)) { // Validate decimal input
                        System.out.println("Invalid decimal number.");
                    } else {
                        double decimalNumber;
                        if (decimalStr.contains("/")) { // Check if input is a fraction
                            decimalNumber = fractionToDecimal(decimalStr); // Convert fraction to decimal
                        } else {
                            decimalNumber = Double.parseDouble(decimalStr); // Parse the decimal number
                        }
                        String binaryEquivalent = decimalToBinary(decimalNumber); // Convert decimal to binary
                        System.out.println("Binary equivalent: " + binaryEquivalent);
                    }
                    break;
                default:
                    System.out.println("Invalid option. Please choose again."); // Handle invalid options
            }
        }
        scanner.close(); // Close the Scanner to release resources
    }
}
