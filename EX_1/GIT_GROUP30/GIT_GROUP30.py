def decimal_to_binary(decimal_number):
    """Convert a decimal number to binary representation without using built-in functions."""
    if decimal_number == 0:
        return '0'
    binary = ''
    while decimal_number > 0:
        remainder = decimal_number % 2
        binary = str(remainder) + binary
        decimal_number = decimal_number // 2
    return binary


def binary_to_decimal(binary_string):
    """Convert a binary string to decimal representation without using built-in functions."""
    for digit in binary_string:
        if digit != '0' and digit != '1':  # Check if the input contains only 0s and 1s
            raise ValueError("Invalid input: Please enter a binary number (containing only 0s and 1s).")
    decimal_number = 0
    power = len(binary_string) - 1
    for digit in binary_string:
        decimal_number += int(digit) * (2 ** power)
        power -= 1
    return decimal_number

def main():
    print("Welcome to the Decimal and Binary Converter!")
    while True:
        print("1. Convert Decimal to Binary")
        print("2. Convert Binary to Decimal")
        print("3. Exit")
        choice = input("Please enter your choice (1, 2, or 3): ")

        if choice == '1':
            try:
                decimal_number = int(input("Enter a decimal number: "))
                print("The binary representation is:", decimal_to_binary(decimal_number))
            except ValueError:
                print("Invalid input! Please enter a valid decimal number.")
        elif choice == '2':
            binary_string = input("Enter a binary number (e.g., 1010): ")
            try:
                print("The decimal representation is:", binary_to_decimal(binary_string))
            except ValueError:
                print("Invalid input! Please enter a valid binary number.")
        elif choice == '3':
            print("Exiting the program.")
            break
        else:
            print("Invalid choice, please enter 1, 2, or 3.")

        print("\n")

main()




