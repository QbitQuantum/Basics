void GoToPos(int x, int y)
{
	COORD cur={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cur);
}