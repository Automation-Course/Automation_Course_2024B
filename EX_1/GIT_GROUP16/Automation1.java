import java.util.Scanner;

public class Automation1 {
	static Scanner sc = new Scanner(System.in);

	public static void main(String[] args) {
		int digit=1;
		while (digit!=0) {
			digit=menu();
			if (digit==1) { // the user choose Decimal to Binary
				System.out.println("Please insert Decimal number:");
				long num = sc.nextLong();
				DecToBin(num);
			}
			if (digit==2) { // the user choose Binary to Decimal
				String num;
				System.out.println("Please insert binary number:");
				do{
					num = sc.nextLine();
				} while (num.length() == 0); 
				BinToDec(num);
			}
		}
		System.out.println("End Program. Goodbye!");
	}

	public static void DecToBin (long dec) { // function that convert from decimal to binary number.
		if(dec < 0) {
			System.out.println("The number is smaller then 0. Choose again.");
			System.out.println();
			return;
		}
		int n = checkLength(dec);
		int [] binary = new int [n];
		for (int i=0 ; i<n ; i++) {
			binary[i]=(int)(dec%2);
			dec=dec/2;
		}
		System.out.print("The binary number is: ");
		for (int i=n-1 ; i>=0 ; i--) {
			System.out.print(binary[i]);
		}
		System.out.println();
		System.out.println();
	}

	public static void BinToDec (String bin) { // function that convert from binary to decimal number.
		char tmp;
		double ans = 0;
		double pow = 0;
		int binary;
		for( int i = bin.length()-1; i > -1 ; i--) {
			tmp = bin.charAt(i);
			if(tmp == '0')
				binary = 0;
			else if(tmp == '1')
				binary = 1;
			else {
				System.out.println("it's not a binary number. Please choose again");
				System.out.println();
				return;
			}
			ans = ans + binary*Math.pow(2,pow);	
			pow++;
		}
		System.out.println("The decimal number is: " + (long)ans);
		System.out.println();
	}

	public static int menu () { // menu function.
		int digit = 0 ;
		System.out.println("Base calculater: ");
		System.out.println("0. End Program");
		System.out.println("1. Decimal to Binary");
		System.out.println("2. Binary to Decimal");
		digit = sc.nextInt();
		if (digit<=2 && digit>=0)
			return digit ;
		else { //Check the integrity of the input
			while (digit>2 || digit<0) {
				System.out.println("Invalid menu input");
				System.out.println("0. End Program");
				System.out.println("1. Decimal to Binary");
				System.out.println("2. Binary to Decimal");
				digit = sc.nextInt();
			}
		}
		return digit;
	}

	public static int checkLength (long num) { // function that check the number length. 
		int n = 0, check=1 ;
		while (num >= check) {
			check = check*2;
			n++;
		}
		return n;
	}
}

