//Issue 60: BUGBUG: На некоторых системых (Win2k3, WinXP) SetConsoleCP (и иже с ними) просто зависают
//Поэтому выполняем в отдельном потоке, и если он завис - просто зовем TerminateThread
static DWORD WINAPI OurSetConsoleCPThread(LPVOID lpParameter)
{
	UINT nCP = (UINT)lpParameter;
	SetConsoleCP(nCP);
	SetConsoleOutputCP(nCP);
	return 0;
}