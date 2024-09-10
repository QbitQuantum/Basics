// *****************************************************************
//		SetDrawingKey()
// *****************************************************************
void CMapView::SetDrawingKey(long DrawHandle, LPCTSTR lpszNewValue)
{
	if( IsValidDrawList (DrawHandle) )
	{	
		::SysFreeString(_allDrawLists[DrawHandle]->key);
		_allDrawLists[DrawHandle]->key = A2BSTR(lpszNewValue);
	}
	else
		ErrorMessage(tkINVALID_DRAW_HANDLE);
}