void GameInterface::AttachInterface(GameStatus gameStatus)
{
	int gotoX;
	int gotoY;
	int currentY;
	int menuSelector = 0;
	switch (gameStatus)
	{
	case TITLE:
		gotoX = 0;
		gotoY = 10;
		while (!_kbhit())
		{
			Sleep(600);
			SetCursorPosition(gotoX, gotoY);
			printf_s("\t\t\t     PRESS ENTER KEY TO START      \t\t\t");
			Sleep(1000);
			SetCursorPosition(gotoX, gotoY);
			printf_s("                                                                            ");
		}
		getchar();
		break;
	case SELECT_PLAYER:
		gotoX = 22;
		gotoY = 9;
		currentY = gotoY + 6;
		SetColor(BLACK, WHITE);
		SetCursorPosition(gotoX, gotoY);
		printf_s("                  \n");
		SetCursorPosition(gotoX, gotoY + 1);
		printf_s("   PLAYER SELECT  \n");
		SetCursorPosition(gotoX, gotoY + 2);
		printf_s("                  ");
		SetColor(WHITE, BLACK);
		SetCursorPosition(gotoX + 7, gotoY + 6);
		printf_s("VS Friend");
		SetCursorPosition(gotoX + 7, gotoY + 9);
		printf_s("VS AI");
		SetCursorPosition(gotoX + 7, gotoY + 12);
		printf_s("VS Network");
		SetCursorPosition(gotoX - 1, currentY);
		printf_s("¢º");
		menuSelector = MenuSelect(3, gotoX, gotoY, currentY, gameStatus);
		if (menuSelector == 0)
		{
			m_GameType = PVP_PLAY;
		}
		else if (menuSelector == 1)
		{
			m_GameType = AI_PLAY;
		}
		else if (menuSelector == 2)
		{
			m_GameType = NET_PLAY;
		}
		break;
	case SELECT_MAP_SHIP:
		gotoX = 4;
		gotoY = 9;
		currentY = gotoY + 5;
		SetColor(BLACK, WHITE);
		SetCursorPosition(gotoX + 18, gotoY);
		printf_s("                  \n");
		SetCursorPosition(gotoX + 18, gotoY + 1);
		printf_s("    SHIP SELECT   \n");
		SetCursorPosition(gotoX + 18, gotoY + 2);
		printf_s("                  ");
		SetColor(WHITE, BLACK);
		SetCursorPosition(gotoX + 6, gotoY + 5);
		printf_s("Map size");
		SetCursorPosition(gotoX + 6, gotoY + 8);
		printf_s("Aircraft Carrier");
		SetCursorPosition(gotoX + 6, gotoY + 11);
		printf_s("Battleship");
		SetCursorPosition(gotoX + 6, gotoY + 14);
		printf_s("Cruiser");
		SetCursorPosition(gotoX + 6, gotoY + 17);
		printf_s("Destroyer");
		SetColor(BLACK, WHITE);
		SetCursorPosition(gotoX + 18, gotoY + 20);
		printf_s("                   \n");
		SetCursorPosition(gotoX + 18, gotoY + 21);
		printf_s("      N E X T      \n");
		SetCursorPosition(gotoX + 18, gotoY + 22);
		printf_s("                   ");
		SetColor(WHITE, BLACK);
		SetCursorPosition(gotoX + 40, gotoY + 5);
		printf_s("¢¸ %d*%d ¢º", m_MapSize, m_MapSize);
		SetCursorPosition(gotoX + 40, gotoY + 8);
		printf_s("¢¸  %d  ¢º", m_NumShip[0]);
		SetCursorPosition(gotoX + 40, gotoY + 11);
		printf_s("¢¸  %d  ¢º", m_NumShip[1]);
		SetCursorPosition(gotoX + 40, gotoY + 14);
		printf_s("¢¸  %d  ¢º", m_NumShip[2]);
		SetCursorPosition(gotoX + 40, gotoY + 17);
		printf_s("¢¸  %d  ¢º", m_NumShip[3]);
		SetCursorPosition(gotoX, currentY);
		printf_s("¢º");
		menuSelector = MenuSelect(6, gotoX, gotoY, currentY, gameStatus);
		break;
	case SET_SHIP:
		gotoX = (m_MapSize + 3) * 4 + 4;
		gotoY = 7;
		currentY = gotoY + 5;
		SetCursorPosition(gotoX + 6, gotoY + 5);
		printf_s("Manual Set");
		SetCursorPosition(gotoX + 6, gotoY + 8);
		printf_s("Random Set");
		SetCursorPosition(gotoX, currentY);
		printf_s("¢º");
		SetColor(BLACK, WHITE);
		SetCursorPosition(gotoX + 2, gotoY + 12);
		printf_s("                  \n");
		SetCursorPosition(gotoX + 2, gotoY + 13);
		printf_s("    Start Game    \n");
		SetCursorPosition(gotoX + 2, gotoY + 14);
		printf_s("                  \n");
		SetCursorPosition(gotoX + 2, gotoY + 17);
		printf_s("                  \n");
		SetCursorPosition(gotoX + 2, gotoY + 18);
		printf_s("       Reset      \n");
		SetCursorPosition(gotoX + 2, gotoY + 19);
		printf_s("                  ");
		SetColor(WHITE, BLACK);
		menuSelector = MenuSelect(2, gotoX, gotoY, currentY, gameStatus);
		if (menuSelector == 0)
		{
			m_ManualOrRandom = true;
		}
		else if (menuSelector == 1)
		{
			m_ManualOrRandom = false;
		}
		SetColor(WHITE, BLACK);
		break;
	case GAMEPLAY:
		break;
	case WIN:
		gotoX = 3;
		gotoY = 13;
		currentY = 0;
		SetColor(BLACK, GREEN);
		SetCursorPosition(gotoX, gotoY);
		printf_s("                \n");
		SetCursorPosition(gotoX, gotoY + 1);
		printf_s("    To Title    \n");
		SetCursorPosition(gotoX, gotoY + 2);
		printf_s("  (New Setting) \n");
		SetCursorPosition(gotoX, gotoY + 3);
		printf_s("                ");
		SetColor(BLACK, WHITE);
		SetCursorPosition(gotoX + 20, gotoY);
		printf_s("                \n");
		SetCursorPosition(gotoX + 20, gotoY + 1);
		printf_s("   Play Again   \n");
		SetCursorPosition(gotoX + 20, gotoY + 2);
		printf_s(" (Same Setting) \n");
		SetCursorPosition(gotoX + 20, gotoY + 3);
		printf_s("                ");
		SetCursorPosition(gotoX + 40, gotoY);
		printf_s("                \n");
		SetCursorPosition(gotoX + 40, gotoY + 1);
		printf_s("      Quit      \n");
		SetCursorPosition(gotoX + 40, gotoY + 2);
		printf_s("      Game      \n");
		SetCursorPosition(gotoX + 40, gotoY + 3);
		printf_s("                ");
		SetColor(WHITE, BLACK);
		m_LastMenu = MenuSelect(3, gotoX, gotoY, currentY, gameStatus);
		break;
	case LOSE:
		gotoX = 6;
		gotoY = 13;
		currentY = 0;
		SetColor(BLACK, GREEN);
		SetCursorPosition(gotoX, gotoY);
		printf_s("                \n");
		SetCursorPosition(gotoX, gotoY + 1);
		printf_s("    To Title    \n");
		SetCursorPosition(gotoX, gotoY + 2);
		printf_s("  (New Setting) \n");
		SetCursorPosition(gotoX, gotoY + 3);
		printf_s("                ");
		SetColor(BLACK, WHITE);
		SetCursorPosition(gotoX + 20, gotoY);
		printf_s("                \n");
		SetCursorPosition(gotoX + 20, gotoY + 1);
		printf_s("   Play Again   \n");
		SetCursorPosition(gotoX + 20, gotoY + 2);
		printf_s(" (Same Setting) \n");
		SetCursorPosition(gotoX + 20, gotoY + 3);
		printf_s("                ");
		SetCursorPosition(gotoX + 40, gotoY);
		printf_s("                \n");
		SetCursorPosition(gotoX + 40, gotoY + 1);
		printf_s("      Quit      \n");
		SetCursorPosition(gotoX + 40, gotoY + 2);
		printf_s("      Game      \n");
		SetCursorPosition(gotoX + 40, gotoY + 3);
		printf_s("                ");
		SetColor(WHITE, BLACK);
		m_LastMenu = MenuSelect(3, gotoX, gotoY, currentY, gameStatus);
		break;
	}
}