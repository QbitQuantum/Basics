// Game::Next step
void Game::NextStep() {
	char tmp[256];
	int choice;

	if( enemy == NULL ) {
		if( (GameMode == 1 || NextPlayer == 1 && GameMode != MODE_NET_CLIENT) || (GameMode == MODE_NET_CLIENT && NextPlayer == 2) ) {
			printf("Player %d (1-9): ", NextPlayer);
			memset(tmp,0,256);
			#ifdef _WIN32
			scanf_s("%s", tmp);
			#else
			scanf("%s", tmp);
			#endif
			choice = atoi(tmp);

			if(choice<1 || choice>9 || Board[choice-1] != 3)
				return;

			Board[choice-1] = (char) (NextPlayer - 1);
		}
	}

	switch(GameMode) {
		case 1:
			if(NextPlayer == 1) {
				NextPlayer = 2;
			} else {
				NextPlayer = 1;
			}
			break;

		case 2:
			if(NextPlayer == 2) {
				printf("Enemy is thinkin'...\n");
				Board[enemy->Analyze(Board)] = 1;
				NextPlayer = 1;
			} else {
				NextPlayer = 2;
			}
			break;

		case MODE_NET_HOST:
			if( NextPlayer == 2 ) {
				printf("Waiting for Player 2...\n");
				recv(this->Server->GetClient(), tmp, 1, 0);
				Board[atoi(tmp)-1] = 1;
				NextPlayer = 1;
			} else {
				send(this->Server->GetClient(), Board, 9,0);
				NextPlayer = 2;
			}
			break;

		case MODE_NET_CLIENT:
			if( NextPlayer == 1 ) {
				printf("Waiting for Player 1...\n");
				recv(this->Client->GetClient(), Board, 9, 0);
				NextPlayer = 2;
			} else {
				Board[atoi(tmp)-1] = 1;
				send(this->Client->GetClient(), tmp, 1, 0);
				NextPlayer = 1;
			}
			break;

		default:
			break;
	}
}