#define _CRT_SECURE_NO_WARNINGS // Normally used to prevent errors from warnings of security
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include "server.h"
#include "app.h"


#define appStart main

void appStart(void)
{
	//In[0]:
	// Card Calling functions of enumeration returns
	EN_cardError_t getCardHolderName_f;
	EN_cardError_t getCardExpiryDate_f;
	EN_cardError_t getCardPAN_f;

	// Card Data Struct
	ST_cardData_t cardHolderData;
	ST_cardData_t* cardData = &cardHolderData;

	// Getting card data(Name, Expiration Date & PAN Number)
	if (getCardHolderName_f = getCardHolderName(cardData) == WRONG_NAME) // if the enum return is wrong name
	{
		printf("\nWrong Name \n");
		return 0;
	}

	if (getCardExpiryDate_f = getCardExpiryDate(cardData) == WRONG_EXP_DATE)
	{
		printf("Wrong Expiration Date \n");
		return 0;
	}
	
	if (getCardPAN_f = getCardPAN(cardData) == WRONG_PAN)
	{
		printf("Wrong PAN \n");
		return 0;
	}
	
	//n[1]:
	// returned error emuns for the terminal functions

	EN_terminalError_t getTransactionDate_f;
	EN_terminalError_t isCardExpired_f;
	EN_terminalError_t getTransactionAmount_f;
	EN_terminalError_t isBelowMaxAmount_f;
	EN_terminalError_t setMaxAmount_f;

	// Terminal Data Structure
	ST_terminalData_t terminalData;
	ST_terminalData_t* termData = &terminalData;
	
	// Getting terminal data(Transaction Date, Terminal Max amounts & Transaction amounts )
	if (getTransactionDate_f = getTransactionDate(termData) == WRONG_DATE )
	{
			printf("\nWrong Date \n");
			return 0;
	}
	
	if (isCardExpired_f = isCardExpired(cardHolderData, terminalData) == EXPIRED_CARD)
	{
		printf("Expired Card, Please go to the nearest Bank and get a new Card \n");
			return 0;
	}
	
	if (getTransactionAmount_f = getTransactionAmount(termData) == INVALID_AMOUNT)
	{
		printf("Please Enter Valide Amount \n");
		return 0;
	}
	
	if (isBelowMaxAmount_f = isBelowMaxAmount(termData) == EXCEED_MAX_AMOUNT)
	{
		printf("Max Amount Exceeded, Lowering your amount to the terminal max amount so you can withdraw or deposit \n");
		return 0;
	}

	if (setMaxAmount_f = setMaxAmount(termData) == INVALID_MAX_AMOUNT)
	{
		printf("Invalid Max Amount \n");
		return 0;
	}
	
	//In[2]:
	// returned errors of the recieving the transaction data
	EN_transState_t recieveTransactionData_f;

	// Transaction Data Structure
	ST_transaction_t transactonData;
	ST_transaction_t* transData = &transactonData;
	
	//Getting Card Data, and Terminal Data
	transData->cardHolderData = cardHolderData;
	transData->terminalData = terminalData;
	
	recieveTransactionData_f = recieveTransactionData(transData);
	switch (recieveTransactionData_f)
	{

	case DECLINED_INSUFFECIENT_FUND:
		saveTransaction(transData);
		printf("\nTransaction Error Due To Insuffecient Fund");
		break;

	case DECLINED_STOLEN_CARD:
		saveTransaction(transData);
		printf("\nStolen Card, Thanks For Delivering The Card");
		break;

	case INTERNAL_SERVER_ERROR:
		saveTransaction(transData);
		printf("\nTransaction Declined Due To Server Error, Please Comeback Later .. ");
		break;

	case APPROVED:
		printf("\nTransaction was Done successfully ");
		break;

	default:
		break;
	}
}