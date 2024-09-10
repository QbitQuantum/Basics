int ComputerPlayer::getMove(int configurationMaskSelf, int configurationMaskOpponent){
	_sleep(1000);
	//check if the player is one move away from winning
	for(int i = 0 ; i < 24 ; i++){
		if((configurationMaskSelf & OneMoveFromWinMasks[i]) == OneMoveFromWinMasks[i]){ //is the current configuration one move away from winning?
			if(((configurationMaskSelf | configurationMaskOpponent) & mask(WinningMove[i])) != mask(WinningMove[i])){ //is the winning move position unoccupied?
				return WinningMove[i];
			}
		}
	}
	for(int i = 0 ; i < 24 ; i++){
		if((configurationMaskOpponent & OneMoveFromWinMasks[i]) == OneMoveFromWinMasks[i]){ //is the current configuration one move away from winning?
			if(((configurationMaskOpponent | configurationMaskSelf) & mask(WinningMove[i])) != mask(WinningMove[i])){ //is the winning move position unoccupied?
				return WinningMove[i];
			}
		}
	}
	//otherwise just return a random space
	while(true){
		int move = 0;
		move = (rand() % 9) + 1;
		if(((configurationMaskOpponent | configurationMaskSelf) & mask(move)) != mask(move)) return move;
	}
	return 0;
}