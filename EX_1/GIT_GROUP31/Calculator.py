import sys


'''****************************************************************************
************************** Automation Course 2024B EX1 ************************
****************************************************************************'''


'''*************************** 1.Binary to Decimal **************************'''

def binaryConverter(binary):
    if not(('-' in binary) or ('.' in binary)):
        DecimalOutput=0
        for i in binary:
            DecimalOutput=DecimalOutput*2+int(i)

        print(f'The Decimal value of the binary input {binary} is equal to: {DecimalOutput} \n                        ')
    else:
        print("enter a whole positive binary number not fractional or negative! \n                                    ")

'''*************************** 2.Decimal to Binary **************************'''
def DecimalConverter(Decimal):
    if Decimal >=1:
        DecimalConverter(Decimal//2)
    print(Decimal%2, end='')

'''******************************* Main Loop *******************************'''

while True:
    choice = input(
        "Welcome to our calculator please chose one of the available options: \n 1. Binary to Decimal \n 2. Decimal to Binary \n 3. exit \n your value: ")
    match choice:
        case '1':
            # Binary number as Input:
            binary = input("please enter a binary number:")
            binaryConverter(binary)
        case '2':
            Decimal = input("please enter a Decimal number:")
            if not (('-' in Decimal) or ('.' in Decimal)):
                DecimalConverter(int(Decimal))
                print("\n")
            else:
                print("enter a whole positive binary number not fractional or negative! \n                                    ")
        case '3':
            sys.exit()
        case _:  print("please insert a valid number 1/2/3!!! \n ***********************************************\n")