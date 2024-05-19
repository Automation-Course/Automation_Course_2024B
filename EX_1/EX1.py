
def decimal_to_binary(decimal): # Convert decimal to binary
    if decimal < 0: # negative number
        return '-' + decimal_to_binary(-decimal)
    if decimal == 0:
        return '0'
    binary = '' # initial value
    while decimal > 0: # valid input
        binary = str(decimal % 2) + binary # get the remainder
        decimal //= 2 # divides the number by two
    return binary

def binary_to_decimal(binary): # Convert binary to decimal
    decimal = 0 # initial value
    power = len(binary) - 1 # the highest power level
    for digit in binary: # go over each digit
        if digit == '1':
            decimal += 2 ** power # get the relevant number by the power level
        elif digit != '0': # if the digit is not 1 or 0
            print("The input number is not valid, please try again")
            return None
        power -= 1 # lower the power
    return decimal

print("Hello to conversion calculator, please choose the conversion type you would like to use")
main_input = True
while main_input == True:
    choose_input = input("Menu:\n1 - convert from binary to decimal\n2 - convert from decimal to binary\n3- End\n")

    if choose_input == '1': # binary to decimal
        binary_choose = True
        while binary_choose == True:
            binary_input = input("Enter a binary number: ")
            decimal_output = binary_to_decimal(binary_input) # use the function to convert
            if decimal_output is not None:
                binary_choose = False # ends the loop
                print("The decimal equivalent is:", decimal_output)

    elif choose_input == '2': # decimal to binary
        decimal_choose = True
        while decimal_choose == True:
            decimal_input = input("Enter a decimal number: ")
            if decimal_input.isdigit(): # check if the input in a number
                binary_output = decimal_to_binary(int(decimal_input))
                decimal_choose = False # ends the loop
                print("The binary equivalent is:", binary_output)
            else:
                decimal_choose = True
                print("The input number is not valid, please try again")

    elif choose_input == '3': # End option
        print("Thank you for using the calculator, see you next time")
        main_input = False
    else:
        print("The input must be 1-3, please choose again")