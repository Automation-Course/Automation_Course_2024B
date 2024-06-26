# -*- coding: utf-8 -*-
"""
Created on Sun May 19 19:21:58 2024

@author: ram19
"""

def check_number(num, base):
    """
    Checks if the given number is valid in the specified base. 
    Args:
        num (str): The number to be checked.
        base (str): The base of the number (either '10' for base 10 or '2' for base 2).     
    Returns:
        bool: True if the number is valid, False otherwise.
    """
    # Check if the base is valid
    if base not in ('2', '10'):
        print("Wrong base")
        return False
    # Define the allowed characters based on the base
    if base == '10':
        allowed = '1234567890'
    else:
        allowed = '01'
    
    # Check if the number contains only allowed characters
    if not all(char in allowed for char in num):
        print('Number contains characters that are not allowed\n')
        return False
    
    # Return True if the number is not None
    if num is not None:
        return True

def get_input():
    """
    Gets input from the user for the number and its base, and validates the input.
    
    Returns:
        tuple: A tuple containing the number and its base.
    """
    flag = False
    while not flag:
        # Get number and base from user
        num = input('Enter a number:\n')
        base = input('Which base? Enter 10 or 2:\n')
        # Validate input
        flag = check_number(num, base)
    return (num, base)

def ten_to_two(num):
    """
    Converts a base 10 number to its equivalent in base 2.
    
    Args:
        num (str): The base 10 number to be converted.
        
    Returns:
        str: The equivalent number in base 2.
    """
    num = int(num)
    base_2 = ''
    # Convert to base 2
    while num != 0:
        a = num % 2
        base_2 += str(a)
        num //= 2
    return base_2[::-1]

def two_to_ten(num):
    """
    Converts a base 2 number to its equivalent in base 10.
    
    Args:
        num (str): The base 2 number to be converted.
        
    Returns:
        int: The equivalent number in base 10.
    """
    base_10 = 0
    # Convert to base 10
    for i, char in enumerate(num):
        base_10 += int(char) * 2 ** (len(num) - i - 1)
    return base_10

def calc():
    """
    Performs the conversion based on user input.
    
    Returns:
        str or int: The converted number.
    """
    num = get_input()
    # Choose conversion based on input base
    if num[1] == '10':
        return ten_to_two(num[0])
    else:
        return two_to_ten(num[0])

def main():
    """
    Main function to interact with the user and perform conversions.
    """
    print("Hi! Please choose a base for the number.")
    print("This program will convert the number to base 2 or 10 based on your choice.\n")
    
    exit_choice = input("To start, press any key. To exit, press 0.\n")
    
    while exit_choice != '0':
        # Perform conversion and display result
        result = calc()
        print("Your converted number is:", result)
        exit_choice = input("To convert another number, press any key. To exit, press 0.\n")

if __name__ == '__main__':
    main()
