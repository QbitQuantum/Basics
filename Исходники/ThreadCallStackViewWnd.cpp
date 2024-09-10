CThreadCallStackViewWnd::CThreadCallStackViewWnd(HWND parentWindow) 
: CDialog(MAKEINTRESOURCE(IDD_DEBUG_THREADCALLSTACK), parentWindow)
, m_hasSelection(false)
, m_selectedAddress(0)
{
	SetClassPtr();

	m_okButton			= new Framework::Win32::CButton(GetItem(IDOK));
	m_cancelButton		= new Framework::Win32::CButton(GetItem(IDCANCEL));
	m_callStackItemList = new Framework::Win32::CListBox(GetItem(IDC_CALLSTACKITEM_LIST));

	RECT buttonSize;
	SetRect(&buttonSize, 0, 0, 75, 16);
	MapDialogRect(m_hWnd, &buttonSize);
	unsigned int buttonWidth = buttonSize.right - buttonSize.left;
	unsigned int buttonHeight = buttonSize.bottom - buttonSize.top;

	m_layout = 
		Framework::VerticalLayoutContainer
		(
			Framework::LayoutExpression(Framework::Win32::CLayoutWindow::CreateCustomBehavior(100, 20, 1, 1, m_callStackItemList)) +
			Framework::HorizontalLayoutContainer
			(
				Framework::LayoutExpression(Framework::Win32::CLayoutWindow::CreateButtonBehavior(buttonWidth, buttonHeight, m_okButton)) +
				Framework::LayoutExpression(Framework::CLayoutStretch::Create()) +
				Framework::LayoutExpression(Framework::Win32::CLayoutWindow::CreateButtonBehavior(buttonWidth, buttonHeight, m_cancelButton))
			)
		);

	{
		RECT rc = GetClientRect();
		m_layout->SetRect(rc.left + 10, rc.top + 10, rc.right - 10, rc.bottom - 10);
		m_layout->RefreshGeometry();
	}
}