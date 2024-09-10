bool ToolsOptionsWindow::SaveHotKeySettings ()
{
	char szEncHotkey[SIZE_NAME];
	ZeroMemory (szEncHotkey, SIZE_NAME);
	GetDlgItemText (m_hwnd, ID_UTETXTHOTENC, szEncHotkey, SIZE_NAME);

	char szDecHotkey[SIZE_NAME];
	ZeroMemory (szDecHotkey, SIZE_NAME);
	GetDlgItemText (m_hwnd, ID_UTETXTHOTDEC, szDecHotkey, SIZE_NAME);

	if (strlen (szEncHotkey) != 1) {
		MessageBox (NULL, "Please enter a valid Encryption Hotkey.", "Hotkey Invalid", MB_OK | MB_ICONEXCLAMATION);
		return false;
	} else {
		_strupr (szEncHotkey);
		m_registry.WriteStringSetting (UTEENCRYPTHOTKEY, szEncHotkey);
	}

	if (strlen (szDecHotkey) != 1) {
		MessageBox (NULL, "Please enter a valid Decryption Hotkey.", "Hotkey Invalid", MB_OK | MB_ICONEXCLAMATION);
		return false;
	} else {
		_strupr (szDecHotkey);
		m_registry.WriteStringSetting (UTEDECRYPTHOTKEY, szDecHotkey);
	}

	return true;
}