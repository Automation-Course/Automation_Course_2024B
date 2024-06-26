import java.util.Scanner;
public class Calculator {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		boolean cont = true;
		while (cont)
		{
			System.out.println();
			System.out.println("Please choose transformation type:" //menu
					+ " \n1 - Decimal to Binary"
					+ "\n2 - Binary to Decimal"
					+ "\n0 - End Use");
			String userInput = scanner.next();
			 
			if (userInput.equals("1")) {
				boolean cor = false;
				int num = 0;
				/*while (!cor) {
					System.out.println("Please Enter a Decimal Number:"); //input can be negative or positive
					try 
					{
						num = scanner.nextInt();	
					}
					catch (NumberFormatException e)
					{
						System.out.println("only whole numbers are excepted");
					}
					else 
						cor = true;
				}*/
				while(!cor) {
				System.out.println("Please Enter a Decimal Number:"); //input can be negative or positive

				try {
				num = scanner.nextInt();
				cor = true;
				}
				catch (Exception e)
				{
					System.out.println("Only whole numbers are excepted");
					scanner.next();
				}
				}
				if (num >= 0) {  // case where input is positive
					int bits = (int) Math.ceil(Math.log(num+1) / Math.log(2)); //finds length of binary number
					int[] binArray = new int[bits+1]; //creates array 
					for (int i = 0; i < bits; i++) //populates array from  end to start
					{
						binArray[(bits - i )] = num%2;
						num = num/2;
					}
					
					binArray[0]=0; //first digit is positive or negative sign
					System.out.println("The correct Binary number is: ");
					for (int i = 0; i < bits+1; i++)
					{
					    System.out.print(binArray[i]);  
					}
					System.out.println();
				}
				else {
					num = num*-1; //negative number, turned positive first
					int bits = (int) Math.ceil(Math.log(num+1) / Math.log(2));
					int[] binArray = new int[bits+1];
					for (int i = 0; i < bits; i++)
					{
						binArray[(bits - i)] = num%2;
						num = num/2;
						
					}
					binArray[0]=1;
					System.out.println("The correct Binary number is: ");
					for (int i = 0; i < bits+1; i++)
					{
					    System.out.print(binArray[i]);
					}
					System.out.println();
				}
				
			}
			else if (userInput.equals("2")) {
				boolean cor = false;
				int dec = 0;
				String bin = "";
				while (!cor)
				{
				System.out.println("Please Enter a Binary Number:");
				bin = scanner.next();
				if (bin.contains("."))
					System.out.println("Only whole numbers are excepted");
				else if (bin.matches("[01]+"))
					cor = true;
				}
				
				int[] binArray = new int[bin.length()];
				for (int i = 0; i < bin.length(); i++) {
		            char digitChar = bin.charAt(i); // Get the character representing the digit
		            int digit = Character.getNumericValue(digitChar); // Convert the character to an integer
		            binArray[i] = digit; // Store the digit in the array
		        }
				/*for (int i = 0; i < binArray.length; i++) {
				    System.out.print(binArray[i]);}
				System.out.println();*/
				for (int i = 0; i < binArray.length; i++) {
					if (i != 0)// first digit is positive or negative sign
					{
				    int pwr = (int)(Math.pow(2,(double)(binArray.length-1-i))); // for each digit we find the value of 2
				    dec = dec + pwr*binArray[i]; // add the value to the current decimal number
					}
				}
				if (binArray[0] == 1) // return negative
				{
					dec =dec*-1;
				}
				System.out.println("The correct Decimal number is:" + "\n" + dec);
			}
			else if (userInput.equals("0"))
			{
				System.out.println("Thank you for using the Binary Calculator");
				cont = false;
			}
			else {
				System.out.println("invalid input, please enter valid option");
			}
			
		 // the assumptions in the code are - 1. the numbers entered are only whole numbers. 2. the binary numbers are in size and sign form
	
		}}}


