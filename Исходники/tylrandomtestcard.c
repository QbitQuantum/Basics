int main(){
	int randomPlayer, seed, i, j, numPlayers;
    int runStatus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

	srand(time(NULL));
	for (i = 0; i < 2000; i++)
	{
		seed = (rand()%100) + 1;
		//Pick a random player 0,1,2,3
		randomPlayer = (rand()% 4);
		//Random number of players 2,3,4
		numPlayers = (rand()% 3) + 2;
		if (randomPlayer > numPlayers - 1)
			numPlayers = randomPlayer + 1;
		//Initialize game
		runStatus = initializeGame(numPlayers, k, seed, &G);

		//Check if initialize successful
		assert(runStatus == 0);

		//Set player turn
		G.whoseTurn = randomPlayer;

		//Set random game state
		//Hand count 0-20
		G.handCount[randomPlayer] = (rand() % 21);
		//Deck count 10-100
		G.deckCount[randomPlayer] = (rand() % 91) + 10;
		//Discard count 0-20
		G.discardCount[randomPlayer] = (rand() % 21);
		//Played count 0-20
		G.playedCardCount = (rand() % 21);

		//Sets card to hand, deck, discard pile
		for(j = 0; j < G.handCount[randomPlayer]; j++)
		{
			G.hand[randomPlayer][j] = rand() % 27;
		}
		for(j = 0; j < G.deckCount[randomPlayer]; j++)
		{
			G.deck[randomPlayer][j] = rand() % 27;
		}
		for(j = 0; j < G.discardCount[randomPlayer]; j++)
		{
			G.discard[randomPlayer][j] = rand() % 27;
		}

		//Add a smithy card to be played
		G.hand[randomPlayer][G.handCount[randomPlayer]] = smithy;
		G.handCount[randomPlayer]++;

		//Set defaults for card counts
		int cardCount = G.handCount[randomPlayer];
		int pCardCount = G.playedCardCount;
		int dCardCount = G.discardCount[randomPlayer];
		int coinCount = 0;
		int deCardCount = G.deckCount[randomPlayer];

		//Loop through hand to count how many treasures for coin count
		for(j = 0; j < G.handCount[randomPlayer]; j++){
			if(G.hand[randomPlayer][j] == copper)
				coinCount++;
			else if(G.hand[randomPlayer][j] == silver)
				coinCount+=2;
			else if(G.hand[randomPlayer][j] == gold)
				coinCount+=3;
		}

		//Coin count check
		updateCoins(randomPlayer, &G, 0);
		assert(G.coins == coinCount);

		//Loops through the first 3 cards at the top of the deck for treasure cards
		for(j = G.deckCount[randomPlayer] - 1; j >= G.deckCount[randomPlayer] - 3; j--){
			if(G.deck[randomPlayer][j] == copper)
				coinCount++;
			else if(G.deck[randomPlayer][j] == silver)
				coinCount+=2;
			else if(G.deck[randomPlayer][j] == gold)
				coinCount+=3;
		}

		//Play smithyCard, add one to played pile, add (3-1) cards to hand count, remove 3 from deck count
		smithy_(G.handCount[randomPlayer]-1, &G);
		pCardCount++;
		cardCount+=2;
		deCardCount-=3;

		//Update coin count
		updateCoins(randomPlayer, &G, 0);


		if(G.handCount[randomPlayer] != cardCount)
			printf("randomtestcard.c: FAIL\r\nG.handCount[randomPlayer] == %d\r\nExpected:G.handCount[randomPlayer] == %d\r\n", G.handCount[randomPlayer], cardCount);
		if(G.playedCardCount != pCardCount)
			printf("randomtestcard.c: FAIL\r\nG.playedCardCount == %d\r\nExpected:G.playedCardCount == %d\r\n", G.playedCardCount, pCardCount);
		if(G.discardCount[randomPlayer] != dCardCount)
			printf("randomtestcard.c: FAIL\r\nG.discardCount[randomPlayer] == %d\r\nExpected:G.discardCount[randomPlayer] == %d\r\n", G.discardCount[randomPlayer], dCardCount);
		if(G.deckCount[randomPlayer] != deCardCount)
			printf("randomtestcard.c: FAIL\r\nG.deckCount == %d\r\nExpected:G.deckCount == %d\r\n", G.deckCount[randomPlayer], deCardCount);
		if(G.coins != coinCount)
			printf("randomtestcard.c: FAIL\r\nG.coins == %d\r\nExpected:G.coins == %d\r\n", G.coins, coinCount);

		//printf("All test passed for adventurer card, cardtest1.c\n");
		printf("All other test passed for adventurer card, randomtestadventurer.c, iteration %d\r\n\r\n", i+1);
		printf("--------------------\r\n\r\n");
	}
	return 0;
}