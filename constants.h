#pragma once

/*
	CONSTANTS
*/

#define MAX 80							// max char for string 
#define DATE_SIZE 12					
#define FILENAME "Stocks.txt"
#define TEMP_FILENAME "tmp.txt"
#define SOLD_SHARES_FILENAME "Sold_Shares.txt"
#define EXIT_VALUE 8					// exit the menu
#define LOWER_LIMIT_YEAR 1900			// lowest value that can inputted in the date field
#define UPPER_LIMIT_YEAR 9999			// highest value that can inputted in the date field
#define WIDTH_FROM_DECIMAL_POINT 4		// purchase price of the share will be rounded upto '3' digits + '.' (thus, total count = 4)

/*
	WIDTH CONSTANTS FOR PRINTING
*/
#define COMPANY_NAME_LABEL 13		
#define NR_OF_SHARES_lABEL 12
#define PURCHASE_PRICE_LABEL 11
#define PURCHASE_DATE_LABEL 12

#define SELLING_COMPANY_NAME_LABEL 2
#define NR_OF_SOLD_SHARES_LABEL 1
#define TOTAL_LOSS_LABEL 4
