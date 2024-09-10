os_string CArcViewLayer::GetUniqueFieldName (LPCSTR pcName)
{
// als erstes einfach auf 10 Zeichen verkürzen und Eindeutigkeit prüfen
os_string strName (pcName, min(MAX_DBASEFIELDNAME_LEN, strlen(pcName)));
int iCurrNumber = 0;

	while (!IsUniqueName (strName)) {
	// letzte Zeichen einfach durch hochgezählte Ziffern ersetzen
	char cbCnt[32];

		_ltoa (++iCurrNumber, cbCnt, 10);
		strName = strName.substr (0, min(MAX_DBASEFIELDNAME_LEN, strName.size()) - (strlen(cbCnt) + 1)) + "_" + cbCnt;
	}
	return strName;
}