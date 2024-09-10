static HWND getTextItem(HWND comboBox) {
	COMBOBOXINFO cbi;
	ZeroMemory(&cbi, sizeof(cbi));
	cbi.cbSize = sizeof(cbi);
	GetComboBoxInfo(comboBox, &cbi);
	return cbi.hwndItem;
}