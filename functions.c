#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"
#include "constants.h"

//clear input buffer
void clear_buffer()
{
	while ((getchar()) != '\n');
}

/* this function will repeatedlty display error msg until
 the user has entered the correct input*/
int fix_input_error()
{
	int expression = 0;
	printf("Error: Enter a number in the range (1 - 8):");
	scanf("%d", &expression);
	clear_buffer();

	printf("\n");

	return expression;
}

// read a string
bool read_string(char* str, int size)
{
read:
	if (fgets(str, size, stdin) != NULL)
	{
		size_t len = strlen(str);
		if (str[len - 1] == '\n')
		{
			str[len - 1] = '\0';
		}
		else
		{
			memset(str, 0, size * sizeof(char));
			clear_buffer();
			printf("Error: Enter less than %d characters:", size);
			goto read;
		}
	}
	return true;
}

// read a positive integer value
int read_positive_int()
{
	int num = 0;

	while (scanf("%d", &num) != 1)
	{
		clear_buffer();
		printf("Error: Enter a positive integer:");
	}

	while (num <= 0)
	{
		clear_buffer();
		printf("Error: Enter an integer greater than zero(0):");
		scanf("%d", &num);
	}

	clear_buffer();
	return num;
}

// read a positive float value
float read_positive_float()
{
	float num = 0.00;

	while (scanf("%f", &num) != 1)
	{
		clear_buffer();
		printf("Error: Enter a positive number:");
	}

	while (num <= 0)
	{
		clear_buffer();
		printf("Error: Enter a number greater than zero(0):");
		scanf("%f", &num);
	}

	clear_buffer();
	return num;
}

// read user input from the menu
int get_user_input()
{
	int expression = 0;

	printf("1. Initialize (empty the database)\n");
	printf("2. Save database to file\n");
	printf("3. Read database from file\n");
	printf("4. Buy shares \n");
	printf("5. Sell shares \n");
	printf("6. Print a report which contains list of all shares that you still own followed by the total price of the shares.\n");
	printf("7. Print a report of all sold shares. Display profit/loss per sale. Print total profit/losses at the end of the report.\n");
	printf("8. Exit\n");

	printf("SELECT ONE OF THE OPTIONS GIVEN ABOVE (Enter a number between 1-8):");
	scanf("%d", &expression);
	clear_buffer();

	printf("\n");

	return expression;
}

// read date and check whether it is valid
bool check_date(char* date)
{
	int day = 0, month = 0, year = 0;
	bool is_leap = false, is_valid = true;

	sscanf(date, "%d/%d/%d", &day, &month, &year);
	clear_buffer();

	// check that the year is entered in the correct range
	if (year >= LOWER_LIMIT_YEAR && year <= UPPER_LIMIT_YEAR)
	{
		//  check whether year is a leap year
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			is_leap = true;
		}

		// check whether month is between 1 and 12
		if (month >= 1 && month <= 12)
		{
			// check for days in feb
			if (month == 2)
			{
				if (is_leap && (day <= 0 || day > 29))
				{
					is_valid = false;
					printf("Error: Day should be in the range [1 - 29] in a leap year\n");

				}
				else if (!is_leap && (day <= 0 || day > 28))
				{
					is_valid = false;
					printf("Error: Day should be in the range [1 - 28]\n");
				}
			}
			// check for days in April, June, September and November
			else if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day <= 0 || day > 30)
				{
					is_valid = false;
					printf("Error: Day should be in the range [1 - 30]\n");
				}

			}
			// check for days in Jan, Mar, May, July, Aug, Oct, Dec
			else if (day <= 0 || day > 31)
			{
				is_valid = false;
				printf("Error: Day should be in the range [1 - 31]\n");
			}
		}
		else
		{
			is_valid = false;
			printf("Error: Month should be in the range [1 - 12]\n");
		}
	}
	else
	{
		is_valid = false;
		printf("Year should be in the range [%d - %d]\n", LOWER_LIMIT_YEAR, UPPER_LIMIT_YEAR);
	}

	return is_valid;
}

// count the number of digits in an integer
int count_digits_in_integer(int n)
{
	int count = 0;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}

	return count;
}

// get the max width out of all the data values
int get_max_width(data* stocks, int loop_len)
{
	int max_width = -1, digits_in_nr_of_shares = 0, digits_in_purchase_price = 0;

	for (int i = 0; i < loop_len; i++)
	{
		int company_name_len = strlen(stocks[i].company_name);
		digits_in_nr_of_shares = count_digits_in_integer(stocks[i].nr_of_shares);
		digits_in_purchase_price = WIDTH_FROM_DECIMAL_POINT + count_digits_in_integer(stocks[i].purchase_price_of_shares);
		int date_len = strlen(stocks[i].purchase_date);

		// comparing each value to get the max_width
		if (max_width < company_name_len)
		{
			max_width = company_name_len;
		}
		if (max_width < digits_in_nr_of_shares)
		{
			max_width = digits_in_nr_of_shares;
		}
		if (max_width < digits_in_purchase_price)
		{
			max_width = digits_in_purchase_price;
		}
		if (max_width < date_len)
		{
			max_width = date_len;
		}
	}

	return max_width;
}

// ---------------------------------------------------------------------------------------//

/*
	MENU FUNCTIONS
*/

// 1. initializes the database to zero(0)
void initialize_the_database(data* stocks)
{
	int return_value;
	char ans;
	bool keep_running = true;

	memset(stocks, 0, MAX * sizeof(data)); // initialize the array
	printf("All records set to zero\n");

	do
	{
		printf("Do you want to delete the file?('Y' for yes or 'N' for no):");
		scanf(" %c", &ans);

		if ((toupper(ans) != 'Y' && toupper(ans) != 'N'))   // convert to uppercase & check answer
		{
			printf("INCORRECT ANSWER, TRY AGAIN\n");
		}
		else if (toupper(ans) == 'Y')
		{
			return_value = remove(FILENAME);

			if (return_value == 0) {
				printf("File deleted succesfully");
			}
			else {
				printf("Error: Unable to delete file");
			}

			keep_running = false;
		}
		else {
			printf("File not deleted.\n\n");
			keep_running = false;
		}

	} while (keep_running);

}

// 2. save to a file
void save_database(data* stocks, int i)
{
	int loop_len = i + 1;		//loop_len = no. of times struct is read
	FILE* file;
	file = fopen(FILENAME, "a");

	if (file == NULL)
	{
		printf("Error opening %s file.", FILENAME);
		exit(1);
	}

	if (stocks[0].purchase_price_of_shares != 0)
	{
		for (i = 0; i < loop_len; i++)
		{
			fprintf(file, "%s\n", stocks[i].company_name);
			fprintf(file, "%d\n", stocks[i].nr_of_shares);
			fprintf(file, "%.3f\n", stocks[i].purchase_price_of_shares);
			fprintf(file, "%s\n\n", stocks[i].purchase_date);
		}
	}


	fclose(file);

	printf("Saved succesfully!\n\n");
}

//3. read from a file
int read_database(data* stocks)
{
	FILE* file;
	file = fopen(FILENAME, "r");

	if (file == NULL)
	{
		printf("Error opening %s file.", FILENAME);
		exit(1);
	}

	int i = 0, loop_len = 0;
	while (fscanf(file, " %[^\n]", &stocks[i].company_name) == 1)
	{
		loop_len++;
		fscanf(file, "%d %f %s", &stocks[i].nr_of_shares, &stocks[i].purchase_price_of_shares, &stocks[i].purchase_date);

		i++;
	}

	fclose(file);

	return loop_len;	//loop_len =  no. of times struct is read
}

// 4. buy shares
void buy_shares(data* stocks, int i)
{
	printf("Enter company name:");
	read_string(stocks[i].company_name, MAX);

	printf("Enter number of shares you want to buy:");
	stocks[i].nr_of_shares = read_positive_int();

	printf("Price of shares:");
	stocks[i].purchase_price_of_shares = read_positive_float();

	do
	{
		printf("Purchase date [dd/mm/yyyy]:");
		scanf(" %[^\n]", &stocks[i].purchase_date);

		printf("\n");
	} while (!check_date(stocks[i].purchase_date));

	printf("The shares were successfully bought. Remember to save to database! Press Enter to continue...\n");

}

// 5. sell shares
float sell_shares(data* stocks, int i, float* selling_result)
{
	int loop_len = i + 1;			// loop_len = no. of times struct is read
	FILE* fp, * fp_tmp, * fp_of_sold_shares;
	bool found = false;
	char selling_company_name[MAX];
	int nr_of_shares_to_sell = 0;
	float total_buying_price_of_shares = 0;

	printf("Enter company name:");
	read_string(selling_company_name, MAX);

	printf("Enter number of shares you want to sell:");
	nr_of_shares_to_sell = read_positive_int();

	printf("Selling price of shares:");
	stocks[i].sell_price_of_shares = read_positive_float();

	do
	{
		printf("Selling date [dd/mm/yyyy]:");
		scanf(" %[^\n]", &stocks[i].sell_date);

		printf("\n");
	} while (!check_date(stocks[i].sell_date));

	/*
		File error handling
	*/
	fp = fopen(FILENAME, "r");
	if (fp == NULL) {
		printf("Unable to open file %s", FILENAME);
		exit(1);
	}

	fp_tmp = fopen(TEMP_FILENAME, "w");
	if (fp_tmp == NULL) {
		printf("Unable to open %s file.", TEMP_FILENAME);
		exit(1);
	}

	fp_of_sold_shares = fopen(SOLD_SHARES_FILENAME, "a");
	if (fp_of_sold_shares == NULL)
	{
		printf("Unable to open %s file.", SOLD_SHARES_FILENAME);
		exit(1);
	}

	i = 0;
	while (fscanf(fp, " %[^\n]", stocks[i].company_name) == 1) {

		// implement this if the company name in the file matches with the company name that the user wants to sell the shares of
		if (strcmp(selling_company_name, stocks[i].company_name) == 0)
		{
			fscanf(fp, "%d %f %s", &stocks[i].nr_of_shares, &stocks[i].purchase_price_of_shares, &stocks[i].purchase_date);

			found = true;

			// printing the information about the sold shares in a file
			fprintf(fp_of_sold_shares, "%s\n", stocks[i].company_name);
			fprintf(fp_of_sold_shares, "%d\n", nr_of_shares_to_sell);
			fprintf(fp_of_sold_shares, "%.3f\n", stocks[i].purchase_price_of_shares);
			fprintf(fp_of_sold_shares, "%s\n", stocks[i].purchase_date);
			fprintf(fp_of_sold_shares, "%.3f\n", stocks[i].sell_price_of_shares);
			fprintf(fp_of_sold_shares, "%s\n\n", stocks[i].sell_date);

			// calulating total buying price
			total_buying_price_of_shares = stocks[i].purchase_price_of_shares * nr_of_shares_to_sell;

			// calculationg remaning shares after selling
			stocks[i].nr_of_shares -= nr_of_shares_to_sell;

			// printing the updated stock information if all of the shares are not sold.
			if (stocks[i].nr_of_shares > 0)
			{
				fprintf(fp_tmp, "%s\n", stocks[i].company_name);
				fprintf(fp_tmp, "%d\n", stocks[i].nr_of_shares);
				fprintf(fp_tmp, "%.3f\n", stocks[i].purchase_price_of_shares);
				fprintf(fp_tmp, "%s\n\n", stocks[i].purchase_date);
			}

			// calulating total selling price
			*selling_result = stocks[i].sell_price_of_shares * nr_of_shares_to_sell;
		}
		else
		{
			fscanf(fp, "%d %f %s", &stocks[i].nr_of_shares, &stocks[i].purchase_price_of_shares, stocks[i].purchase_date);

			// printing the other stocks' information in the temp file

			fprintf(fp_tmp, "%s\n", stocks[i].company_name);
			fprintf(fp_tmp, "%d\n", stocks[i].nr_of_shares);
			fprintf(fp_tmp, "%.3f\n", stocks[i].purchase_price_of_shares);
			fprintf(fp_tmp, "%s\n\n", stocks[i].purchase_date);
		}

	}

	i++;

	if (found == false) {
		printf("No record(s) found with the requested name: %s\n\n", selling_company_name);
	}

	// closing all the files
	fclose(fp);
	fclose(fp_tmp);
	fclose(fp_of_sold_shares);

	remove(FILENAME);
	rename(TEMP_FILENAME, FILENAME);

	printf("The shares were successfully sold.\n\n");

	return total_buying_price_of_shares;
}



// 6. print all the stocks owned by the user in a formatted column
void print_stocks_owned_by_user(data* stocks)
{
	int max_width = 0, loop_len = 0;
	float total_price_of_share = 0;

	loop_len = read_database(stocks);				// loop_len = no. of times data struct is read

	max_width = get_max_width(stocks, loop_len);	// max_width = width used for printing in a formatted column

	for (int i = 0; i < loop_len; i++)
	{
		total_price_of_share = stocks[i].nr_of_shares * stocks[i].purchase_price_of_shares;

		printf("COMPANY NAME: %*s\n", max_width + COMPANY_NAME_LABEL, stocks[i].company_name);
		printf("NR. OF SHARES: %*d\n", max_width + NR_OF_SHARES_lABEL, stocks[i].nr_of_shares);
		printf("PURCHASE PRICE: %*.3f\n", max_width + PURCHASE_PRICE_LABEL, stocks[i].purchase_price_of_shares);
		printf("PURCHASE DATE: %*s\n", max_width + PURCHASE_DATE_LABEL, stocks[i].purchase_date);
		printf("TOTAL PRICE OF THIS SHARE: %*.3f\n\n", max_width, total_price_of_share);
	}
}

// 7. print a report of all sold shares
void print_report_of_sold_shares(data* stocks, float total_buying_price_of_share, float selling_result)
{
	FILE* fp;
	int i = 0, max_width = 0, loop_len = 0, digits_in_sell_price = 0, sell_date_len = 0;
	float profit = 0, loss = 0, total_profit = 0, total_loss = 0;

	fp = fopen(SOLD_SHARES_FILENAME, "r");

	if (fp == NULL)
	{
		printf("Please sell some shares before printing a report\n");
		exit(1);
	}

	while (fscanf(fp, " %[^\n]", stocks[i].company_name) == 1)
	{
		loop_len++;

		fscanf(fp, "%d %f %s %f %s", &stocks[i].nr_of_shares, &stocks[i].purchase_price_of_shares, &stocks[i].purchase_date,
			&stocks[i].sell_price_of_shares, stocks[i].sell_date);

		i++;
	}

	// printing stock information
	for (int i = 0; i < loop_len; i++)
	{
		/*
			getting the max_width out of all the data values for printing in a formatted column
		*/
		digits_in_sell_price = WIDTH_FROM_DECIMAL_POINT + count_digits_in_integer(stocks[i].sell_price_of_shares);
		sell_date_len = strlen(stocks[i].sell_date);

		max_width = get_max_width(stocks, loop_len);

		if (max_width < digits_in_sell_price)
		{
			max_width = digits_in_sell_price;
		}
		if (max_width < sell_date_len)
		{
			max_width = sell_date_len;
		}

		printf("COMPANY NAME: %*s\n", max_width + SELLING_COMPANY_NAME_LABEL, stocks[i].company_name);
		printf("NR. OF SHARES: %*d\n", max_width + NR_OF_SOLD_SHARES_LABEL, stocks[i].nr_of_shares);
		printf("PURCHASE PRICE: %*.3f\n", max_width, stocks[i].purchase_price_of_shares);
		printf("PURCHASE DATE: %*s\n", max_width + NR_OF_SOLD_SHARES_LABEL, stocks[i].purchase_date);
		printf("SELLING PRICE: %*.3f\n", max_width + NR_OF_SOLD_SHARES_LABEL, stocks[i].sell_price_of_shares);
		printf("SELLING DATE: %*s\n", max_width + SELLING_COMPANY_NAME_LABEL, stocks[i].sell_date);

		// displaying profit/loss per sale
		if (selling_result > total_buying_price_of_share)
		{
			profit = selling_result - total_buying_price_of_share;
			printf("PROFIT OCCURED: %*.3f\n\n", max_width, profit);

			// getting total profit
			total_profit += profit;
		}
		else if (selling_result < total_buying_price_of_share)
		{
			loss = total_buying_price_of_share - selling_result;
			printf("LOSS OCCURED: %*.3f\n\n", max_width + SELLING_COMPANY_NAME_LABEL, loss);

			// getting total loss
			total_loss += loss;
		}
		else
		{
			printf("\nNeither Profit nor loss has occured. Your money remains the same.");
		}


	}

	// diplaying total profit/loss
	if (total_profit > total_loss)
	{
		printf("TOTAL PROFIT: %*.3f\n\n", max_width + SELLING_COMPANY_NAME_LABEL, total_profit);
	}
	else
	{
		printf("TOTAL LOSS: %*.3f\n\n", max_width + TOTAL_LOSS_LABEL, total_loss);
	}


}

