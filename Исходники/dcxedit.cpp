DcxEdit::DcxEdit(const UINT ID, DcxDialog *p_Dialog, const HWND mParentHwnd, const RECT *rc, TString &styles)
: DcxControl(ID, p_Dialog)
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles(styles, &Styles, &ExStyles, &bNoTheme);

	this->m_Hwnd = CreateWindowExW(
		ExStyles | WS_EX_CLIENTEDGE, 
		L"EDIT",
		NULL,
		WS_CHILD | Styles,
		rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top,
		mParentHwnd,
		(HMENU) ID,
		GetModuleHandle(NULL), 
		NULL);

	if (!IsWindow(this->m_Hwnd))
		throw "Unable To Create Window";

	if (bNoTheme)
		Dcx::UXModule.dcxSetWindowTheme(this->m_Hwnd , L" ", L" ");

	Edit_LimitText(this->m_Hwnd, 0);
	//this->m_tsText = "";

	//SendMessage(this->m_Hwnd, CCM_SETUNICODEFORMAT, TRUE, NULL);

	if (p_Dialog->getToolTip() != NULL) {
		if (styles.istok("tooltips")) {
			this->m_ToolTipHWND = p_Dialog->getToolTip();
			AddToolTipToolInfo(this->m_ToolTipHWND, this->m_Hwnd);
		}
	}

	this->m_bIgnoreRepeat = TRUE;
	this->setControlFont((HFONT) GetStockObject(DEFAULT_GUI_FONT), FALSE);
	this->registreDefaultWindowProc();
	SetProp(this->m_Hwnd, "dcx_cthis", (HANDLE) this);
	DragAcceptFiles(this->m_Hwnd, TRUE);
}