void SetColor(unsigned char Fore, unsigned char Back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(Fore & 15)+(Back & 15)*16);
}