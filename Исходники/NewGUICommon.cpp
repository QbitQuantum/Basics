void NewGUI_ComboBox_GetInfo(HWND hComboBox, HWND* phComboBox,
	HWND* phEditBox, HWND* phListBox)
{
	COMBOBOXINFO cbi;
	ZeroMemory(&cbi, sizeof(COMBOBOXINFO));
	cbi.cbSize = sizeof(COMBOBOXINFO);
	VERIFY(GetComboBoxInfo(hComboBox, &cbi));

	if(phComboBox != NULL) *phComboBox = cbi.hwndCombo;
	if(phEditBox != NULL) *phEditBox = cbi.hwndItem;
	if(phListBox != NULL) *phListBox = cbi.hwndList;
}