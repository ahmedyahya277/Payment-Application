#ifndef CARD_H
#define CARD_H

#include "defs.h"
// A Structure that holds the card data of the user
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[50];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[20];

}ST_cardData_t;

// An enum that has the output of the returned functions that containing the struture of the card data
typedef enum EN_cardError_t
{
	OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif // !CARD_H

