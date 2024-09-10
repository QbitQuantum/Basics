BOOL
init_print_gdi(HDC hdc)
{
    // create the pipe for capturing printer output
    /* Set the bInheritHandle flag so pipe handles are inherited. */
    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;
    HANDLE hPipeTemp;

    if (!CreatePipe(&hPipeTemp, &print_gdi_write_handle, &saAttr, 0)) {
	gs_addmess("failed to open printer pipe\n");
	return FALSE;
    }
    /* make the read handle non-inherited */
    if (!DuplicateHandle(GetCurrentProcess(), hPipeTemp,
	    GetCurrentProcess(), &print_gdi_read_handle, 0,
	    FALSE,       /* not inherited */
	    DUPLICATE_SAME_ACCESS)) {
	gs_addmess("failed to duplicate pipe handle\n");
	return FALSE;
    }
    CloseHandle(hPipeTemp);

    // open printer, get size and resolution
    DOCINFO di;
    TCHAR wpsname[MAXSTR];
    convert_multibyte(wpsname, psfile_name(&psfile), 
	sizeof(wpsname)/sizeof(TCHAR)-1);
    memset(&di, 0, sizeof(DOCINFO));
    di.cbSize = sizeof(DOCINFO);
    di.lpszDocName = wpsname;
    di.lpszOutput = NULL;
    if (StartDoc(hdc, &di) == SP_ERROR) {
	DWORD err = GetLastError();
	LPSTR lpMessageBuffer;
	char buf[MAXSTR];
	sprintf(buf, "StartDoc failed, error %d\n", err);
	gs_addmess(buf);
	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
	    FORMAT_MESSAGE_FROM_SYSTEM,
	    NULL, err,
	    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), /* user default language */
	    (LPSTR)&lpMessageBuffer, 0, NULL);
	if (lpMessageBuffer) {
	    gs_addmess(lpMessageBuffer);
	    gs_addmess("\r\n");
	    LocalFree(LocalHandle(lpMessageBuffer));
	}
	return FALSE;
    }

    // Need to pass these back to gvcprn.cpp.
    // Use global variables for now.
    print_gdi_width = GetDeviceCaps(hdc, PHYSICALWIDTH);
    print_gdi_height = GetDeviceCaps(hdc, PHYSICALHEIGHT);
    print_gdi_xdpi = GetDeviceCaps(hdc, LOGPIXELSX);
    print_gdi_ydpi = GetDeviceCaps(hdc, LOGPIXELSY);
    if (debug & DEBUG_GDI) {
	char buf[MAXSTR];
	sprintf(buf, "GDI width=%d height=%d xdpi=%d ydpy=%d\n",
	    print_gdi_width, print_gdi_height, print_gdi_xdpi, print_gdi_ydpi);
	gs_addmess(buf);
    }

    if ( (print_gdi_width == 0) || (print_gdi_height == 0) ) {
	gs_addmess("Printer width or height is zero\n");
	return FALSE;
    }
 
    return TRUE;
}