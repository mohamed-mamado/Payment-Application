#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "card.h"

cardError getCardHolderName(cardData* cardData) {

	char name[30];
	printf("\n\n\n");
	printf("\t\t\t\t    Enter Card Holder Name \n");
	rewind(stdin);
	fgets(name, sizeof(name), stdin);

	int z = strlen(name);
	int size = z -1;
	int pos = 0;
	if (size > 24 || size < 20) {
		return WRONG_NAME;
	}
	else if (size == 0) {
		return WRONG_NAME;
	}
	else {
		for (int i = 0; i < size; i++) {
			cardData->cardHolderName[i] = name[i];
		}
		return OK;
	}
}

cardError getCardExpiryDate(cardData* cardData) {

	char date[30];
	printf("\n\n\n");
	printf("\t\t\t\t    Enter Card Expiry Date in this format 'mm/yy' \n");
	rewind(stdin);
	fgets(date, sizeof(date), stdin);

	int z = strlen(date);
	int size = z - 1;

	if (size != 5) {
		return WRONG_EXP_DATE;
	}
	else if (date[2] != '/') {
		return WRONG_EXP_DATE;
	}
	else {
		int a[5];
		for (int i = 0; i < 5; i++) {
			a[i] = date[i] - '0';
		}
		if (a[0] == 1 && a[1] > 2) {
			return WRONG_EXP_DATE;
		}
		else if (a[0] > 1 || a[1] > 9 || a[3] > 4 || a[4] > 9) {
			return WRONG_EXP_DATE;
		}
		else {
			for (int i = 0; i < size; i++) {
				cardData->cardExpirationDate[i] = date[i];
			}
			return OK;
		}
	}
}

cardError getCardPAN(cardData* cardData) {

	char date[30];
	printf("\n\n\n");
	printf("\t\t\t\t    Enter primary Account Number \n");
	rewind(stdin);
	fgets(date, sizeof(date), stdin);

	int z = strlen(date);
	int size = z;

	int nDigits = z;
	int d;
	int nSum = 0;
	bool isSecond = false;
	for (int i = nDigits - 2; i >= 0; i--) {

		int d = date[i] - '0';

		if (isSecond == true)
		{
			d = d * 2;
		}

		// We add two digits to handle
		// cases that make two digits after
		// doubling
		nSum += d / 10;
		nSum += d % 10;

		isSecond = !isSecond;
	}
	if (nSum % 10 != 0) {
		return WRONG_PAN;
	}
	else if (size <= 16 || size >= 19) {
		return WRONG_PAN;
	}
	else {
		for (int i = 0; i < size; i++) {
			cardData->primaryAccountNumber[i] = date[i];
		}
		return OK;
	}
}