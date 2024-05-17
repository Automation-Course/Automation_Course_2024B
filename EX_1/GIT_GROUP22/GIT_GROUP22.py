def binary_to_decimal(binary_str: str)->int:
    decimal_num = 0
    power = len(binary_str)-1
    for digit in binary_str:
        if digit == '1':
            decimal_num = decimal_num + (2**power)
            power = power-1
        elif digit == '0':
            power = power-1
        else:
            return None  # Invalid binary input
    return decimal_num

def decimal_to_binary(decimal_str: str)->str:
  
    if decimal_str.isdigit() == False:
        return None # Invalid decimal input
    elif decimal_str == '0':
        return 0
    
    decimal_num = int(decimal_str) # Turn string to int so we can divide it
    binary_str = ''
    while decimal_num > 0:
        binary_str = str(decimal_num % 2) + binary_str
        decimal_num = decimal_num // 2
    return binary_str

def main():
    flag = True
    while flag == True:
        print("\nChoose an option:")
        print("1. Convert binary to decimal")
        print("2. Convert decimal to binary")
        print("3. Exit")

        choice = input("Enter your choice (1/2/3): ")

        if choice == '1':
            binary_input = input("Enter a binary number: ")
            decimal_output = binary_to_decimal(binary_input)
            if decimal_output is not None:
                print(f"The decimal equivalent of {binary_input} is {decimal_output}")
            else:
                print("Invalid binary input. Please start over.")

        elif choice == '2':
            decimal_input = (input("Enter a decimal number: "))
            binary_output = decimal_to_binary(decimal_input)
            if binary_output is not None:
                print(f"The binary equivalent of {decimal_input} is {binary_output}")
            else:
                print("Invalid decimal input. Please start over.")

        elif choice == '3':
            print("Exiting...")
            flag = False

        else:
            print("Invalid choice. Please choose again.")

main()