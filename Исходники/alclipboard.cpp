bool AlClipboard::writeToClipboard(char *pKey)
{
	logger->debug("AlClipboard::writeToClipboard:-- START\n");

	char tbuf[128];
	ZeroMemory(tbuf, sizeof(char) * 128);

	char tbuf2[128];
	ZeroMemory(tbuf2, sizeof(char) * 128);
	sprintf(tbuf, "%s/%s\0", DEFAULT_DIRECTORY_NAME, pKey);
	sprintf(tbuf2, "\t reading... '%s'\n\0", tbuf);
	logger->debug(tbuf2);
	FILE *fle = fopen(tbuf, "rt");
	if (!fle)
	{
		sprintf(tbuf2, "\t Opening file '%s' failed.\n\0", tbuf);
		logger->debug(tbuf2);
		return false;
	}
	fseek(fle, 0, SEEK_END);
	int maxSize = ftell(fle);
	fclose(fle);

	sprintf(tbuf2, "\t File size: '%i'.\n\0", maxSize);
	logger->debug(tbuf2);
	if (maxSize < 1)
	{
		sprintf(tbuf2, "\t file too small.\n\0", tbuf);
		logger->debug(tbuf2);
		return false;
	}

	char *pBuffer = NULL;
	pBuffer = new char[maxSize+1];
	ZeroMemory(pBuffer, sizeof(char) * (maxSize+1));
	if (!readFromDisk(pKey, pBuffer, maxSize))
	{
		return false;
	}

	if (!OpenClipboard(NULL))
	{
		logger->debug("\t OpenClipboard.. FAILED..\n");
		return false;
	}

	EmptyClipboard();
	HGLOBAL hClipboardData;
	hClipboardData = GlobalAlloc(GMEM_DDESHARE, maxSize+1);
	char * pchData;
	pchData = (char*)GlobalLock(hClipboardData);
	strcpy(pchData, pBuffer);
	GlobalUnlock(hClipboardData);
	SetClipboardData(CF_TEXT, hClipboardData);


	logger->debug("\t CloseClipboard()");
	CloseClipboard();
	SAFE_DEL(pBuffer);
	return true;
}