import java.util.Scanner;

public class calculation_bin {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        boolean continueProgram = true;

        while (continueProgram) {
            System.out.println("Main Menu:");
            System.out.println("1. Binary to Decimal");
            System.out.println("2. Decimal to Binary");
            System.out.println("3. Exit");
            String choice = scanner.next();

            switch (choice) {
                case "1":
                    System.out.println("Enter a binary number:");
                    String binaryInput = scanner.next();
                    if (!isValidBinary(binaryInput)) {
                        System.out.println("Invalid input, please enter a binary number only (0s and 1s).");
                        break;
                    }
                    int decimalResult = binaryToDecimal(binaryInput);
                    System.out.println("The decimal number is: " + decimalResult);
                    break;
                case "2":
                    System.out.println("Enter a decimal number:");
                    if (!scanner.hasNextInt()) {
                        System.out.println("Invalid input, please enter a valid decimal number.");
                        scanner.next(); // Clear the invalid input from the scanner
                        break;
                    }
                    int decimalInput = scanner.nextInt();
                    if (decimalInput < 0) {
                        System.out.println("Negative numbers are not supported. Please enter a positive number.");
                        break;
                    }
                    String binaryResult = decimalToBinary(decimalInput);
                    System.out.println("The binary number is: " + binaryResult);
                    break;
                case "3":
                    System.out.println("Exiting program...");
                    continueProgram = false; // Exit the loop and terminate the program
                    break;
                default:
                    System.out.println("Invalid choice. Please enter a number between 1 and 3.");
            }
        }

        scanner.close();
    }

    public static int binaryToDecimal(String binary) {
        int decimal = 0;
        int n = binary.length();
        for (int i = 0; i < n; i++) {
            if (binary.charAt(i) == '1') {
                decimal += Math.pow(2, n - 1 - i);
            }
        }
        return decimal;
    }

    public static String decimalToBinary(int decimal) {
        StringBuilder binary = new StringBuilder();

        do {
            binary.insert(0, decimal % 2);
            decimal /= 2;
        } while (decimal > 0);

        return binary.toString();
    }

    public static boolean isValidBinary(String binary) {
        if (binary.isEmpty()) {
            return false;
        }

        for (char ch : binary.toCharArray()) {
            if (ch != '0' && ch != '1') {
                return false;
            }
        }

        return true;
    }
}
