#pragma once

//To be able to write normal c code without error messages
#pragma warning(disable : 4996)

//To avoid secure error messages that force the use of scanf_s, fopen_s, etc.
#ifdef  _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

//#include "stdio.h"		//Input/Output for user
//#include "conio.h"		//Input/Output for console
//#include "tchar.h"		//To Edit console window name character string
//#include "string.h"		//string check and processing like (strcmp(string, string) == 0)
//#include "stdlib.h"		//Used forctext to number and vice versa, Input/Output, string, etc.
//#include "errno.h"		//Displays Error Numbers

#include "windows.h"	//includes sleep definition and setting console window name, strcmp, strlen,
#include "io.h"			//file functions like _access to check if file exits and if writable
#include "time.h"		//To freeze the system when needed and to display time and date

//Function Prototypes NOT in this header file
int account_login(const char *logfile);
void main_Menu();
void admin_Menus();
void admin_Menu(const char *datafile, const char *file);
void modify_delete(const char *datafile);
void modify_Account(const char *datafile);
void delete_Account(const char *datafile);
void staff_Menu();
void view_Accounts(const char *datafile, const char *textfile);
void new_Account(const char *datafile);
void billing_Account(const char *datafile);
void customer_Menu(int accountNo);
void customer_view(const char *datafile, int accountNum);
void logout();

//All files used and max accounts for each
#define admin_d "admin.dat"
#define admin_f "admin.txt"
#define staff_d "staff.dat"
#define staff_f "staff.txt"
#define customer_d "customer.dat"
#define customer_f "customer.txt"
#define MAX_Accounts 999

/*Structure used for all accounts to use for
reading, writing, and modifying binary files*/
struct account
{
	//"ACCOUNT NUMBER" or "USER ID"
	unsigned int ID;

	//credentials used to login
	char username[17];
	char password[17];

	char fullname[17];

	//Billing address and mobile number
	char billing[17];
	char mobileNo[17];

	double balance;
	//Date automatically updated with each change
	char updated[17];
};

//used to know the logged in user to display name
char user[17], pass[17];

//used for the current date string generation
time_t now = time(NULL);
struct tm today = *(localtime(&now));
size_t str;


//Used in many functions to have a "smooth" feel of the system
void smooth()
{
	/*Clears the console window and displays loading
	message for miliseconds then clears again*/
	system("cls");
	printf("Loading...\n");
	Sleep(300);
	system("cls");
}

//Sets up the system for the first start, facilitates all the files needed
void setup()
{
	FILE *fPtr;
	unsigned int n = 0;
	//creates customer binary file if it doesn't exist
	if ((fPtr = fopen(customer_d, "rb+")) == NULL)
	{
		fPtr = fopen(customer_d, "wb+");
		fclose(fPtr); n++;
	}
	//creates staff binary file if it doesn't exist
	if ((fPtr = fopen(staff_d, "rb+")) == NULL)
	{
		fPtr = fopen(staff_d, "wb+");
		fclose(fPtr); n++;
	}
	//creates admin binary file if it doesn't exist
	if ((fPtr = fopen(admin_d, "rb+")) == NULL)
	{
		puts("First System Run!\nProvide Your Admin Details");
		fPtr = fopen(admin_d, "wb+");
		fclose(fPtr);
		Sleep(1500);
		new_Account(admin_d); n++;
	}
	if (n > 0)
	{
		system("cls");
		puts("System Ready To Use!");
		Sleep(2000);
	}
}

//Takes in a string and ouputs a Clean Menu Page
void output(const char *string)
{
	//clears screen and loads
	smooth();

	//Displays current date and time w/ customized string
	char date[33];
	str = strftime(date, 32, "%B %d, %Y %H:%M", &today);
	printf("%s\n", date);

	printf("\n\t\t\t\t");
	//Displays - to the length of the string
	for (size_t i = 0; i <= strlen(string) + 1; i++)
	{
		printf("-");
	}

	//Displays string passed
	printf("\n\t\t\t\t ");
	puts(string);

	printf("\t\t\t\t");
	//Displays - to the length of the string
	for (size_t i = 0; i <= strlen(string) + 1; i++)
	{
		printf("-");
	}
	puts("\n");
}

//Main function for user choice input used for many other functions
//Prompts a choice number from user and checks if it is a number
int choice_Input()
{
	printf("%-16s", "Choice: ");
	unsigned int menuchoice;
	char menu[10];

	//Reads input as a string first
	scanf_s("%16s", menu, sizeof(menu));

	//checks if input is a number to avoid run time errors
	if (sscanf_s(menu, "%u", &menuchoice) != 1)
	{
		puts("\n\aInput Only Numbers!");
		Sleep(1000);
		menuchoice = 0;
		return(-1);
	}
	//returns number to function call
	else
	{
		return (menuchoice);
	}
}

/*Displays Main MBBS Menu using output function to look like a menu page
Displays choices and gets input of choice using choice_input function*/
unsigned int main_Choice()
{
	output("WELCOME TO MOON BUCKS BILLING SYSTEM");
	puts("(1)Administrator\n(2)Staff\n(3)Customer\n(0)EXIT");
	return(choice_Input());
}

/*Displays Admin first Menu using output function to look like a menu page
Displays choices and gets input of choice using choice_input function*/
unsigned int admin_First_Choice(void)
{
	output("ADMIN MAIN MENU");
	puts("(1)Your Account\n(2)Staff Accounts\n(3)Customer Accounts\n(0)EXIT");
	return (choice_Input());
}

/*Displays Admin second Menu using output function to look like a menu page
Displays choices and gets input of choice using choice_input function*/
unsigned int admin_Choice(void)
{
	output("ADMIN MENU");
	puts("(1)View Profiles\n(2)New Account\n(3)Transaction\n(4)Modify / Delete Accounts\n(0)Go Back");
	return (choice_Input());
}

/*Displays Staff Menu using output function to look like a menu page
Displays choices and gets input of choice using choice_input function*/
unsigned int staff_Choice(void)
{
	output("STAFF MAIN MENU");
	puts("(1)View Profiles\n(2)New Customer\n(3)Transaction\n(0)EXIT");
	return (choice_Input());
}

/*Displays Customer Menu using output function to look like a menu page
Displays choices and gets input of choice using choice_input function*/
unsigned int customer_Choice(void)
{
	output("CUSTOMER MAIN MENU");
	puts("(1)View Your Profile\n(0)Exit");
	return (choice_Input());
}

//Displays choices and gets input of choice using choice_input function*/
unsigned int modify_Choice(void)
{
	output("UPDATE ACCOUNT RECORDS");
	puts("\n(1)Modify Account\n(2)Delete Account\n(0)Go Back");
	return (choice_Input());
}

//Displays the labels of the account information of the structure
void acc_Output(void)
{
	printf("%-6s%-18s%-18s%-18s%-18s%-18s%-7s%10s\n", "ID", "UserName", "Password", "Name",
		"Billing Add.", "Mobile No.", "Balance", "Updated");
}

/*Displays Account menu using output function to look like a page
Displays prompt and gets input of account number*/
int acc_Input(const char *string)
{
	output(string);
	printf("%-16s", "(0)Return\nAcount ID: ");
	char num[16];
	int account;

	//Reads input as a string first
	scanf_s("%16s", num, sizeof(num));

	//checks if input is a number to avoid run time errors
	if (sscanf_s(num, "%d", &account) != 1)
	{
		puts("\n\aInput Only Numbers!");
		account = 0;
		num[0] = '\0';
		Sleep(1000);
		system("cls");
		acc_Input(string);
	}
	//checks if account number is outside range to avoid logical errors
	
	else if (account == 0)
	{
		return(-1);
	}

	else if (account > MAX_Accounts or account < 1)
	{
		puts("\n\aInvalid Account Number!");
		account = 0;
		num[0] = '\0';
		Sleep(1000);
		system("cls");
		acc_Input(string);
	}
	//returns number to function call to be used
	else
	{
		return(account);
	}
}


//Checks if a Text FILE is accessable
int text_file_check(const char *file)
{
	FILE *pcheck;
	fopen_s(&pcheck, file, "w+");

	//_access from io header for file asssertions and error check
	if ((_access(file, 0)) != -1 && (_access(file, 2)) != -1)
	{
		if (pcheck)
			fclose(pcheck);
		return(0);
	}
	//If there is an error in file access error message is displayed and -1 is returned
	else
	{
		system("cls");
		printf("\aFile Access Error: %d\n", errno);
		Sleep(1500);
		return(-1);
	}
}

//Checks if a Binary FILE is accessable
int binary_file_check(const char *datafile)
{
	FILE *pcheck;
	fopen_s(&pcheck, datafile, "rb+");

	//_access from io header for file asssertions and error check
	if ((_access(datafile, 0)) != -1 && (_access(datafile, 2)) != -1)
	{
		if (pcheck)
			fclose(pcheck);
		return(0);
	}
	//If there is an error in file access error message is displayed and -1 is returned
	else
	{
		system("cls");
		printf("\aFile Access Error: %d\n", errno);
		Sleep(1500);
		return(-1);
	}
}

/*Displays logout and exit menu using output function to look like a menu page
Displays choices and gets input of choice using choice_input function*/
unsigned int logout_exit(void)
{
	output("LOGOUT AND EXIT PAGE");
	puts("(1)Logout\n(0)Exit");
	return (choice_Input());
}

//Closes the system in a fashionable manner
void close(void)
{
	system("cls");
	puts("Closing...");
	Sleep(300);
	exit(0);
}

//Could be used to further verify
unsigned int yes_no(void)
{
	puts("\nAre You Sure You Want To Proceed?");
	puts("(1)Yes\n(0)No Return");
	return (choice_Input());
}

void loops()
{
	for(a=0; a<11;a++)
	{
	printf(a);
	}
	
	int z=0;
	while(z< 11){
		printf(z);
		z++
	}
	
}