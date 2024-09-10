void ConvertKeyToCurrentKeyboard(char* sNewKey, char* sOldKey, int nNewKeyMaxSize)
{
	if (_mbstrlen(sOldKey) == 1)
	{
		HKL nDefaultKeyboard = GetKeyboardLayout(0);

		SHORT nCharCode = sOldKey[0];

		if ((nCharCode > 0) && (nCharCode <= 255))
		{
			SHORT nScanCode = g_pEnglishCharToScanCodeTable[nCharCode];

			if (nScanCode != -1)
			{
				SHORT nKeyCode2 = MapVirtualKeyEx(nScanCode & 0xff, 1, nDefaultKeyboard);

				if (nKeyCode2 != -1)
				{
					UINT nNewChar = MapVirtualKeyEx( nKeyCode2 & 0xff, 2, nDefaultKeyboard);

					if (nNewChar != 0)
					{
						sNewKey[0] = (char)nNewChar;
						sNewKey[1] = '\0';
						return;
					}
				}
			}
		}
	}

	_mbsncpy((unsigned char*)sNewKey, (const unsigned char*)sOldKey, nNewKeyMaxSize);
	sNewKey[nNewKeyMaxSize-1] = '\0';
}