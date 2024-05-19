import tkinter as tk
from tkinter import messagebox

def Binary():# if the user want to convert a binary number
    BInary_window = tk.Tk() # create GUI
    BInary_window.title("Binary Calculator")
    label = tk.Label(BInary_window, text="Please enter your BINARY number:")
    label.pack(pady=40)
    entry = tk.Entry(BInary_window)
    entry.pack(padx=10, pady=10)
    button3 = tk.Button(BInary_window, text="GO", command=lambda: convert_to_decimal(entry))
    button3.pack(pady=20, padx=50)

def Decimel(): #  if the user want to convert decimal number
    Decimal_window = tk.Tk() #create GUI
    Decimal_window.title("Binary Calculator")
    label = tk.Label(Decimal_window, text="Please enter your Decimal number:")
    label.pack(pady=40)
    entry = tk.Entry(Decimal_window)
    entry.pack(padx=10, pady=10)
    button3 = tk.Button(Decimal_window, text="GO", command=lambda: decimal_to_binary_fractional(entry))
    button3.pack(pady=20, padx=50)

def convert_to_decimal(entry): #convert binary number to decimal
    decimal = 0.0
    binary = entry.get()#take the value that the user inserted
    counter = 0
    for char in binary:#check if theres letters or another numbers beside 0 or 1 in the value
        if char == '.':#to check if the user inserted too many dots in the value
            counter += 1
        if char != '1' and char != '0' and char != '.':# give an error to the user in that case
            messagebox.showinfo("Error", "error - please enter BINARY number")
            entry.master.destroy()
            return
        if counter > 1:# error if theres too many dots
            messagebox.showinfo("Error", "ERROR - too many dots")
            entry.master.destroy()
            return
    if '.' in binary:
        integer, fraction = binary.split('.')#handle with fractions
        # for integer:
        length = len(integer) - 1
        for digit in integer:
            decimal += int(digit) * (2 ** length)
            length -= 1
        # for fraction:
        i = 1
        for digit in fraction:
            decimal += int(digit) * (2 ** -i)
            i += 1
    else: # if theres no fractions:
        integer = binary
    #for integer:
        length = len(integer) - 1
        for digit in integer:
            decimal += int(digit) * (2 ** length)
            length -= 1
    messagebox.showinfo("Decimal Value", f"The decimal value is: {decimal}") #give the answer to the user
    entry.master.destroy()


def decimal_to_binary_fractional(entry, precision=5):#convert decimal to binary number
    decimal = float(entry.get())#get the value from the user, float to handle fractions
    if decimal < 0:# if the value is negative
        messagebox.showinfo("Error", "error - please enter positive number")
        entry.master.destroy()
        return
    integer_part = int(decimal)  # the full number
    fractional_part = decimal - integer_part  # the fraction

    # Convert the integer part manually
    binary_integer_part = ''
    if integer_part == 0:
        binary_integer_part = '0'
    else:
        while integer_part > 0:
            binary_integer_part = str(integer_part % 2) + binary_integer_part
            integer_part //= 2

    # Convert the fractional part by repeated multiplication
    binary_fractional_part = '.'
    while precision > 0 and fractional_part != 0:
        fractional_part *= 2
        bit = int(fractional_part)
        binary_fractional_part += str(bit)
        fractional_part -= bit
        precision -= 1
    messagebox.showinfo("Binary Value", f"The binary value is: {binary_integer_part + binary_fractional_part}")
    entry.master.destroy()



# Create the main application window
root = tk.Tk()
root.title("Binary Calculator")
label = tk.Label(root, text="Hello, please decide which calculation you want to do:")
label.pack(pady=40)

# Create a button
button = tk.Button(root, text="Binary to Decimal", command=Binary)
button.pack(side=tk.LEFT,pady=20, padx=50)
button2 = tk.Button(root, text="Decimal to Binary", command=Decimel)
button2.pack(side=tk.LEFT ,pady=20, padx=60)


# Run the event loop
root.mainloop()

