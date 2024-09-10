/***************************************************************************
 Function:	StrHexCmp 16进制字符串比较
 Param：     str1 str2 要比对的字符串 ，格式：01030001 16进制字符串
 bFull true 严格一致
 false 遇到** 二个星 认为与任何字符都相同
 Returns:	true 一致 false不一致
 ***************************************************************************/
bool TDataSwitch::StrHexCmp(AnsiString str1, AnsiString str2, bool bFull) {
	if (str1.Length() != str2.Length())
		return false;

	for (int i = 0; i < str1.Length() / 2; i++) {

		if (bFull) {
			if (str1.SubString(i * 2 + 1, 2) != str2.SubString(i * 2 + 1, 2))
				return false;

		}
		else if (str1.SubString(i * 2 + 1, 2) != "**" && str2.SubString
			(i * 2 + 1, 2) != "**") {

			AnsiString tmp1 = str1.SubString(i * 2 + 1, 2);
			AnsiString tmp2 = str2.SubString(i * 2 + 1, 2);
			if (str1.SubString(i * 2 + 1, 2) != str2.SubString(i * 2 + 1, 2))
				return false;
		}
	}

	return true;
}