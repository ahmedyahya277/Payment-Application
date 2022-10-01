// incuding liberaries and card.h file
#define _CRT_SECURE_NO_WARNINGS // Normally used to prevent errors from warnings of security
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include "card.h"
#include "defs.h"

// define some constants
#define Max_Card_Name 24
#define Min_Card_Name 20
#define Card_Ex_Date 5
#define PAN_Min 16
#define PAN_Max 19


// Card Holder Name Function
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	int siz = 0;
	printf("Enter Card Holder Name :\n");
	scanf_s("%[^\n]%*c", &cardData->cardHolderName, Max_Card_Name + 1); // 25 because it counts from 0 to 24
	siz = strlen(cardData->cardHolderName);
	//printf("%d\n", siz);
	if (siz > Max_Card_Name)
	{
		return WRONG_NAME;
	}
	if (siz < Min_Card_Name)
	{
		return WRONG_NAME;
	}
	if ( (cardData->cardHolderName) == NULL) //this is the value for NULL
	{
		return WRONG_NAME;
	}
	else
	{
		printf("Welcome %s\n", cardData->cardHolderName);
		return OK;
	}
}

// Getting the Card Expiration date from the user in form of MM/YY
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	printf("\nEnter Card Expire Date in Format MM/YY :\n");
	scanf_s("%[^\n]%*c", &cardData->cardExpirationDate, Card_Ex_Date + 1); // 5 characters for MM/YY from 0 to 5 = 6 digits
	if (cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	if (!isdigit(cardData->cardExpirationDate[3]))
	{
		return WRONG_EXP_DATE;
	}
	if (!isdigit(cardData->cardExpirationDate[4]))
	{
		return WRONG_EXP_DATE;
	}
	if (!isdigit(cardData->cardExpirationDate[1]))
	{
		return WRONG_EXP_DATE;
	}
	if (!isdigit(cardData->cardExpirationDate[0]))
	{
		return WRONG_EXP_DATE;
	}
	if (cardData->cardExpirationDate == NULL)
	{
		return WRONG_EXP_DATE;
	}
	if ( strlen(cardData->cardExpirationDate) != Card_Ex_Date)
	{
		return WRONG_EXP_DATE;
	}
	else
	{
		printf("Your Card Expiration Date is %s\n", cardData->cardExpirationDate);
		return OK;
	}
}

// Getting the PAN Number fom the User
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	int sez;
	printf("Enter Card PAN :\n");
	scanf_s("%[^\n]%*c", &cardData->primaryAccountNumber, PAN_Max + 1); // 20 because it counts from 0 to 19
	sez = strlen(&cardData->primaryAccountNumber);
	//printf("%d\n", sez);
	for (int i = 0; i < sez; i++)
	{
		if (!isdigit(cardData->primaryAccountNumber[i]) )
		{
			return WRONG_PAN;
			break;
		}
	}
	if (sez > PAN_Max)
	{
		return WRONG_PAN;
	}
	if (sez < PAN_Min)
	{
		return WRONG_PAN;
	}
	if (sez == 0) // NULL 
	{
		return WRONG_PAN;
	}
	else
	{
		printf("Your Card PAN is : %s\n", cardData->primaryAccountNumber);
		return OK;
	}
}
