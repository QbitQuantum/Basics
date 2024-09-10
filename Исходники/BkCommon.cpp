void GetLegalFileName(LPCTSTR lpName, LPSTR lpBuf, int nBuf)
{
	LPSTR lpPtr = lpBuf;
	LPCTSTR lpSub = lpName;
	int nLen = 0;
	while (*(LPBYTE)lpSub <= (BYTE)'\x20') lpSub++;
	while (*lpSub) {
		char c = *lpSub++;
		nLen++;
		if ((lpPtr - lpBuf) >= nBuf-3) {
			break;
		}
		if (_ismbblead(c)) {
			*lpPtr++ = c;
			*lpPtr++ = *lpSub;
			nLen++;
			if (*lpSub == '\0') break;
			else lpSub++;
		} else if ((BYTE)c < (BYTE)'\x20') {
			c = ' ';
			*lpPtr++ = c;
		} else {
			switch (c) {
			case '*':
			case '<':
			case '>':
			case '?':
			case '\\':
			case '|':
			case '/':
				c = '=';
				break;
			case ':':
				c = ';';
				break;
			case '\"':
				c = '\'';
				break;
			default:
				break;
			}
			*lpPtr++ = c;
		}
	}
	while (nLen && (*(lpPtr-1) == '.' || *(lpPtr-1) == ' ')) {
		lpPtr--;
		nLen--;
	}
	*lpPtr++ = '\0';
	if (*lpBuf == '\0') {
		strcpy(lpBuf, "(noname)");
	}
}