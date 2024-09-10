void DOHexEditor::copy()
{
	if(!canCopy()) return;

	std::string text;
	if(mInData)
	{
		U32 start = getProperSelectionStart();
		U32 end = getProperSelectionEnd();
		for(U32 i = start; i < end; i++)
			text.append(llformat("%02X", mValue[i]));
	}
	else
	{
		U32 start = getProperSelectionStart();
		U32 end = getProperSelectionEnd();
		for(U32 i = start; i < end; i++)
			text.append(llformat("%c", mValue[i]));
	}
	LLWString wtext = utf8str_to_wstring(text);
	gClipboard.copyFromSubstring(wtext, 0, wtext.length());
}