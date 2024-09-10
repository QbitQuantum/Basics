void CUIGameLog::AddChatMessage(LPCSTR msg, LPCSTR author){
	string256 fullLine;
	sprintf_s(fullLine, "%s %s", author, msg);
	_TrimRight	(fullLine);
    
	CUIStatic* pItem = NULL;

	pItem = xr_new<CUIStatic>();
	pItem->SetTextComplexMode		(true);
	pItem->SetText(fullLine);
    pItem->m_pLines->SetCutWordsMode(true);
	pItem->SetFont(GetFont());
	pItem->SetTextColor(txt_color);
	pItem->SetClrAnimDelay(5000.0f);
	pItem->SetClrLightAnim(CHAT_LOG_ITEMS_ANIMATION, false, true, true, true);	
	pItem->SetWidth(this->GetDesiredChildWidth());
	pItem->AdjustHeightToText();
	AddWindow(pItem, true);	
}