#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

#pragma warning(disable : 4996)

#include "..\Card\card.h"
#include "..\Server\server.h"
#include "..\Terminal\terminal.h"
#ifndef APP_H
#define APP_H
void appStart(void);
void start(void);
void wel_come(void);


void appStart(void) {
	int choice;
	transaction tran;
	wel_come();
agein:
	system("cls");
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t\t   If you want to do transction Enter [1] \n\n\n");
	printf("\t\t\t\t   If you want to Lock Account Enter [2] \n\n\n");
	printf("\t\t\t\t   If you want to close app Enter [3] \n\n\n");
	
	scanf("%i", &choice);
	system("cls");
	switch (choice)
	{
	case 1:
		start();
		printf("\n\t\t\t               Press any key to continue.........\t\t\t\t\t\t\t\t\t\t\n");
		getch();
		goto agein;
		break;
	case 2:
		printf("\n");
		cardData* card = malloc(sizeof(cardData));
		if (getCardPAN(card) == 0) {
			int l;
			printf("\n\n\n");
			printf("\t\t\t\t    To lock priss '1'\n");
			printf("\t\t\t\t    To unlock priss '0'\n");
			scanf("%d", &l);
			if (l == 1 || l == 0) {
				toLock(l, card);
			}
			else { printf("\t\t\t\t    wronge input\n"); }
		}
		else { printf("\t\t\t\t   you have entered wronge PAN\n"); }
		printf("\n\t\t\t               Press any key to continue.........\t\t\t\t\t\t\t\t\t\t\n");
		getch();
		goto agein;
		break;
	case 3:
		system("cls");
		break;
	default:
		printf("Invalid Choice!\n");
		printf("\n\t\t\t               Press any key to continue.........\t\t\t\t\t\t\t\t\t\t\n");
		getch();
		goto agein;
	}
}

void start(void) {
	transaction trans;
	int a = 0;
	if (getCardHolderName(&trans.cardHolderData) == 0) {
		system("cls");
		if (getCardPAN(&trans.cardHolderData) == 0) {
			system("cls");
			if (getCardExpiryDate(&trans.cardHolderData) == 0) {
				system("cls");
				if (getTransactionDate(&trans.terminalData) == 0) {
					system("cls");
					if (isCardExpired(&trans.cardHolderData, &trans.terminalData) == 0) {
						system("cls");
						if (getTransactionAmount(&trans.terminalData) == 0) {
							system("cls");
							if (setMaxAmount(&trans.terminalData) == 0) {
								system("cls");
								if (isBelowMaxAmount(&trans.terminalData) == 0) {
									system("cls");
									a = recieveTransactionData(&trans);
									system("cls");
									if (a == 0) {
										printf("\n\n\n\n");
										printf("\t\t\t\t    Transaction Approved \n");
									}
									else if (a == 1) {
										printf("\n\n\n\n");
										printf("\t\t\t\t   !!!! DECLINED INSUFFECIENT FUND\n");
									}
									else if (a == 2) {
										printf("\n\n\n\n");
										printf("\t\t\t\t   !!!! DECLINED_STOLEN_CARD\n");
									}
									else if (a == 3) {
										printf("\n\n\n\n");
										printf("\t\t\t\t   !!!! INTERNAL_SERVER_ERROR\n");
									}
									else {
										printf("\n\n\n\n");
										printf("\t\t\t\t   !!!! Card is Locked\n");
									}
								}
								else {
									printf("\n\n\n\n");
									printf("\t\t\t\t  !!!! you have exceed max amount\n"); 
								}
							}
							else {
								printf("\n\n\n\n");
								printf("\t\t\t\t   !!!! you have entered invald max amount\n"); 
							}
						}
						else {
							printf("\n\n\n\n");
							printf("\t\t\t\t   !!!! you have entered invald amount\n"); 
						}
					}
					else { 
						printf("\n\n\n\n");
						printf("\t\t\t\t   !!!! your card is expired\n");
					}
				}
				else {
					printf("\n\n\n\n");
					printf("\t\t\t\t   !!!! you have entered wronge date\n"); 
				}
			}
			else {
				printf("\n\n\n\n");
				printf("\t\t\t\t   !!!! you have entered wronge expiry date\n");
			}
		}
		else {
			printf("\n\n\n\n");
			printf("\t\t\t\t   !!!! you have entered wronge PAN\n");
		}
	}
	else {
		printf("\n\n\n\n");
		printf("\t\t\t\t  !!!! you have entered wrong name\n");
	}
}


void wel_come(void)
{
	time_t t;
	time(&t);
	printf("                                                                                                         \n");
	printf("---------------------------------------------------------------------------------------------------------\n");
	printf("\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");

	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xbd\t     WELCOME TO \t \xbd\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xbd\t      THE ATM   \t \xbd\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\t\t\t\t\t\xbd\n");

	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");

	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\t\t\t\t\t\t\t\t\t\t\t\t\t\xbd\n");
	printf("\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\n");
	printf("\t\t\t\t\t%s", ctime(&t));
	printf("\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\xbd\n");
	printf("\n\t\t\t               Press any key to continue.........\t\t\t\t\t\t\t\t\t\t\n");

	getch();
	system("cls");
}

#endif //APP_H
