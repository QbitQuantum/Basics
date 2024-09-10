void textColor(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo; 
    SetConsoleTextAttribute(hConsole, color);
}