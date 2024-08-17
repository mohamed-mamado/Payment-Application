#include <stdio.h>
#include <string.h>
#include "..\Card\card.h"
#include "..\Terminal\terminal.h"
#ifndef SERVER_H
#define SERVER_H

typedef enum
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR, LOCK
}transState;

typedef struct
{
	cardData cardHolderData;
	terminalData terminalData;
	transState transState;
	unsigned int transactionSequenceNumber;
}transaction;

typedef enum 
{
	ok, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, LOCKED
}serverError;

typedef struct
{
	int lock;
	float balance;
	unsigned int primaryAccountNumber[20];
}accountsDB;

transState recieveTransactionData(transaction* transData);

serverError isValidAccount(cardData* cardData);

serverError isAmountAvailable(terminalData* termData);

serverError saveTransaction(transaction* transData);

void getTransaction(unsigned int transactionSequenceNumber);

serverError accountsUpdate(terminalData* termData);

serverError toLock(int locke, cardData* cardData);

void accountsDataBase();

accountsDB accountsDatabase[255];

transaction transactionDatabase[255];

#endif //SERVER_H