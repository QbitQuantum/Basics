String FileZip::GetS()
{
	// Check parameters
	if (m_cZipFile.IsFileOpen()) {
		// Read string
		char szString[2048];
		char *pszPos = szString;
		int   nChar = GetC();
		while (nChar >= 0 && nChar != 10) {
			// Concatenate char to string
			*pszPos = static_cast<char>(nChar);
			pszPos++;

			// Read next character
			nChar = GetC();
		}

		// Terminate string
		if (nChar == 10) {
			*pszPos = '\n';
			pszPos++;
		}
		*pszPos = 0;

		// Return string
		if (pszPos > szString || nChar != -1)
			return szString;
	}

	// Error!
	return "";
}