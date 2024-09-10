wchar_t* Util::String::MbcsToUnicode(const char* pMbcs)
{
	int codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
	int nChar = MultiByteToWideChar(codepage, 0, pMbcs, -1, NULL,0);

	int nSize = nChar * sizeof(wchar_t) + 1;
	wchar_t* pwchBuffer = new wchar_t[nSize];

	nChar = MultiByteToWideChar(codepage, 0, pMbcs, -1, pwchBuffer, nSize);
	if(nChar == 0)
	{
		delete[] pwchBuffer;
		return NULL;
	}

	pwchBuffer[nChar]=0;

	return pwchBuffer;
}