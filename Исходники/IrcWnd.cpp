CString CIrcWnd::StripMessageOfFontCodes(CString sTemp)
{
	sTemp = StripMessageOfColorCodes(sTemp);
	sTemp.Remove(_T('\002')); // 0x02 - BOLD
	//sTemp.Remove(_T('\003')); // 0x03 - COLOUR
	sTemp.Remove(_T('\017')); // 0x0f - RESET
	sTemp.Remove(_T('\026')); // 0x16 - REVERSE/INVERSE was once italic?
	sTemp.Remove(_T('\037')); // 0x1f - UNDERLINE
	return sTemp;
}