

def user_interface():
    """
    User interface for binary and decimal conversion.

    Returns:
    - None.
    """
    while True:
        print("")
        print("Please select an option:")
        print("1. Convert decimal to binary")
        print("2. Convert binary to decimal")
        print("3. Quit")
        choice = input("Enter your choice: ")


        if choice == "1":
            decimal_num = input("Enter a decimal number: ")
            print("")
            decimal_to_binary(decimal_num)
        elif choice == "2":
            binary_num = input("Enter a binary number: ")
            print("")
            binary_to_decimal(binary_num)
        elif choice == "3":
            print("")
            print("Exiting the program.")
            break
        else:
            print("")
            print("Invalid choice. Please enter 1, 2, or 3.")




def float_to_binary(dec_num):
    """
    Convert a float to its binary representation.

    Args:
    - dec_num (float): The float number to convert.

    Returns:
    - str: The binary representation of the float number.
    """
    # Extract the sign, integer part, and fractional part of the float
    int_part = abs(int(dec_num))
    frac_part = abs(dec_num) - int_part

    # Convert integer part to binary
    int_binary = ""
    while int_part > 0:
        int_binary = str(int_part % 2) + int_binary
        int_part //= 2

    # Convert fractional part to binary
    frac_binary = ""
    precision = 10  # Set precision for fractional part
    while frac_part != 0 and precision > 0:
        frac_part *= 2
        frac_bit = int(frac_part)
        frac_binary += str(frac_bit)
        frac_part -= frac_bit
        precision -= 1

    return int_binary + "." + frac_binary

def decimal_to_binary(dec_num):
    """
    Convert a decimal number to binary.

    Args:
    - dec_num (str): The decimal number to convert.

    Returns:
    - str: The binary representation of the decimal number.
    """
    if '-' in dec_num:
        if not dec_num.startswith('-') or dec_num.count("-") > 1:
            print("Input not valid. Please provide a decimal number.")
            return

    if dec_num.count(".") > 1:
        print("Input not valid. Please provide a decimal number.")
        return

    if not isinstance(dec_num, str) or not all(char in '-0123456789.' for char in dec_num) or dec_num == '-' or dec_num == '.':
        print("Input not valid. Please provide a decimal number.")
        return

    dec_num = float(dec_num)
    int_part = abs(int(dec_num))
    frac_part = abs(dec_num) - int_part
    if frac_part == 0.0:
        dec_num = int(dec_num)
    elif isinstance(dec_num, float):
        if dec_num < 0:
            print("-" + float_to_binary(dec_num))
        else:
            print(float_to_binary(dec_num))

    if isinstance(dec_num, int):
        sign = ""
        if dec_num == 0:
            print(0)
        if dec_num < 0:
            sign += "-"
        binary_result = ""
        dec_num = abs(dec_num)
        while dec_num > 0:
            binary_result = str(dec_num % 2) + binary_result
            dec_num //= 2
        print(sign + str(binary_result))




def binary_to_decimal(binary_num):
    """
    Convert a binary number to decimal.

    Args:
    - binary_num (str): The binary number to convert.

    Returns:
    - int or str: The decimal representation of the binary number.
    """
    if '-' in binary_num:
        if not binary_num.startswith('-') or binary_num.count("-") > 1:
            print("Input not valid. Please provide a binary number.")
            return

    if binary_num.count(".") > 1:
        print("Input not valid. Please provide a binary number.")
        return

    if not isinstance(binary_num, str) or not all(char in '-01.' for char in binary_num) or binary_num == '-' or binary_num == '.':
        print("Input not valid. Please provide a binary number.")

        return
    # Handle negative binary number
    if binary_num[0] == '-':
        binary_num = binary_num[1:]
        is_negative = True
    else:
        is_negative = False

    # Split binary number into integer and fractional parts
    parts = binary_num.split('.')
    int_part = parts[0]
    frac_part = parts[1] if len(parts) > 1 else ''

    # Convert integer part to decimal
    decimal_result = 0
    power = len(int_part) - 1
    for digit in int_part:
        decimal_result += int(digit) * (2 ** power)
        power -= 1

    # Convert fractional part to decimal
    if frac_part:
        frac_result = 0
        for i, digit in enumerate(frac_part):
            frac_result += int(digit) * (2 ** -(i + 1))
        decimal_result += frac_result

    print(-decimal_result if is_negative else decimal_result)



user_interface()