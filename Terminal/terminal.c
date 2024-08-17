#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "terminal.h"


terminalError getTransactionDate(terminalData* termData) {

	char date[30];
	printf("\n\n\n");
	printf("\t\t\t\t    Enter Transaction Date in this format 'dd/mm/yyyy' \n");
	rewind(stdin);
	fgets(date, sizeof(date), stdin);

	int z = strlen(date);
	int size = z - 1;

	if (size != 10) {
		return WRONG_DATE;
	}
	else if (date[2] != '/' || date[5] != '/') {
		return WRONG_DATE;
	}
	else {
		int a[10];
		for (int i = 0; i < 10; i++) {
			a[i] = date[i] - '0';
		}
		if (a[0] > 3 || a[1] > 9 || a[3] > 1 || a[4] > 9 || a[6] > 2 || a[7] > 1 || a[8] > 9 || a[9] > 9) {
			return WRONG_DATE;
		}
		else if (a[0] == 3 && a[1] > 2) {
			return WRONG_DATE;
		}
		else if (a[3] == 1 && a[4] > 2) {
			return WRONG_DATE;
		}
		else {
			for (int i = 0; i < size; i++) {
				termData->transactionDate[i] = date[i];
			}
			return Ok;
		}
	}
}

terminalError isCardExpired(cardData* cardData, terminalData* termData) {

	if (termData->transactionDate[8] < cardData->cardExpirationDate[3]) {
		return Ok;
	}
	else if (termData->transactionDate[9] < cardData->cardExpirationDate[4]) {
		return Ok;
	}
	else if (termData->transactionDate[3] < cardData->cardExpirationDate[0]) {
		return Ok;
	}
	else if (termData->transactionDate[4] < cardData->cardExpirationDate[1]) {
		return Ok;
	}
	else {
		return EXPIRED_CARD;
	}
}

terminalError getTransactionAmount(terminalData* termData) {

	float number;
	printf("\n\n\n");
	printf("\t\t\t\t    Enter Transaction Amount' \n");
	scanf_s("%f", &number);

	if (number > 0.0) {
		termData->transAmount = number;
		return Ok;
	}
	else {
		return INVALID_AMOUNT;
	}
}

terminalError setMaxAmount(terminalData* termData) {
	float number;
	printf("\n\n\n");
	printf("\t\t\t\t    Enter Transaction Max Amount' \n");
	scanf_s("%f", &number);

	if (number > 0.0) {
		termData->maxTransAmount = number;
		return Ok;
	}
	return INVALID_MAX_AMOUNT;
}


terminalError isBelowMaxAmount(terminalData* termData) {
	terminalError b;
	if (termData->maxTransAmount < termData->transAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	return Ok;
}
