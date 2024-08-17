#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include "server.h"
#include <stdbool.h> 

void accountsDataBase() {
	FILE* sfile;
	char q[20];
	sfile = fopen("AccountsDB.txt", "r"); //opening file to read
	accountsDB d;
	int i = 1;
	while (!feof(sfile))
	{
		fscanf(sfile, "%i %f %s\n", &accountsDatabase[i].lock, &accountsDatabase[i].balance, q);
		int z = strlen(q);
		int size = z;
		for (int j = 0; j < size; j++) {
			accountsDatabase[i].primaryAccountNumber[j] = q[j];
		}
		i++;
	}
	fclose(sfile);
}


serverError toLock(int locke, cardData* cardData) {
	accountsDataBase();
	terminalData termData;
	int x = 1;
	while (accountsDatabase[x].balance != 0) {
		int sizeST = 0;
		char primaryAccountNumbe[20];
		while (accountsDatabase[x].primaryAccountNumber[sizeST] != 0) {
			primaryAccountNumbe[sizeST] = accountsDatabase[x].primaryAccountNumber[sizeST];
			sizeST++;
		}
		int sizeARR = 0;
		while (cardData->primaryAccountNumber[sizeARR] != 10) {
			sizeARR++;
		}
		int check = 0;
		if (sizeST == sizeARR) {
			for (int size = 0; size < 20; size++) {
				if (accountsDatabase[x].primaryAccountNumber[size] == cardData->primaryAccountNumber[size]) {
					check++;
				}
			}
			if (check == sizeST && check == sizeARR) {
				accountsDatabase[x].lock = locke;
				termData.transAmount = 0;
				accountsDatabase[0].primaryAccountNumber[0] = x;
				if (accountsUpdate(&termData) == 0) {
					return ok;
				}
				else
				{
					SAVING_FAILED;
				}
			}
		}
		x++;
	}
	return SAVING_FAILED;
}
serverError accountsUpdate(terminalData* termData) {
	unsigned int postion = accountsDatabase[0].primaryAccountNumber[0];
	accountsDatabase[postion].balance -= termData->transAmount;
	FILE* fp;
	if ((fp = fopen("AccountsDB.txt", "w")) == NULL) {
		fclose(fp);
		return SAVING_FAILED;
	}
	else {
		int x = 1;
		while (accountsDatabase[x].balance != 0) {
			int sizeST = 0;
			char primaryAccountNumbe[20];
			while (accountsDatabase[x].primaryAccountNumber[sizeST] != 0) {
				primaryAccountNumbe[sizeST] = accountsDatabase[x].primaryAccountNumber[sizeST];
				sizeST++;
			}
			primaryAccountNumbe[sizeST] = '\0';
			fprintf(fp, "%i %f %s\n", 
				accountsDatabase[x].lock,
				accountsDatabase[x].balance,
				primaryAccountNumbe);
			x++;
		}
		fclose(fp);
		return ok;
	}
}

serverError isValidAccount(cardData* cardData) {
	for (int x = 1; x < 255; x++) {
		int check = 0;
		int sizeST = 0;
		int sizeARR = 0;
		while (cardData->primaryAccountNumber[sizeARR] != 10) {
			sizeARR++;
		}
		while (accountsDatabase[x].primaryAccountNumber[sizeST] != 0) {
			sizeST++;
		}
		if (sizeST == sizeARR) {
			for (int size = 0; size < 20; size++) {
				if (accountsDatabase[x].primaryAccountNumber[size] == cardData->primaryAccountNumber[size]) {
					check++;
				}
			}
			if (check == sizeST && check == sizeARR) {
				accountsDatabase[0].primaryAccountNumber[0] = x;
				if (accountsDatabase[x].lock == 1)
				{
					return LOCKED;
				}
				return ok;
			}
		}
	}
	return DECLINED_STOLEN_CARD;
}

serverError isAmountAvailable(terminalData* termData) {
	unsigned int postion = accountsDatabase[0].primaryAccountNumber[0];
	if (accountsDatabase[postion].balance < termData->transAmount) {
		return LOW_BALANCE;
	}
	return ok;
}


transState recieveTransactionData(transaction* transData) {
	accountsDataBase();
	int isValid;
	int isAmount;
	int isSave;
	isValid = isValidAccount(&transData->cardHolderData);
	if (isValid == 0) {
		isAmount = isAmountAvailable(&transData->terminalData);
		if (isAmount == 0) {
			isSave = accountsUpdate(&transData->terminalData);
			if (isSave == 0) {
				transData->transState = APPROVED;
				saveTransaction(transData);
				return APPROVED;
			}
			else {
				transData->transState = INTERNAL_SERVER_ERROR;
				saveTransaction(transData);
				return INTERNAL_SERVER_ERROR;
			}
		}
		else {
			transData->transState = DECLINED_INSUFFECIENT_FUND;;
			saveTransaction(transData);
			return DECLINED_INSUFFECIENT_FUND;
		}
	}
	else if (isValid == 5) {
		return LOCK;
	}
	else {
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(transData);
		return DECLINED_STOLEN_CARD;
	}
}

serverError saveTransaction(transaction* transData) {
	
	FILE* fp;
	if ((fp = fopen("TransactionsDB.txt", "a")) == NULL) {
		return SAVING_FAILED;
	 }
	else {

		char cardHolderNam[25];
		char primaryAccountNumbe[20];
		char cardExpirationDat[6];
		char transactionDat[11];
		int i = 0;

		while (transData->cardHolderData.primaryAccountNumber[i] != 10) {
			primaryAccountNumbe[i] = transData->cardHolderData.primaryAccountNumber[i];
			i++;
		}
		primaryAccountNumbe[i] = '\0';
		i = 0;
		while (transData->cardHolderData.cardHolderName[i] < 3000) {
			cardHolderNam[i] = transData->cardHolderData.cardHolderName[i];
			i++;
		}
		cardHolderNam[i] = '\0';
		i = 0;
		while (i < 5) {
			cardExpirationDat[i] = transData->cardHolderData.cardExpirationDate[i];
			i++;
		}
		cardExpirationDat[i] = '\0';

		i = 0;
		while (i < 10) {
			transactionDat[i] = transData->terminalData.transactionDate[i];
			i++;
		}
		transactionDat[i] = '\0';



		char  incremention[9];
		i = 0;
		while (transactionDatabase[i].cardHolderData.cardHolderName[0] != 0) {
			i++;
		}
		if (i == 255) {
			fclose(fp);
			return SAVING_FAILED;
		}
		transactionDatabase[i].cardHolderData = transData->cardHolderData;
		transactionDatabase[i].terminalData = transData->terminalData;
		transactionDatabase[i].transState = transData->transState;
		incremention[0] = transData->cardHolderData.primaryAccountNumber[0];
		incremention[1] = transData->cardHolderData.primaryAccountNumber[1];
		incremention[2] = transData->cardHolderData.primaryAccountNumber[2];

		incremention[3] = transData->terminalData.transactionDate[3];
		incremention[4] = transData->terminalData.transactionDate[4];
		incremention[5] = transData->terminalData.transactionDate[8];
		incremention[6] = transData->terminalData.transactionDate[9];

		incremention[7] = i + '0';
		incremention[8] = '\0';

		sscanf(incremention, "%u", &transactionDatabase[i].transactionSequenceNumber);




		fprintf(fp, "%i %u %s %s %s %f %f %s\n", transactionDatabase[i].transactionSequenceNumber, transData->transState, primaryAccountNumbe, cardHolderNam, cardExpirationDat, transData->terminalData.transAmount, transData->terminalData.maxTransAmount, transactionDat);
		fclose(fp);
		return ok;
	}
}


