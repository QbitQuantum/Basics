void CTextConsoleWin32::UpdateStatus()
{
	COORD coord;
	DWORD dwWritten = 0;
	WORD wAttrib[ 80 ];

	for (int i = 0; i < 80; i++)
	{
		wAttrib[i] = Attrib; // FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;
	}

	coord.X = coord.Y = 0;

	WriteConsoleOutputAttribute(houtput, wAttrib, 80, coord, &dwWritten);
	WriteConsoleOutputCharacter(houtput, statusline, 80, coord, &dwWritten);
}