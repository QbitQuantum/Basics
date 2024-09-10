void controlUC::setAttribute(PCWSTR pstrName, PCWSTR pstrValue)
{
	if( _tcscmp(pstrName, L"pos") == 0 ) {
		RECT rcPos = { 0 };
		PWSTR pstr = NULL;
		rcPos.left = _tcstol(pstrValue, &pstr, 10);  assert(pstr);    
		rcPos.top = _tcstol(pstr + 1, &pstr, 10);    assert(pstr);    
		rcPos.right = _tcstol(pstr + 1, &pstr, 10);  assert(pstr);    
		rcPos.bottom = _tcstol(pstr + 1, &pstr, 10); assert(pstr);    
		SIZE szXY = {rcPos.left >= 0 ? rcPos.left : rcPos.right, rcPos.top >= 0 ? rcPos.top : rcPos.bottom};
		setFixedXY(szXY);
		setFixedWidth(rcPos.right - rcPos.left);
		setFixedHeight(rcPos.bottom - rcPos.top);
	}
	else if( _tcscmp(pstrName, L"relativepos") == 0 ) {
		SIZE szMove,szZoom;
		PWSTR pstr = NULL;
		szMove.cx = _tcstol(pstrValue, &pstr, 10);  assert(pstr);    
		szMove.cy = _tcstol(pstr + 1, &pstr, 10);    assert(pstr);    
		szZoom.cx = _tcstol(pstr + 1, &pstr, 10);  assert(pstr);    
		szZoom.cy = _tcstol(pstr + 1, &pstr, 10); assert(pstr); 
		setRelativePos(szMove,szZoom);
	}
	else if( _tcscmp(pstrName, L"padding") == 0 ) {
		RECT rcPadding = { 0 };
		PWSTR pstr = NULL;
		rcPadding.left = _tcstol(pstrValue, &pstr, 10);  assert(pstr);    
		rcPadding.top = _tcstol(pstr + 1, &pstr, 10);    assert(pstr);    
		rcPadding.right = _tcstol(pstr + 1, &pstr, 10);  assert(pstr);    
		rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10); assert(pstr);    
		setPadding(rcPadding);
	}
	else if( _tcscmp(pstrName, L"bkcolor") == 0 || _tcscmp(pstrName, L"bkcolor1") == 0 ) {
		while( *pstrValue > L'\0' && *pstrValue <= L' ')  pstrValue = ::CharNext(pstrValue);
		if( *pstrValue == L'#') pstrValue = ::CharNext(pstrValue);
		PWSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		setBkColor(clrColor);
	}
	else if( _tcscmp(pstrName, L"bordercolor") == 0 ) {
		if( *pstrValue == L'#') pstrValue = ::CharNext(pstrValue);
		PWSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		setBorderColor(clrColor);
	}
	else if( _tcscmp(pstrName, L"focusbordercolor") == 0 ) {
		if( *pstrValue == L'#') pstrValue = ::CharNext(pstrValue);
		PWSTR pstr = NULL;
		DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
		setFocusBorderColor(clrColor);
	}
	else if( _tcscmp(pstrName, L"bordersize") == 0 ) setBorderSize(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, L"borderround") == 0 ) {
		SIZE cxyRound = { 0 };
		PWSTR pstr = NULL;
		cxyRound.cx = _tcstol(pstrValue, &pstr, 10);  assert(pstr);    
		cxyRound.cy = _tcstol(pstr + 1, &pstr, 10);    assert(pstr);     
		setBorderRound(cxyRound);
	}
	else if( _tcscmp(pstrName, L"width") == 0 ) setFixedWidth(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, L"height") == 0 ) setFixedHeight(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, L"minwidth") == 0 ) setMinWidth(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, L"minheight") == 0 ) setMinHeight(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, L"maxwidth") == 0 ) setMaxWidth(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, L"maxheight") == 0 ) setMaxHeight(_ttoi(pstrValue));
	else if( _tcscmp(pstrName, L"name") == 0 ) setName(pstrValue);
	else if( _tcscmp(pstrName, L"text") == 0 ) setText(pstrValue);
	else if( _tcscmp(pstrName, L"tooltip") == 0 ) setToolTip(pstrValue);
	else if( _tcscmp(pstrName, L"userdata") == 0 ) setUserData(pstrValue);
	else if( _tcscmp(pstrName, L"enabled") == 0 ) setEnabled(_tcscmp(pstrValue, L"true") == 0);
	else if( _tcscmp(pstrName, L"mouse") == 0 ) setMouseEnabled(_tcscmp(pstrValue, L"true") == 0);
	else if( _tcscmp(pstrName, L"visible") == 0 ) setVisible(_tcscmp(pstrValue, L"true") == 0);
	else if( _tcscmp(pstrName, L"float") == 0 ) setFloat(_tcscmp(pstrValue, L"true") == 0);
	else if( _tcscmp(pstrName, L"shortcut") == 0 ) setShortcut(pstrValue[0]);
	else if( _tcscmp(pstrName, L"menu") == 0 ) setContextMenuUsed(_tcscmp(pstrValue, L"true") == 0);
}