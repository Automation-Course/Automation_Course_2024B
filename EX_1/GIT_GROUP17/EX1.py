def numCheckBin(number): # A function to validate the binary number
    for digit in number:
        if digit != '0' and digit != '1': # Allow only 0's and 1's
            return False
    return  True
def convert_base2_to_base10(number): # Binary to Decimal conversion
    decimal = 0 # Initialize the output number
    power = len(number) - 1 # Initialize the power number
    flag=numCheckBin(number)
    while flag==False: # while the input number keeps being invalid
        number=input("Error: Invalid input. Please enter a binary number (0s and 1s) only.")
        flag=numCheckBin(number) # The condition for staying inside the loop depends on the new input
    for digit in number:
        decimal += int(digit) * (2 ** power)  #The mathematical calculations for the relevant digit
        power -= 1
    print(f"Decimal equivalent: {int(decimal)}") # Print when conversion is done

def numCheckDec(number):# A function to validate the decimal number
    try:
        number = int(number) # Try to convert input into an integer
    except ValueError: # In case the input doesn't contain integer characters
        print("Error: Invalid input.")
        return  False

    if int(number) < 0: # In case the input integer is negative
        print("Error: Invalid input. positive numbers only.")
        return False

    return True
def convert_base10_to_base2(number): #Decimal to Binary conversion
    flag = numCheckDec(number)  # initiate correctness validation
    while flag == False:  # The user will be stuck in the loop as long as the input is incorrect
        number = input("Please enter a positive decimal number.")
        flag = numCheckDec(number)
    number = int(number)
    binary = "" # Start with an empty string
    while number > 0:
        remainder = number % 2 #The remainder defines the binary digit
        binary = str(remainder) + binary #Add current digit
        number //= 2 # Divide by 2 and round downwards
    print(f"Binary equivalent: {binary}")


while True: # Main code
    print("\nSelection Menu:")
    print("1. Convert from base 2 to base 10")
    print("2. Convert from base 10 to base 2")
    choice = input("Enter your choice (1 or 2): ")

    if choice == '1':
        binary_input = input("Enter a binary number: ")
        decimal_output = convert_base2_to_base10(binary_input)
    elif choice == '2':
        decimal_input = input("Enter a positive decimal number: ")
        binary_output = convert_base10_to_base2(decimal_input)
    else:
        print("Error: Invalid choice. Please enter 1 or 2.")
        continue

    proceed = input("Do you want to perform another conversion? (yes/no): ")
    if proceed.lower() != 'yes':
        break # Return to menu once more