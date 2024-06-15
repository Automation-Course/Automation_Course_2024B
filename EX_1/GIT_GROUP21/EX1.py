1import math

# Function to convert decimal number to binary
def dec_to_bin(decimal):
    # Check if the decimal number is an integer
    if decimal.is_integer():
        integer_part = int(decimal)
        if integer_part == 0:
            return '000'
        binary_str = ''
        # Convert the integer part to binary
        while integer_part > 0:
            binary_str = str(integer_part % 2) + binary_str
            integer_part //= 2
         # Ensure the binary string has at least 3 digits
        if len(binary_str) < 3:
            binary_str = '0' * (3 - len(binary_str)) + binary_str
        return binary_str
    else:
        int_part = int(decimal)
        frac_part = decimal - int_part
        int_bin = ''
        if int_part == 0:
            int_bin = '000'
        # Convert the integer part to binary
        else:
            while int_part > 0:
                int_bin = str(int_part % 2) + int_bin
                int_part //= 2
            # Ensure the binary string has at least 3 digits
            if len(int_bin) < 3:
                int_bin = '0' * (3 - len(int_bin)) + int_bin
        frac_bin = ''
        # Convert the fractional part to binary
        while frac_part != 0:
            frac_part *= 2
            if frac_part >= 1:
                frac_bin += '1'
                frac_part -= 1
            else:
                frac_bin += '0'
            if len(frac_bin) >= 32:
                break
        return int_bin + '.' + frac_bin

# Function to convert binary number to decimal
def bin_to_dec(binary):
    # Check if the binary number is valid
    if not all(char in '01.' for char in binary):
        print("Invalid binary number. Please enter a valid binary number.")
        return None

    if '.' in binary:
        int_part, frac_part = binary.split('.')
    else:
        int_part = binary
        frac_part = ''

    int_value = 0
    # Convert the integer part from binary to decimal
    for i, digit in enumerate(reversed(int_part)):
        if digit == '1':
            int_value += 2 ** i

    frac_value = 0
    # Convert the fractional part from binary to decimal
    for i, digit in enumerate(frac_part):
        if digit == '1':
            frac_value += 2 ** -(i + 1)

    return int_value + frac_value

# Main function to run the calculator
def main():
    while True:
        print("Choose an option:")
        print("1. Convert decimal number to binary")
        print("2. Convert binary number to decimal")
        print("3. Exit")
        choice = input("Enter the option you want to perform: ")

        if choice == '1':
            decimal_input = input("Enter a decimal number: ").strip()
            if not decimal_input:
                print("Invalid input. Please enter a valid decimal number.")
            else:
                try:
                    decimal = float(decimal_input)
                    if decimal < 0:
                        print("Invalid option, please try again.")
                    else:
                        print("The binary number is:", dec_to_bin(decimal))
                except ValueError:
                    print("Invalid input. Please enter a valid decimal number.")

        elif choice == '2':
            binary = input("Enter a binary number: ")
            decimal = bin_to_dec(binary)
            if decimal is not None:
                print("The decimal number is:", decimal)

        elif choice == '3':
            print("Thank you for using the calculator.")
            break

        else:
            print("Invalid option, please try again.")

# Entry point of the script
if __name__ == "__main__":
    main()