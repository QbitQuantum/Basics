static int GetWordFromConsolePack(TConsoleParams *params)
{
	int WordLen=0;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut != INVALID_HANDLE_VALUE) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
			COORD CurPos;
			CurPos.X = csbi.srWindow.Left + (SHORT)(params->Pt.x * (csbi.srWindow.Right - csbi.srWindow.Left + 1) / params->ClientRect.right);
			CurPos.Y = csbi.srWindow.Top + (SHORT)(params->Pt.y * (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / params->ClientRect.bottom);
			if ((CurPos.X >= 0) && (CurPos.X <= csbi.dwSize.X - 1) && (CurPos.Y >= 0) && (CurPos.Y <= csbi.dwSize.Y - 1)) {
				int BegPos;
				WCHAR *Buf;

				params->BeginPos = CurPos.X;
				CurPos.X = 0;
				Buf = GlobalAlloc(GMEM_FIXED, (csbi.dwSize.X + 1)*sizeof(WCHAR));
				if (Buf) {
					DWORD ActualRead;
					if ((ReadConsoleOutputCharacterW(hStdOut, Buf, csbi.dwSize.X, CurPos, &ActualRead)) && (ActualRead == (DWORD)csbi.dwSize.X)) {
						BegPos=0;
						WordLen=ActualRead;
						if(WordLen>85) {
							while(params->BeginPos-BegPos>43 && WordLen>85) {
								BegPos++; WordLen--;
							}
							if(WordLen>85) WordLen=85;
							params->BeginPos -= BegPos;
						}
						if(WordLen) {
							memset(params->Buffer, 0, sizeof(params->Buffer));
							lstrcpynW(params->Buffer, Buf + BegPos, WordLen+1);
						}
					}
					GlobalFree(Buf);
				}
			}
		}
	}
	return WordLen;
}