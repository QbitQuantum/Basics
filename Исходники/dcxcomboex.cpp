DcxComboEx::DcxComboEx( UINT ID, DcxDialog * p_Dialog, HWND mParentHwnd, RECT * rc, TString & styles ) 
: DcxControl( ID, p_Dialog )
{
	LONG Styles = 0, ExStyles = 0;
	BOOL bNoTheme = FALSE;
	this->parseControlStyles( styles, &Styles, &ExStyles, &bNoTheme );

	this->m_Hwnd = CreateWindowEx(	
		ExStyles,
		DCX_COMBOEXCLASS,
		NULL,
		WS_CHILD | CBS_AUTOHSCROLL | Styles,
		rc->left, rc->top, rc->right - rc->left, rc->bottom - rc->top,
		mParentHwnd,
		(HMENU) ID,
		GetModuleHandle(NULL),
		NULL);

	if (!IsWindow(this->m_Hwnd))
		throw "Unable To Create Window";

	if ( bNoTheme ) {
		Dcx::UXModule.dcxSetWindowTheme( this->m_Hwnd , L" ", L" " );
		//SendMessage( this->m_Hwnd, CBEM_SETWINDOWTHEME, NULL, (LPARAM)(LPCWSTR)L" "); // do this instead?
	}

	this->m_EditHwnd = (HWND) this->getEditControl( );

	if ( IsWindow( this->m_EditHwnd ) ) {
		if ( bNoTheme )
			Dcx::UXModule.dcxSetWindowTheme( this->m_EditHwnd , L" ", L" " );

		try {
			LPDCXCOMBOEXEDIT lpce = new DCXCOMBOEXEDIT;

			lpce->cHwnd = this->m_Hwnd;
			lpce->pHwnd = mParentHwnd;

			//SetWindowLong( this->m_EditHwnd, GWL_STYLE, GetWindowLong( this->m_EditHwnd, GWL_STYLE ));// | ES_AUTOHSCROLL );
			lpce->OldProc = SubclassWindow( this->m_EditHwnd, DcxComboEx::ComboExEditProc );
			SetWindowLongPtr( this->m_EditHwnd, GWLP_USERDATA, (LONG) lpce );
		}
		catch ( std::bad_alloc ) {
			DestroyWindow(this->m_Hwnd);
			throw "Unable to Allocate Memory";
		}
	}

	HWND combo = (HWND)SendMessage(this->m_Hwnd,CBEM_GETCOMBOCONTROL,0,0);
	if (IsWindow(combo)) {
		if (bNoTheme)
			Dcx::UXModule.dcxSetWindowTheme( combo , L" ", L" " );

		COMBOBOXINFO cbi = { 0 };
		cbi.cbSize = sizeof(cbi);
		GetComboBoxInfo(combo, &cbi);

		if (styles.istok("sort")) { // doesnt work atm.
			if (IsWindow(cbi.hwndList)) {
				AddStyles(cbi.hwndList, GWL_STYLE, LBS_SORT);
			}
		}
		if (styles.istok("hscroll")) {
			//if (IsWindow(cbi.hwndCombo))
			//AddStyles(cbi.hwndCombo, GWL_STYLE, WS_HSCROLL);
			if (IsWindow(cbi.hwndList))
				AddStyles(cbi.hwndList, GWL_STYLE, WS_HSCROLL);
		}
	}
	//if (p_Dialog->getToolTip() != NULL) {
	//	if (styles.istok("tooltips")) {
	//		this->m_ToolTipHWND = p_Dialog->getToolTip();
	//		AddToolTipToolInfo(this->m_ToolTipHWND, this->m_Hwnd);
	//		AddToolTipToolInfo(this->m_ToolTipHWND, this->m_EditHwnd);
	//	}
	//}

	this->setControlFont( GetStockFont( DEFAULT_GUI_FONT ), FALSE );
	this->registreDefaultWindowProc( );
	SetProp( this->m_Hwnd, "dcx_cthis", (HANDLE) this );

	DragAcceptFiles(this->m_Hwnd, TRUE);

	// fix bug with disabled creation
	// todo: fix this properly
	if (Styles & WS_DISABLED) {
		EnableWindow(this->m_Hwnd, TRUE);
		EnableWindow(this->m_Hwnd, FALSE);
	}
}