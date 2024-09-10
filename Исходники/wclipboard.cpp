Status sys_clipboard_set(const wchar_t* text)
{
	if(!OpenClipboard(hWndNewOwner))
		WARN_RETURN(ERR::FAIL);

	WARN_IF_FALSE(EmptyClipboard());

	// NB: to enable copy/pasting something other than text, add
	// message handlers for WM_RENDERFORMAT and WM_RENDERALLFORMATS.
	HGLOBAL hMem;
	Status ret = SetClipboardText(text, hMem);

	WARN_IF_FALSE(CloseClipboard());	// must happen before GlobalFree

	ENSURE(GlobalFree(hMem) == 0);	// (0 indicates success)

	return ret;
}