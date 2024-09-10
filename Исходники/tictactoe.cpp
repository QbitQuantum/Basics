void main(){
	char nice='y';
	while(nice == 'y'){
		char winner = 'N';
		bool turn=true, validty;
		int move, counter=1, i, m=49;
		char board[9];
		for (i=0; i<9; i++){
			board[i] = m;
			m++;
		}
		PrintBoard(board);
		while (winner == 'N'){
			printf("Where do you want to go? Pick an available number: ");
			scanf("%d", &move);
			validty = IsValidMove(board, move-1);
			while (validty==false || board[move-1]=='X' || board[move-1]=='O'){
				printf("INVALID MOVE. PICK AGAIN.\n");
				printf("Where do you want to go? Pick an available number: ");
				scanf("%d", &move);
				validty = IsValidMove(board, move-1);
			}
			if (turn)
				board[move-1] = 'X';
			else
				board[move-1] = 'O';
			PrintBoard(board);
			winner = WinnerIfAny(board);
			if (counter==9 && winner=='N')
				winner = 'S';
			turn = !turn;
			counter++;
		}
		if(winner != 'S')
			printf("CONGRATULATIONS PLAYER %c!!! YOU WON!!!\n", winner);
		else
			printf("STAKENATE!!!\n");
		printf("Would you like to play another game?(y/n):");
		flushall();
		scanf("%c", &nice);
	}
}