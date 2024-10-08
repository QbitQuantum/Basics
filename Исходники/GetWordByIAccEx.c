BOOL getWordByAccEx( POINT pt )
{
HRESULT hr;
IAccessible *pAcc, *pAccParent;
ITextProvider *pText;
ITextRangeProvider *pTextRange;
VARIANT var;
long idChild;
BSTR bstr = NULL;
int n;
UiaPoint upt;
POINT ppt = { 0, 0 };

	if( getPhysicalCursorPosFunc != NULL ) {
		getPhysicalCursorPosFunc( &ppt );
	} else {
		ppt = pt;
	}

	upt.x = ppt.x;
	upt.y = ppt.y;

	pAcc = NULL;
	hr = AccessibleObjectFromPoint( ppt, &pAcc, &var );
	idChild = var.lVal;

	if( hr != S_OK || pAcc == NULL) {
		VariantClear( &var );
		return FALSE;
	}

	pText = NULL;
	while( pAcc != NULL) {
		hr = GetPatternFromIAccessible( pAcc, 0, UIA_TextPatternId, &IID_ITextProvider, (void **)&pText );
		if( hr == S_OK && pText != NULL )
			break;
		pAccParent = NULL;
		hr = GetParentAccessibleObject( pAcc, &pAccParent );
		pAcc->lpVtbl->Release( pAcc );
		pAcc = pAccParent;
	}
	if( pAcc == NULL ) 
		return FALSE;

	pAcc->lpVtbl->Release( pAcc );

	pTextRange = NULL;
	hr = pText->lpVtbl->RangeFromPoint( pText, upt, &pTextRange );
	if( hr != S_OK || pTextRange == NULL ) {
		pText->lpVtbl->Release( pText );
		return FALSE;
	}

	hr = pTextRange->lpVtbl->ExpandToEnclosingUnit( pTextRange, TextUnit_Word );
	if( hr == S_OK) {
		bstr = NULL;
		hr = pTextRange->lpVtbl->GetText( pTextRange, 255, &bstr );
		if (hr == S_OK) {
			n = SysStringLen( bstr );
			if( n != 0 ) {
				n = WideCharToMultiByte( CP_UTF8, 0, (LPCWSTR)bstr, n, GlobalData->CurMod.MatchedWord, sizeof( GlobalData->CurMod.MatchedWord ) - 1, NULL, NULL );
				GlobalData->CurMod.WordLen = n;
				GlobalData->CurMod.MatchedWord[n] = 0;
			}
			SysFreeString( bstr );
		}
	}
	pTextRange->lpVtbl->Release( pTextRange );
	pText->lpVtbl->Release( pText );

	return TRUE;
}