#include <stdio.h>
#include <string.h>

#ifndef CARD_H
#define CARD_H

typedef struct {
	unsigned int cardHolderName[25];
	unsigned int primaryAccountNumber[20];
	unsigned int cardExpirationDate[6];
} cardData;

typedef enum {
	OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
} cardError;

cardError getCardHolderName(cardData* cardData);

cardError getCardExpiryDate(cardData* cardData);

cardError getCardPAN(cardData* cardData);

#endif //CARD_H
