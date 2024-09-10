HRESULT CTTS::InitTokenList(HWND hWnd, BOOL bIsComboBox)
{
	if (bIsComboBox)
		return SpInitTokenComboBox(hWnd, SPCAT_RECOGNIZERS);
	else
		return SpInitTokenListBox(hWnd, SPCAT_RECOGNIZERS);
}