import java.util.Scanner;

public class Automation1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        boolean continueCalculations = true;

        while (continueCalculations) {
            System.out.print("Enter the base of the number you want to convert (2 or 10): ");
            int base = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            System.out.print("Enter a number: ");
            String input = scanner.nextLine();

            if (base == 10) {
                if (isValidDecimal(input)) {
                    int decimalInput = Integer.parseInt(input);
                    if (decimalInput < 0) {
                        System.out.println("Negative numbers are not supported.");
                    } else {
                        String binary = decimalToBinary(decimalInput);
                        System.out.println("Binary equivalent: " + binary);
                    }
                } else {
                    System.out.println("Invalid decimal number format.");
                }
            } else if (base == 2) {
                if (isValidBinary(input)) {
                    int decimal = binaryToDecimal(input);
                    System.out.println("Decimal equivalent: " + decimal);
                } else {
                    System.out.println("Invalid binary number format.");
                }
            } else {
                System.out.println("Invalid base number. Please enter 2 or 10.");
            }

            System.out.print("Do you want to convert another number? (yes/no): ");
            String choice = scanner.nextLine();
            continueCalculations = choice.equalsIgnoreCase("yes");
        }

        scanner.close();
    }

    // Function to check if the input is a valid decimal number format
    public static boolean isValidDecimal(String input) {
        return input.matches("-?[0-9]+");
    }

    // Function to check if the input is a valid binary number format
    public static boolean isValidBinary(String input) {
        return input.matches("[01]+");
    }

    // Function to convert binary to decimal
    public static int binaryToDecimal(String binary) {
        int decimal = 0;
        int power = 0;

        for (int i = binary.length() - 1; i >= 0; i--) {
            if (binary.charAt(i) == '1') {
                decimal += Math.pow(2, power);
            }
            power++;
        }

        return decimal;
    }

    // Function to convert decimal to binary
    public static String decimalToBinary(int decimal) {
        if (decimal == 0) {
            return "0";
        }

        StringBuilder binary = new StringBuilder();
        while (decimal > 0) {
            int remainder = decimal % 2;
            binary.insert(0, remainder);
            decimal /= 2;
        }

        return binary.toString();
    }
}