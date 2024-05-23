package group25;

import java.util.Scanner;
public class binaryDecimalCalculator {

    public static String convertDecimalToBinary(int decimalNumber) {
        return Integer.toBinaryString(decimalNumber);
    }

   
    public static int convertBinaryToDecimal(String binaryNumber) throws IllegalArgumentException {
        if (!binaryNumber.matches("[01]+")) {
            throw new IllegalArgumentException("Input must be a binary string containing only '0' and '1'.");
        }
        return Integer.parseInt(binaryNumber, 2);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Welcome to Group 25 Binary-Decimal Converter!");

        while (true) {
            System.out.println("\nMenu:");
            System.out.println("1. Convert Binary to Decimal");
            System.out.println("2. Convert Decimal to Binary");
            System.out.println("3. Exit");
            System.out.print("Select an option (1, 2, or 3): ");

            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    System.out.print("Enter a binary number: ");
                    String binaryInput = scanner.nextLine();
                    try {
                        int decimalResult = convertBinaryToDecimal(binaryInput);
                        System.out.println("Binary " + binaryInput + " converts to Decimal " + decimalResult);
                    } catch (IllegalArgumentException e) {
                        System.out.println("Error: " + e.getMessage());
                    }
                    break;

                case "2":
                    System.out.print("Enter a decimal number: ");
                    try {
                        int decimalNumber = Integer.parseInt(scanner.nextLine());
                        String binaryResult = convertDecimalToBinary(decimalNumber);
                        System.out.println("Decimal " + decimalNumber + " converts to Binary " + binaryResult);
                    } catch (NumberFormatException e) {
                        System.out.println("Error: Input must be a valid integer.");
                    }
                    break;

                case "3":
                    System.out.println("Thank you for using the calculator. Goodbye!");
                    scanner.close();
                    return;

                default:
                    System.out.println("Invalid option. Please choose 1, 2, or 3.");
            }
        }

}}
