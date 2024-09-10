M4Err GetDisplayMode(DDContext *dd)
{
	if (dd->switch_res) {
		HRESULT hr;
		Bool temp_dd = 0;;
		if (!dd->pDD) {
			LPDIRECTDRAW ddraw;
			DirectDrawCreate(NULL, &ddraw, NULL);
#ifdef USE_DX_3
			IDirectDraw_QueryInterface(ddraw, &IID_IDirectDraw, (LPVOID *)&dd->pDD);
#else
			IDirectDraw_QueryInterface(ddraw, &IID_IDirectDraw7, (LPVOID *)&dd->pDD);
#endif		
			temp_dd = 1;
		}
		//we start with a hugde res and downscale
		dd->fs_width = dd->fs_height = 50000;

#ifdef USE_DX_3
		hr = IDirectDraw_EnumDisplayModes(dd->pDD, 0L, NULL, dd,  (LPDDENUMMODESCALLBACK) EnumDisplayModes);
#else
		hr = IDirectDraw7_EnumDisplayModes(dd->pDD, 0L, NULL, dd,  (LPDDENUMMODESCALLBACK2) EnumDisplayModes);
#endif
		if (temp_dd) SAFE_DD_RELEASE(dd->pDD);
		if (FAILED(hr)) return M4IOErr;
	} else {
		dd->fs_width = GetSystemMetrics(SM_CXSCREEN);
		dd->fs_height = GetSystemMetrics(SM_CYSCREEN);
	}
	return M4OK;
}