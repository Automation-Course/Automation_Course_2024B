#Binary to Decimal calculator
def BinaryToDec(binary):
    Dec = 0
    power = len(binary) - 1
    for i in binary:
        if i != "0" and i != "1": #validation check
            return "not a valid number"
        Dec += int(i) * (2 ** power) #create the Decimal number
        power -= 1
    return Dec

#Decimal to Binary calculator
def DecToBinary(Dec) :
    if Dec == 0 :
        return '0'
    if Dec.isdigit() :
        Dec = int(Dec)
        binary = ''
        while Dec > 0 :
            remainder = Dec % 2
            binary = str(remainder) + binary #adds the remainders
            Dec //= 2
        return binary
    else: #validation check
        return "not a valid number"

# user menu
def menu():
    choice = 0
    while choice != "3":
        cho4ice = input("choose option: 1 - convert from Dec to Binary, 2 - convert from Binary to Dec, 3 - finish program")
        if choice == "1":
            Dec = input("Enter number to convert")
            print(DecToBinary(Dec))
        if choice == "2":
            binary = input("Enter number to convert")
            print(BinaryToDec(binary))


menu()


