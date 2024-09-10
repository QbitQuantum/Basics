//---------------------------------------------------------------------------
bool TVPClipboardGetText(ttstr & text)
{
	if(!OpenClipboard(Application->Handle)) return false;

	bool result = false;
	try
	{
		// select CF_UNICODETEXT or CF_TEXT
		UINT formats[2] = { CF_UNICODETEXT, CF_TEXT};
		int format = GetPriorityClipboardFormat(formats, 2);

		if(format == CF_UNICODETEXT)
		{
			// try to read unicode text
			HGLOBAL hglb = (HGLOBAL)GetClipboardData(CF_UNICODETEXT);
			if(hglb != NULL)
			{
				const tjs_char *p = (const tjs_char *)GlobalLock(hglb);
				if(p)
				{
					try
					{
						text = ttstr(p);
						result = true;
					}
					catch(...)
					{
						GlobalUnlock(hglb);
						throw;
					}
					GlobalUnlock(hglb);
				}
			}
		}
		else if(format == CF_TEXT)
		{
			// try to read ansi text
			HGLOBAL hglb = (HGLOBAL)GetClipboardData(CF_TEXT);
			if(hglb != NULL)
			{
				const char *p = (const char *)GlobalLock(hglb);
				if(p)
				{
					try
					{
						text = ttstr(p);
						result = true;
					}
					catch(...)
					{
						GlobalUnlock(hglb);
						throw;
					}
					GlobalUnlock(hglb);
				}
			}
		}
	}
	catch(...)
	{
		CloseClipboard();
		throw;
	}
	CloseClipboard();

	return result;
}