//=================================================
// Check if a level is done and print a message 
// regarding  the way the level was ended
//=================================================
bool TheMathGame::isLevelDone(){
	// at least 1 player is still alive
	bool alivePlayer = player1.isPlayerAlive() || player2.isPlayerAlive();
	// one of the players or the two of them are done
	bool playerNotDone = player1.getPlayerDone() || player2.getPlayerDone();

	// in case time is not up, at least 1 player is a live and players are not done yet
	if (clockTicksCurrentLevel < CLOCK_TICKS_PER_LEVEL && alivePlayer && !playerNotDone)
		return false;
	else{
		clear_screen();
		setTextColor(YELLOW);

		//=======================================================
		// according to the reason of ending the level, print
		// the appropriet message to the screen
		//=======================================================

		// case the times run out
		if (clockTicksCurrentLevel >= CLOCK_TICKS_PER_LEVEL){
			gotoxy(33, 12);
			cout << "Time is up!!!";
			gotoxy(29, 13);
			cout << "Try better next time!!";
		}
		// case both players are dead
		else if (!alivePlayer){
			gotoxy(28, 12);
			cout << "Both Players are dead!!!";
			gotoxy(29, 13);
			cout << "Try better next time!!";
		}
		// case that player 1 is done and player 2 not
		else if (player1.getPlayerDone() && !player2.getPlayerDone()){
			gotoxy(33, 12);
			cout << "Player1 WIN!!";
		}
		// case that player 2 is done and player 1 not
		else if (player2.getPlayerDone() && !player1.getPlayerDone()){
			gotoxy(33, 12);
			cout << "Player2 WIN!!";
		}
		// case that bothe players finished at the same time
		else{
			gotoxy(35, 12);
			cout << "Its a TIE";
		}

		setTextColor(WHITE);
		return true;
	}
}