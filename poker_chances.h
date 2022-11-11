#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Card {
	int val;
	int suit;
} card;

void dealHand(card* deck, card* hand);
void deal(card* deck, card* dealSlot);
void printCard(card* card);
void printHand(card* hand, int size);
void initializeDeck(card* deck);
int evaluateHand(card* hand, card* runout);
void printResult(int eval, int hand);

void printResult(int eval, int hand) {

	switch (eval) {
	case 9:
		printf("Hand %d has a royale flush\n", hand);
		break;
	case 8:
		printf("Hand %d has a straight flush\n", hand);
		break;
	case 7:
		printf("Hand %d has four of a kind\n", hand);
		break;
	case 6:
		printf("Hand %d has a full house\n", hand);
		break;
	case 5:
		printf("Hand %d has a flush\n", hand);
		break;
	case 4:
		printf("Hand %d has a straight\n", hand);
		break;
	case 3:
		printf("Hand %d has three of a kind\n", hand);
		break;
	case 2:
		printf("Hand %d has two pair\n", hand);
		break;
	case 1:
		printf("Hand %d has a pair\n", hand);
		break;
	case 0:
		printf("Hand %d has high card\n", hand);
		break;
	}

}

int evaluateHand(card* hand, card* runout) {

	card largeHand[7];
	largeHand[0] = hand[0];
	largeHand[1] = hand[1];
	largeHand[2] = runout[0];
	largeHand[3] = runout[1];
	largeHand[4] = runout[2];
	largeHand[5] = runout[3];
	largeHand[6] = runout[4];

	int i, j, min_idx;
	for (i = 0; i < 7 - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < 7; j++)
			if (largeHand[j].val < largeHand[min_idx].val)
				min_idx = j;

		card temp = largeHand[min_idx];
		largeHand[min_idx] = largeHand[i];
		largeHand[i] = temp;
	}

	int royalFlush = 0;
	int straightFlush = 0;
	int fourOfAKind = 0;
	int fullHouse = 0;
	int straight = 0;
	int flush = 0;
	int threeOfAKind = 0;
	int twoPair = 0;
	int onePair = 0;

	int spadeCount = 0;
	int diamondCount = 0;
	int clubCount = 0;
	int heartCount = 0;

	//Royal Flush logic
	if(largeHand[0].val == 1){
		int suit = largeHand[0].suit;
		for (int i = 1; i < 7; i++) {
			if (largeHand[i].val == 10 && largeHand[i].suit == suit) {
				for (int j = 2; j < 7; j++) {
					if (largeHand[j].val == 11 && largeHand[j].suit == suit) {
						for (int k = 3; k < 7; k++) {
							if (largeHand[k].val == 12 && largeHand[k].suit == suit) {
								for (int l = 4; l < 7; l++) {
									if (largeHand[l].val == 13 && largeHand[l].suit == suit) {
										royalFlush = 1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	

	//Straight Flush logic
	for (int i = 0; i < 3; i++) {
		int count = 1;
		for (int j = 0; j < 5; j++) {
			if (j == 3 && largeHand[3 + i].val == 13 && largeHand[0].val == 1 && largeHand[3 + i].suit == largeHand[0].suit)
				count++;
			else if (largeHand[j + i].val + 1 == largeHand[j + i + 1].val && largeHand[i + j].suit == largeHand[i + j + 1].suit) {
				count++;
			}
			if (count == 5)
				straightFlush = 1;
		}
	}

	//Four of a kind logic
	for (int i = 0; i < 7; i++) {
		int count = 0;
		int pair = largeHand[i].val;
		for (int j = 0; j < 7; j++) {
			if (largeHand[j].val == pair)
				count++;
		}
		if (count == 4)
			fourOfAKind = 1;
	}

	//Full house logic
	int pairCount = 0;
	int tripsCount = 0;
	for (int i = 0; i < 6; i++) {
		if (largeHand[i].val == largeHand[i + 1].val && largeHand[i].val == largeHand[i + 2].val) {
			i += 2;
			tripsCount++;
		}
		if (i == 5 && !tripsCount) {
			break;
		}
		if (largeHand[i].val == largeHand[i + 1].val) {
			i++;
			pairCount++;
		}

		if (pairCount && tripsCount)
			fullHouse = 1;
	}

	//Flush Logic
	for (int i = 0; i < 7; i++) {
		if (largeHand[i].suit == 1)
			spadeCount++;
		else if (largeHand[i].suit == 2)
			diamondCount++;
		else if (largeHand[i].suit == 3)
			clubCount++;
		else if (largeHand[i].suit == 4)
			heartCount++;
	}

	if (spadeCount >= 5 || diamondCount >= 5 || clubCount >= 5 || heartCount >= 5) {
		flush = 1;
	}

	//Straight Logic
	for (int i = 0; i < 3; i++) {
		int count = 1;
		for (int j = 0; j < 4; j++) {
			if (j == 3 && largeHand[3 + i].val == 13 && largeHand[0].val == 1)
				count++;
			else if (largeHand[j + i].val + 1 == largeHand[j + i + 1].val) {
				count++;
			}
			if (count == 5)
				straight = 1;
		}
	}

	//Three of a kind logic
	for (int i = 0; i < 7; i++) {
		int count = 0;
		int pair = largeHand[i].val;
		for (int j = 0; j < 7; j++) {
			if (largeHand[j].val == pair)
				count++;
		}
		if (count == 3)
			threeOfAKind = 1;
	}

	//Two pair logic
	pairCount = 0;
	for (int i = 0; i < 6; i++) {
		if (largeHand[i].val == largeHand[i + 1].val) {
			i++;
			pairCount++;
		}
		if (pairCount >= 2)
			twoPair = 1;
	}

	//Pair logic
	for (int i = 0; i < 7; i++) {
		int count = 0;
		int pair = largeHand[i].val;
		for (int j = 0; j < 7; j++) {
			if (largeHand[j].val == pair)
				count++;
		}
		if (count == 2)
			onePair = 1;
	}

	//Returning correct final value
	if (royalFlush && straightFlush && straight && flush)
		return 9;
	else if (straightFlush && straight && flush)
		return 8;
	else if (fourOfAKind)
		return 7;
	else if (fullHouse)
		return 6;
	else if (flush)
		return 5;
	else if (straight)
		return 4;
	else if (threeOfAKind)
		return 3;
	else if (twoPair)
		return 2;
	else if (onePair)
		return 1;
	else
		return 0;
}

void deal(card* deck, card* dealSlot) {

	int random = rand() % 52;
	while (deck[random].val == -1) {
		random = rand() % 52;
	}

	dealSlot->val = deck[random].val;
	dealSlot->suit = deck[random].suit;

	deck[random].val = -1;
}

void printCard(card* card) {

	if (card->val == 1)
		printf("Ace of ");
	else if (card->val == 11)
		printf("Jack of ");
	else if (card->val == 12)
		printf("Queen of ");
	else if (card->val == 13)
		printf("King of ");
	else
		printf("%d of ", card->val);

	if (card->suit == 1)
		printf("Spades");
	else if (card->suit == 2)
		printf("Diamonds");
	else if (card->suit == 3)
		printf("Clubs");
	else if (card->suit == 4)
		printf("Hearts");

	printf("\n");

}

void printHand(card* hand, int size) {

	for (int i = 0; i < size; i++) {
		printCard(&hand[i]);
	}

	printf("\n");

}

void initializeDeck(card* deck) {
	int count = 0;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 13; j++) {
			deck[count].val = j;
			deck[count].suit = i;
			count++;
		}
	}
}

void dealHand(card* deck, card* hand) {

	deal(deck, &hand[0]);
	deal(deck, &hand[1]);

}