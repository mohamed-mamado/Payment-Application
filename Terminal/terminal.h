#include <stdio.h>
#include <string.h>
#include "..\Card\card.h"

#ifndef TERMINAL_H
#define TERMINAL_H

typedef struct 
{
	float transAmount;
	float maxTransAmount;
	unsigned int transactionDate[11];
}terminalData; 

typedef enum 
{
	Ok, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}terminalError;

terminalError getTransactionDate(terminalData* termData);

terminalError isCardExpired(cardData* cardData, terminalData* termData);

terminalError getTransactionAmount(terminalData* termData);

terminalError setMaxAmount(terminalData* termData);

terminalError isBelowMaxAmount(terminalData* termData);

#endif //TERMINAL_H
