void setcolor(int fcolor, int bcolor)
{
	SetConsoleTextAttribute(
		GetStdHandle(STD_OUTPUT_HANDLE),
		(WORD)((bcolor << 4) | fcolor ));
}