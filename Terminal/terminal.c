#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include "terminal.h"
#include <string.h>

//DD/MM/YYYY date format
//0123456789 bits representation
#define Transa_Date_size	10
#define day_10_trans		0
#define day_1_trans			1
#define month_10_trans		3
#define month_1_trans		4
#define year_1000_trans		6
#define year_100_trans		7
#define year_10_trans		8
#define year_1_trans		9
//MM/YY date format
//01234 bits representation
#define month_10_ex			0
#define month_1_ex			1
#define year_10_ex			3
#define year_1_ex			4

#define Max_Trans_Amount			5000.00

// Getting the transaction date from the user
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	printf("\nPlease Enter The Transaction Date in formate of DD/MM/YYYY : \n");
	scanf_s("%[^\n]%*c", &termData->transactionDate,Transa_Date_size + 1); // 10 + 1 = 11 which is from 0 to 10
	int seze = strlen(termData->transactionDate);
	//printf("%d\n", sez);
	if ( seze != 10 )
	{
		return WRONG_DATE;
	}
	if (termData->transactionDate == NULL) // NULL
	{
		return WRONG_DATE;
	}
	if (termData->transactionDate[2] != '/') // check the format
	{
		return WRONG_DATE;
	}
	if (termData->transactionDate[5] != '/') // check the format
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[day_10_trans]))
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[day_1_trans]))
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[month_10_trans]))
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[month_1_trans]))
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[year_1000_trans]))
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[year_100_trans]))
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[year_10_trans]))
	{
		return WRONG_DATE;
	}
	if (!isdigit(termData->transactionDate[year_1_trans]))
	{
		return WRONG_DATE;
	}
	else
	{
		printf("The Tracnsaction date is %s", termData->transactionDate);
		return _OK_;
	}
}

// Check the transaction date with the expiration date
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	// getting the ASCII value of the string integer and convert them to integers
	int month_t_10 = (termData.transactionDate[month_10_trans] - 48) * 10;
	int month_t_1 = (termData.transactionDate[month_1_trans] - 48) ;
	int month_trans = month_t_1 + month_t_10;

	int year_t_10 = (termData.transactionDate[year_10_trans] - 48) * 10;
	int year_t_1 = (termData.transactionDate[year_1_trans] - 48);
	int year_trans = year_t_1 + year_t_10;

	int month_ex_10 = (cardData.cardExpirationDate[month_10_ex] - 48) * 10;
	int month_ex_1 = (cardData.cardExpirationDate[month_1_ex] - 48);
	int month_expir = month_ex_1 + month_ex_10;

	int year_ex_10 = (cardData.cardExpirationDate[year_10_ex] - 48) * 10;
	int year_ex_1 = (cardData.cardExpirationDate[year_1_ex] - 48);
	int year_expir = year_ex_1 + year_ex_10;
	printf("\nChecking the card expiration date...\n");
	if ( (year_expir) < (year_trans) )
	{
		return EXPIRED_CARD;
	}
	if ( (year_expir) == (year_trans) )
	{
		if ( (month_expir) < (month_trans) )
		{
			return EXPIRED_CARD;
		}
	}
	else
	{
		printf("Your Card is NOT Expired Yet\n");
		return _OK_;
	}
}

// Getting the transaction ammount you want to withdraw or deposit
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("Please Enter The transaction amount...\n");
	scanf("%f", &termData->transAmount);

	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		printf("The Transaction Amount is %.2f\n", termData->transAmount);
		return _OK_;
	}
}

// Check if the ammount you have entered is below the max amount the terminal can handel or not
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if ((termData->transAmount) > (5000.00))
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return _OK_;
	}
}

// Setting the max amount for the terminal
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	// Setting the max amount for the terminal (Not by the User)
	termData->maxTransAmount = Max_Trans_Amount;

	printf("The Max Transaction Amount Allowed is : %f\n", termData->maxTransAmount);

	if ( (termData->maxTransAmount) <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		return _OK_;
	}
}
