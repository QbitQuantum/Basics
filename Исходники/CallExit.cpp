int main()
{
	char szLine[80]; DWORD nRead;
	printf("Started: %s\nPress Enter to continue: ", GetCommandLineA());
	ReadConsoleA(GetStdHandle(STD_INPUT_HANDLE), szLine, ARRAYSIZE(szLine), &nRead, NULL);
	ExitProcess(1);
	printf("Must not get here!!!\n");
    return 0;
}