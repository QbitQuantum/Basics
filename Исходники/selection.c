LRESULT CALLBACK
HiddenWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT retval;
    HANDLE hText;
    char *pText;
    gchar *str;


    switch (msg) {
    case WM_DESTROY:
	    ChangeClipboardChain(hwnd , next_hwnd);
	    PostQuitMessage(0);
	    break;
    case WM_DRAWCLIPBOARD:
	    OpenClipboard(hwnd);
	    hText = GetClipboardData(CF_TEXT);

	    if(hText != NULL) {
		    pText = GlobalLock(hText);
		    GlobalUnlock(hText);
	    }
	    CloseClipboard();

	    //remove_space(pText);
	    str = iconv_convert(fs_codeset, "utf-8", pText);
	    search_selected(str);
	    g_free(str);

	    if(next_hwnd != NULL)
		    SendMessage(next_hwnd, msg, wParam, lParam);
	    break;
    case WM_CHANGECBCHAIN:
	    if((HWND)wParam == next_hwnd)
		    next_hwnd = (HWND)lParam;
	    break;
    default:
	    break;
    }

    retval = OrgWndProc(hwnd, msg, wParam, lParam);
    return retval;
}