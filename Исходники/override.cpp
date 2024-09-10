// 有効なDCかどうかをチェックする
BOOL IsValidDC(const HDC hdc){
	if (GetDeviceCaps(hdc, TECHNOLOGY) != DT_RASDISPLAY) return FALSE;
	// ここでフォントチェックも行う
	WCHAR szFaceName[LF_FACESIZE] = L"";
	GetTextFaceW(hdc, LF_FACESIZE, szFaceName);
	if (IsFontExcluded(szFaceName)) return FALSE;
	return TRUE;
}