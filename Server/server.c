#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"server.h"
#include "card.h"

// variable will be used for the account numbers
uint16_t account_number = 0;
// variable for the transaction number that will be saved
uint32_t trans_num = 0;
// Accounts DataBase
ST_accountsDB_t Accounts_DataBase[255] = { {11650.50,"111111111111111111" } , {1200.65,"222222222222222222" } ,
		{1800.50,"333333333333333333" }, {2400.80,"444444444444444444" } };

//Transaction processes
ST_transaction_t Transactions_DataBase[255] = { 0 };

// recieving the transaction data
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_serverError_t validated_accounts;
	EN_serverError_t available_amount;
	EN_serverError_t saving_transaction;

	if (validated_accounts = isValidAccount (&transData -> cardHolderData ) == ACCOUNT_NOT_FOUND)
	{
		return DECLINED_STOLEN_CARD;
	}
	if (available_amount = isAmountAvailable(&transData -> terminalData ) == LOW_BALANCE)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (saving_transaction = saveTransaction(transData) == SAVING_FAILED )
	{
		return INTERNAL_SERVER_ERROR;
	}
	
	printf("\nYour Balance was : %f\n", Accounts_DataBase[account_number].balance);

	Accounts_DataBase[account_number].balance = (Accounts_DataBase[account_number].balance - transData->terminalData.transAmount);

	printf("\nNow Your Balance is : %f\n", Accounts_DataBase[account_number].balance);

	return APPROVED;
}


// check the validity of the account based on the database
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	for (account_number = (0 + account_number); account_number < 255; account_number++)
	{
		if (strcmp(cardData->primaryAccountNumber, Accounts_DataBase[account_number].primaryAccountNumber) == 0)
		{
			return OK;
		}
	}
	return ACCOUNT_NOT_FOUND;
	
}

//check if the amount is available in the account
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if (termData->transAmount < Accounts_DataBase[account_number].balance)
	{
		return _OK;
	}
	else
	{
		return LOW_BALANCE;
	}
}

// saving the transaction processes
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	(transData->transactionSequenceNumber) = trans_num + 0;
	if (transData->transactionSequenceNumber < 255)
	{
		Transactions_DataBase[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
		Transactions_DataBase[transData->transactionSequenceNumber].terminalData = transData->terminalData;
		Transactions_DataBase[transData->transactionSequenceNumber].transState = transData->transState;
		Transactions_DataBase[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber + 1;
		trans_num++;
		return _OK;
	}
	else
	{
		return SAVING_FAILED; // due to no memory space found
	}
}