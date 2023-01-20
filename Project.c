#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"
#include "constants.h"


int main(void)
{
	int expression = 0, i = -1;
	data stocks[MAX];
	char newline_char;
	float total_buying_price_of_share = 0, selling_result = 0;
	bool shares_bought = false;

	while (expression != EXIT_VALUE) {

		expression = get_user_input();
		
		/*
			Implementing this loop so that the user saves the information to database
			after buying shares to prevent loss of data in case of any accidents
			(for ex.- user forgets to save to database, application crashes, etc.)
		*/
		while ((shares_bought && expression != 2) && (shares_bought && expression != 4))
		{
			printf("Please save to database(Press '2') or buy more shares(Press '4') before continuing:");
			expression = read_positive_int();
		}
		shares_bought = false;

	menu:
		switch (expression)
		{

		case 1:

			initialize_the_database(stocks);
			break;

		case 2:

			save_database(stocks, i);
			break;

		case 3:

			read_database(stocks);
			break;

		case 4:

			shares_bought = true;
			i++;

			buy_shares(stocks, i);

			/*
				continuing only if user presses 'Enter' key on the keyboard.
				(Implemented this function so that the user does not miss to read the save message)
			*/
			if (scanf("%c", &newline_char))
			{
				continue;
			}

			break;

		case 5:

			i++;
			total_buying_price_of_share = sell_shares(stocks, i, &selling_result);
			break;

		case 6:

			print_stocks_owned_by_user(stocks);
			break;

		case 7:

			print_report_of_sold_shares(stocks, total_buying_price_of_share, selling_result);
			break;

		case 8:

			printf("You have exited the program.\n");
			break;

		default:

			expression = fix_input_error();
			goto menu;
		}

	}

	return 0;
}

