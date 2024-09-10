// main game logic goes in here 
void GamePlay::Game()
{
	Checks ck1;
	Checks ck2;
	Checks ck3;
	Poker a;
	

	int x = 24;
	int y = 3;

	duringhand = true;



	if (g == 0)
	{
		PlayerHandValue = 0;
		CpuHandValue = 0;
		result = "";

		system("cls");
		showc = false;
		shows = false;
		foldc = false;
		fold = " ";
		a.createhand(hand, 25, 40);
		a.createtable(tablehand, 5, 17);  // this will create the table, passing in the table hand, always pass in 5 and 7 for location
		Cards();//creating the hands  
		a.drawdefaultcpu(cpuhand, x, y);
		PlayerHandValue = ck1.DetermineHand(PlayerValues, psuits);// determine the player hand storing value in PlayerHandValue
		CpuHandValue = ck1.DetermineHand(cvalues, csuits);// determine the cpu hand storing value in CpuHandValue
		if (!showc)
		{
			chand = "?????";
		}
		if (!shows)
		{
			PressEnterToContinue = " ";
		}
		if (!foldc)
		{
			fold = " ";
		}
		random = rand() % 10;
		if (random < 3)
		{
			CpuFold(CpuHandValue);
		}
		Text(); // method to display the text on screen
		//
		//betting logic

		// method for cpu betting logic, passing in CpuHandValue to determine what it does
		bet = menu(); // storing the variable returned from menu class to bet
		Betting(bet); // player betting method passing in the value stored at bet
		CpuBetting(bet);


		g++;
		Game();
	}
	if (g == 1)
	{
		PlayerHandValue = 0;
		CpuHandValue = 0;
		result = "";
		system("cls");
		a.createhand(hand, 25, 40);
		if (!allin)
		{
			a.tablecards(deck, 9);
		}
		a.createtable(tablehand, 5, 17);
		a.createtable(tablehand, 5, 17);// this will create the table, passing in the table hand, always pass in 5 and 7 for location
		Cards();//creating the hands  
		a.drawdefaultcpu(cpuhand, x, y);
		PlayerHandValue = ck2.DetermineHand(PlayerValues, psuits);// determine the player hand storing value in PlayerHandValue
		CpuHandValue = ck2.DetermineHand(cvalues, csuits);// determine the cpu hand storing value in CpuHandValue
		if (!showc)
		{
			chand = "?????";
		}
		if (!shows)
		{
			PressEnterToContinue = " ";
		}
		if (!foldc)
		{
			fold = " ";
		}
		random = rand() % 10;
		if (random < 3)
		{
			CpuFold(CpuHandValue);
		}
		Text(); // method to display the text on screen
		//
		bet = menu(); // storing the variable returned from menu class to bet
		Betting(bet); // player betting method passing in the value stored at bet
		CpuBetting(bet);

		g = 2;
		//Game();
	}
	if (g == 2)
	{
		PlayerHandValue = 0;
		CpuHandValue = 0;
		result = "";

		system("cls");
		a.createhand(hand, 25, 40);
		if (!allin)
		{
			a.tablecards(deck, 10);
		}
		a.createtable(tablehand, 5, 17);  // this will create the table, passing in the table hand, always pass in 5 and 7 for location
		Cards();//creating the hands  
		a.drawdefaultcpu(cpuhand, x, y);
		PlayerHandValue = ck3.DetermineHand(PlayerValues, psuits);// determine the player hand storing value in PlayerHandValue
		CpuHandValue = ck3.DetermineHand(cvalues, csuits);// determine the cpu hand storing value in CpuHandValue
		if (!showc)
		{
			chand = "?????";
		}
		if (!shows)
		{
			PressEnterToContinue = " ";
		}
		if (!foldc)
		{
			fold = " ";
		}

		random = rand() % 10;
		if (random < 3)
		{
			CpuFold(CpuHandValue);
		}
		Text(); // method to display the text on screen
		//
		bet = menu(); // storing the variable returned from menu class to bet
		Betting(bet); // player betting method passing in the value stored at bet
		CpuBetting(bet);

		g = 3;
		//Game();
	}
	if (g == 3)
	{
		thirdhand();
	}
}