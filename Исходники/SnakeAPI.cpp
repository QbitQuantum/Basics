void SnakeAPI::clear(bool clearAttribute, char ch)
{
	getInfo();

	DWORD cCharsWritten;
	DWORD size = CSBI.dwSize.X * CSBI.dwSize.Y;
	COORD coord = {0, 0};
	FillConsoleOutputCharacterA(hSnakeAPI, ch, size, coord, &cCharsWritten);

	int attrib = CSBI.wAttributes;
	if (clearAttribute) 
		attrib = LIGHTGRAY;
	FillConsoleOutputAttribute(hSnakeAPI, attrib, size, coord, &cCharsWritten);

	SetConsoleCursorPosition(hSnakeAPI, coord);
	getInfo();
}