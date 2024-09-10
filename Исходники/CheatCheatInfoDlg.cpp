ACheatCheatInfoDlg::ACheatCheatInfoDlg(AWindowBase* parent,ACheatEntry* pEntry)
{
	m_editName   = new AEditBox;
	m_editEdit   = new AEditBox;

	m_pEntry = pEntry;
	m_bCurrentDesc = true;

	SetParent(parent);

	m_ModalDialogResultCode = DialogBox(
		GetModuleHandle(0),
		MAKEINTRESOURCE(IDD_EDITCHEATITEM),
		parent->GetHwnd(),
		(DLGPROC)GetWindowThunk()
	);
}