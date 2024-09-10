//-----------------------------------------------------------------------------
// GetW7PopupIAccessible()
//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
IAccessible *GetW7PopupIAccessible(HWND w)
{
	TRACE((TRACE_ENTER,_F_, "w=0x%08lx",w));
	HRESULT hr;
	IAccessible *pAccessible=NULL;

	gwW7PopupChild=NULL;
	EnumChildWindows(w,W7PopupEnumChildProc,0);
	if (gwW7PopupChild==NULL) goto end;
	TRACE((TRACE_DEBUG,_F_,"w=0x%08lx gwW7PopupChild=0x%08lx",w,gwW7PopupChild));

	// récupère pointeur IAccessible
	hr=AccessibleObjectFromWindow(gwW7PopupChild,(DWORD)OBJID_CLIENT,IID_IAccessible,(void**)&pAccessible);
	if (FAILED(hr))
	{
		TRACE((TRACE_ERROR,_F_,"AccessibleObjectFromWindow()=0x%08lx",hr));
		goto end;
	}
end:
	TRACE((TRACE_LEAVE,_F_, "pAccessible=0x%08lx",pAccessible));
	return pAccessible;
}