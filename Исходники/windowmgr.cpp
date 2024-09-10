void WindowManager::setup() {
	//Set console font
	CONSOLE_FONT_INFOEX lpConsoleCurrentFontEx;
	lpConsoleCurrentFontEx.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	lpConsoleCurrentFontEx.dwFontSize.X = 12;
	lpConsoleCurrentFontEx.dwFontSize.Y = 12;
	lpConsoleCurrentFontEx.FontWeight = 700;
	lpConsoleCurrentFontEx.nFont = 1;
	lpConsoleCurrentFontEx.FontFamily = FF_DONTCARE;
	lstrcpyW(lpConsoleCurrentFontEx.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx ( GetStdHandle(STD_OUTPUT_HANDLE), false, &lpConsoleCurrentFontEx );
	
	//get handles and create screen buffers
	mStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleA = Console::createConsoleOutput();
	mConsoleB = Console::createConsoleOutput();
	mSwitch = true;

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (GetConsoleScreenBufferInfo(mStdHandle, &info) != 0) {
		mCurrentSize.X = (info.srWindow.Right - info.srWindow.Left) + 1;
		mCurrentSize.Y = (info.srWindow.Bottom - info.srWindow.Top) + 1;
	} else {
		mCurrentSize.X = 80;
		mCurrentSize.Y = 25;
	}

	//get current codepage and set new one, unicode
	mOldCodePage = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
}