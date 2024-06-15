def is_Binary(bin):  # Validation for binary number
    if '.' in bin:
        parts = bin.split('.') #split the input to parts after '.'
        if len(parts) > 2: #if there is more then 2 parts in the string
            return False
        return all(part == '' or all(digit in '01' for digit in part) for part in parts)
    return all(digit in '01' for digit in bin) #check bin if there is no dot


def is_Decimal(dec):  # Validation for decimal number
    if '.' in dec:
        parts = dec.split('.')  #split the input to parts after '.'
        if len(parts) > 2: #if there is more then 2 parts in the string
            return False
        return all(part.isdigit() for part in parts)
    return dec.isdigit()  #check dec if there is no dot


def Binary_to_Decimal(binary):
    if '.' in binary:
        integer_part, fractional_part = binary.split('.') #split the input to parts after '.'
        answer_decimal = 0
        power = len(integer_part) - 1
        for digit in integer_part:  #calculate the decimal value of the integer part
            answer_decimal += int(digit) * (2 ** power)
            power -= 1
        power = -1
        for digit in fractional_part:  #calculate the decimal value of the fractional part
            answer_decimal += int(digit) * (2 ** power)
            power -= 1
        return answer_decimal
    else:
        integer_part = binary #calculate the integer part if there is no fractional part
        answer_decimal = 0
        power = len(integer_part) - 1
        for digit in integer_part:
            answer_decimal += int(digit) * (2 ** power)
            power -= 1
        return answer_decimal


def Decimal_to_Binary(decimal):
    if '.' in decimal:
        integer_part, fractional_part = decimal.split('.') #split the input to parts after '.'
        integer_part = int(integer_part)
        binary_integer = ""
        while integer_part > 0: #calculate the integer part
            remainder = integer_part % 2
            binary_integer = str(remainder) + binary_integer
            integer_part //= 2
        if binary_integer == "":
            binary_integer = "0"

        fractional_part = float('0.' + fractional_part) #calculate the fractional part
        binary_fractional = ""
        while fractional_part > 0 and len(binary_fractional) < 10:  # limit the length of fractional part
            fractional_part *= 2
            bit = int(fractional_part)
            if bit == 1:
                fractional_part -= bit
            binary_fractional += str(bit)

        return binary_integer + '.' + binary_fractional
    else:
        decimal = int(decimal)
        binary = ""
        while decimal > 0:
            remainder = decimal % 2
            binary = str(remainder) + binary
            decimal //= 2
        if binary == "":
            binary = "0"
        return binary

while True:
    print("Welcome to Binary-Decimal calculator!\n"
    "which number you want to calculate?\n"
    "Binary -> Decimal (1)\n"
    "Decimal -> Binary (2)\n"
    "Quit (3)")
    user_menu = input("Enter your choose:\n")

    if user_menu == "1":
        while True:
            Binary_input = input("Enter Binary number: ")
            if is_Binary (Binary_input):
                Decimal_output = Binary_to_Decimal (Binary_input)
                print(Binary_input ,"is decimal equivalent to -",Decimal_output)
                break
            else:
                print("Invalid input. Please enter a binary number.")

    elif user_menu == "2":
        while True:
            Decimal_input = input("Enter Decimal number: ")
            if is_Decimal (Decimal_input):
                Binary_output = Decimal_to_Binary (Decimal_input)
                print(Decimal_input ,"is binary equivalent to -",Binary_output)
                break
            else:
                print("Invalid input. Please enter a decimal number.")

    elif  user_menu== "3":
        break

    else:
        print("Invalid input. choose again")

print("Game ended.\nsee you next time :)")