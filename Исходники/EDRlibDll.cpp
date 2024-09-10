EXPORT BOOL CALLBACK EdrCenterTextW(HDC hdc, PRECT prc, PCWSTR pString)

{

	int  iLength;

	SIZE size;


	iLength = lstrlenW(pString);

	GetTextExtentPoint32W(hdc, pString, iLength, &size);

	return TextOutW(hdc, (prc->right - prc->left - size.cx) / 2,

		(prc->bottom - prc->top - size.cy) / 2,

		pString, iLength);

}