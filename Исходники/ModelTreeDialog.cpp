BOOL ModelTreeDialog::doInitDialog(HWND hKbControl)
{
	RECT optionsRect;
	RECT clientRect;

	m_colorButton = new CUIColorButton(GetDlgItem(hWindow,
		IDC_HIGHLIGHT_COLOR), MODEL_TREE_CUST_COLORS_KEY, m_highlightR,
		m_highlightG, m_highlightB);
	setIcon(IDI_APP_ICON);
	m_hTreeView = GetDlgItem(hWindow, IDC_MODEL_TREE);
	m_resizer = new CUIWindowResizer;
	m_resizer->setHWindow(hWindow);
	m_resizer->addSubWindow(IDC_MODEL_TREE,
		CUISizeHorizontal | CUISizeVertical);
	m_resizer->addSubWindow(IDC_SHOW_BOX, CUIFloatLeft | CUIFloatBottom);
	m_resizer->addSubWindow(IDC_OPTIONS, CUIFloatLeft | CUIFloatTop);
	m_resizer->addSubWindow(IDC_HIGHLIGHT, CUIFloatRight | CUIFloatTop);
	m_resizer->addSubWindow(IDC_HIGHLIGHT_COLOR, CUIFloatRight | CUIFloatTop);
	m_lineChecks.resize(LDLLineTypeUnknown + 1);
	setupLineCheck(IDC_COMMENT, LDLLineTypeComment);
	setupLineCheck(IDC_MODEL, LDLLineTypeModel);
	setupLineCheck(IDC_LINE, LDLLineTypeLine);
	setupLineCheck(IDC_TRIANGLE, LDLLineTypeTriangle);
	setupLineCheck(IDC_QUAD, LDLLineTypeQuad);
	setupLineCheck(IDC_CONDITIONAL, LDLLineTypeConditionalLine);
	setupLineCheck(IDC_EMPTY, LDLLineTypeEmpty);
	setupLineCheck(IDC_UNKNOWN, LDLLineTypeUnknown);
	//m_hResizeGrip = CUIWindowResizer::createResizeGrip(hWindow);
	//positionResizeGrip(m_hResizeGrip);
	GetWindowRect(GetDlgItem(hWindow, IDC_SHOW_BOX), &optionsRect);
	screenToClient(hWindow, &optionsRect);
	GetClientRect(hWindow, &clientRect);
	m_optionsDelta = clientRect.right - optionsRect.left;
	minWidth = clientRect.right;
	minHeight = clientRect.bottom;
	if (!TCUserDefaults::boolForKey(MODEL_TREE_OPTIONS_SHOWN_KEY, true, false))
	{
		hideOptions();
	}
	checkSet(IDC_HIGHLIGHT, m_highlight);
	initStatusBar();
	setAutosaveName("ModelTreeDialog");
	return CUIDialog::doInitDialog(hKbControl);
}