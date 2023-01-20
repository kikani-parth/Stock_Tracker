#pragma once
#include "constants.h"

//Structure for the stocks
typedef struct Data_ {
	char company_name[MAX];
	int nr_of_shares;
	float purchase_price_of_shares;
	char purchase_date[DATE_SIZE];
	float sell_price_of_shares;
	char sell_date[DATE_SIZE];
}data;

// FUNCTION DECLARATIONS

void clear_buffer();
int fix_input_error();
bool read_string(char* str, int size);
int read_positive_int();
float read_positive_float();
int get_user_input();
bool check_date(char* date);
int count_digits_in_integer(int n);
int get_max_width(data* stocks, int i);

/*
	MENU FUNCTIONS
*/

// 1.
void initialize_the_database(data* initial);

// 2.
void save_database(data* stocks, int i);

// 3.
int read_database(data* stocks);

// 4.
void buy_shares(data* stocks, int i);

// 5.
float sell_shares(data* stocks, int i, float* selling_result);

// 6.
void print_stocks_owned_by_user(data* stocks);

// 7.
void print_report_of_sold_shares(data* stocks, float total_buying_price_of_share, float selling_result);


