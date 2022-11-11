#include "poker_chances.h"

int main(int argc, char* argv[]) {

	//Setting random seed
	srand(time(NULL));

	int royalFlushCount = 0;
	int straightFlushCount = 0;
	int fourOfAKindCount = 0;
	int fullHouseCount = 0;
	int straightCount = 0;
	int flushCount = 0;
	int threeOfAKindCount = 0;
	int twoPairCount = 0;
	int onePairCount = 0;
	int highCardCount = 0;

	int numRuns = 50000;
	int totalNumHands = numRuns * 9;

	for (int i = 0; i < numRuns; i++) {

		//Initialize deck
		card deck[52];

		//Initialize hands
		card hand1[2];
		card hand2[2];
		card hand3[2];
		card hand4[2];
		card hand5[2];
		card hand6[2];
		card hand7[2];
		card hand8[2];
		card hand9[2];

		//Initialize runout
		card runout[5];

		//Initializing deck with values and suits
		initializeDeck(deck);

		//Dealing all hands
		dealHand(deck, hand1);
		dealHand(deck, hand2);
		dealHand(deck, hand3);
		dealHand(deck, hand4);
		dealHand(deck, hand5);
		dealHand(deck, hand6);
		dealHand(deck, hand7);
		dealHand(deck, hand8);
		dealHand(deck, hand9);

		//Dealing 5 card runout
		for (int i = 0; i < 5; i++) {
			deal(deck, &runout[i]);
		}

		//Get hand evaluations
		int handEvaluations[9];

		handEvaluations[0] = evaluateHand(hand1, runout);
		handEvaluations[1] = evaluateHand(hand2, runout);
		handEvaluations[2] = evaluateHand(hand3, runout);
		handEvaluations[3] = evaluateHand(hand4, runout);
		handEvaluations[4] = evaluateHand(hand5, runout);
		handEvaluations[5] = evaluateHand(hand6, runout);
		handEvaluations[6] = evaluateHand(hand7, runout);
		handEvaluations[7] = evaluateHand(hand8, runout);
		handEvaluations[8] = evaluateHand(hand9, runout);

		for (int i = 0; i < 9; i++) {
			switch (handEvaluations[i]) {
			case 9:
				royalFlushCount++;
				break;
			case 8:
				straightFlushCount++;
				break;
			case 7:
				fourOfAKindCount++;
				break;
			case 6:
				fullHouseCount++;
				break;
			case 5:
				flushCount++;
				break;
			case 4:
				straightCount++;
				break;
			case 3:
				threeOfAKindCount++;
				break;
			case 2:
				twoPairCount++;
				break;
			case 1:
				onePairCount++;
				break;
			case 0:
				highCardCount++;
				break;
			}
		}
	}

	printf("Royal Flush: %d, %.5lf\n", royalFlushCount, 100 * (double)royalFlushCount / totalNumHands);
	printf("Straight Flush: %d, %.5lf\n", straightFlushCount, 100 * (double)straightFlushCount / totalNumHands);
	printf("Four of a Kind: %d, %.5lf\n", fourOfAKindCount, 100 * (double)fourOfAKindCount / totalNumHands);
	printf("Full House: %d, %.5lf\n", fullHouseCount, 100 * (double)fullHouseCount / totalNumHands);
	printf("Flush: %d, %.5lf\n", flushCount, 100 * (double)flushCount / totalNumHands);
	printf("Straight: %d, %.5lf\n", straightCount, 100 * (double)straightCount / totalNumHands);
	printf("Three of a Kind: %d, %.5lf\n", threeOfAKindCount, 100 * (double)threeOfAKindCount / totalNumHands);
	printf("Two Pair: %d, %.5lf\n", twoPairCount, 100 * (double)twoPairCount / totalNumHands);
	printf("One Pair: %d, %.5lf\n", onePairCount, 100 * (double)onePairCount / totalNumHands);
	printf("High Card: %d, %.5lf\n", highCardCount, 100 * (double)highCardCount / totalNumHands);

	int boatOrBetter = royalFlushCount + straightFlushCount + fourOfAKindCount + fullHouseCount;
	printf("Full house or better: %d, %.5lf\n", boatOrBetter, 100 * (double)boatOrBetter / totalNumHands);
}

