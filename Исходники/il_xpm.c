ILboolean XpmGetColour(ILubyte *Buffer, ILint Size, int Len, XpmPixel* Colours)
#endif
{
	ILint		i = 0, j, strLen = 0;
	ILubyte		ColBuff[3];
	char		Buff[1024];

	XpmPixel	Colour;
	ILubyte		Name[XPM_MAX_CHAR_PER_PIXEL];

	for ( ; i < Size; i++) {
		if (Buffer[i] == '\"')
			break;
	}
	i++;  // Skip the quotes.

	if (i >= Size)
		return IL_FALSE;

	// Get the characters.
	for (j = 0; j < Len; ++j) {
		Name[j] = Buffer[i++];
	}

	// Skip to the colour definition.
	for ( ; i < Size; i++) {
		if (Buffer[i] == 'c')
			break;
	}
	i++;  // Skip the 'c'.

	if (i >= Size || Buffer[i] != ' ') { // no 'c' found...assume black
#ifndef XPM_DONT_USE_HASHTABLE
		memset(Colour, 0, sizeof(Colour));
		Colour[3] = 255;
		XpmInsertEntry(Table, Name, Len, Colour);
#else
		memset(Colours[Name[0]], 0, sizeof(Colour));
		Colours[Name[0]][3] = 255;
#endif
		return IL_TRUE;
	}

	for ( ; i < Size; i++) {
		if (Buffer[i] != ' ')
			break;
	}

	if (i >= Size)
		return IL_FALSE;

	if (Buffer[i] == '#') {
		// colour string may 4 digits/color or 1 digit/color
		// (added 20040218) TODO: is isxdigit() ANSI???
		++i;
		while (i + strLen < Size && isxdigit(Buffer[i + strLen]))
			++strLen;

		for (j = 0; j < 3; j++) {
			if (strLen >= 10) { // 4 digits
				ColBuff[0] = Buffer[i + j*4];
				ColBuff[1] = Buffer[i + j*4 + 1];
			}
			else if (strLen >= 8) { // 3 digits
				ColBuff[0] = Buffer[i + j*3];
				ColBuff[1] = Buffer[i + j*3 + 1];
			}
			else if (strLen >= 6) { // 2 digits
				ColBuff[0] = Buffer[i + j*2];
				ColBuff[1] = Buffer[i + j*2 + 1];
			}
			else if(j < strLen) { // 1 digit, strLen >= 1
				ColBuff[0] = Buffer[i + j];
				ColBuff[1] = 0;
			}

			ColBuff[2] = 0; // add terminating '\0' char
			Colour[j] = (ILubyte)strtol((char*)ColBuff, NULL, 16);
		}
		Colour[3] = 255;  // Full alpha.
	}
	else {
		for (j = 0; i < Size; i++) {
			if (!isalnum(Buffer[i]))
				break;
			Buff[j++] = Buffer[i];
		}
		Buff[j] = 0;

		if (i >= Size)
			return IL_FALSE;

		if (!XpmPredefCol(Buff, &Colour))

			return IL_FALSE;
	}


#ifndef XPM_DONT_USE_HASHTABLE
	XpmInsertEntry(Table, Name, Len, Colour);
#else
	memcpy(Colours[Name[0]], Colour, sizeof(Colour));
#endif
	return IL_TRUE;
}