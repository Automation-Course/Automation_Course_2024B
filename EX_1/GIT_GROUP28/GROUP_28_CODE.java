//package Calc;
package automazia; //need to change to the project's name
import java.util.*;
public class calcClass {
	public static void main(String[] args) 
	{
		while (true)
		{
			System.out.println("Enter '1' for converting decimal to binary,");
			System.out.println("Enter '2' for converting binary to decimal,");
			System.out.println("Enter '9' to END");
			Scanner st = new Scanner(System.in);
			String choice = st.nextLine();
			if (choice.equals("9")) break;
			if (!choice.equals("1") && !choice.equals("2")) System.out.println("Wrong input, please try again");
			else
			{
				System.out.println("Enter your number");
				Scanner sc = new Scanner(System.in);
				String usersNum = sc.nextLine();

				if (choice.equals("1"))
				{ 
					if (canConvertToInt(usersNum) == true)
					{
						int convertedNum = Integer.parseInt(usersNum);
						System.out.println("Your number in binary is: " + decimalToBinary(convertedNum));
					}
					else {	System.out.println("Your number is not an integer, please try again");
					}
				}
				else
				{
					if (binaryToDecimal(usersNum) == -1) System.out.println("Your number is not a  binary");
					else System.out.println("Your number in decimal is: " + binaryToDecimal(usersNum));
				}
			}
		}
	}


	public static String decimalToBinary(int decimal) 
	{
		boolean flag = true;
		if (decimal < 0)
		{
			flag = false;
			decimal = Math.abs(decimal);
		}
		String ans = "";
		while (decimal > 0) 
		{
			int remainder = decimal % 2;
			ans = String.valueOf(remainder) + ans;
			decimal = decimal / 2;
		}
		if (flag == true)
		{
			ans = '0' + ans;
		}
		else
		{
			ans = '1' + ans;
		}
		return(ans);
	}

	public static int binaryToDecimal(String binary) 
	{
		if (checkBinary(binary) == false)
		{
			return -1;
		}
		int decimal = 0;
		int power = 0;
		String temp = String.valueOf(binary);
		for (int i = temp.length() - 1; i >= 0; i--) {
			if (temp.charAt(i) == '1') {
				decimal += Math.pow(2, power);
			}
			power++;
		}

		return decimal;
	}


	public static boolean checkBinary(String num) 
	{

		for (int i = 0; i < num.length(); i++) 
		{
			char digit = num.charAt(i);
			if (digit != '0' && digit != '1') 
			{
				return false;
			}
		}
		return true;
	}

	public static boolean canConvertToInt(String str) 
	{
		try 
		{
			Integer.parseInt(str);
			return true;
		} 
		catch (NumberFormatException e) 
		{
			return false;
		}
	}
}

