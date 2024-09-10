void AuthKeyWindow::PasteFromClipboard()
{
	bool gotClipboardText = false;
	
	// Read key into clipboard
#ifdef TARGET_MSVC	
    bool opened = OpenClipboard(NULL);
    if( opened )
    {
        bool textAvailable = IsClipboardFormatAvailable(CF_TEXT);
        if( textAvailable )
        {
            HANDLE clipTextHandle = GetClipboardData(CF_TEXT);
            if( clipTextHandle )
            {
                char *text = (char *) GlobalLock(clipTextHandle); 
                if(clipTextHandle) 
                { 
                    strncpy( m_key, text, AUTHENTICATION_KEYLEN-1 );
					m_key[AUTHENTICATION_KEYLEN] = '\0';
					gotClipboardText = true;
					
                    GlobalUnlock(text); 
                }
            }
        }
        CloseClipboard();
    }
#elif TARGET_OS_MACOSX
	PasteboardRef clipboard = NULL;
	ItemCount numItems = 0;
	CFDataRef clipboardData = NULL;
	CFStringRef clipboardString;
	
	PasteboardCreate(kPasteboardClipboard, &clipboard);
	if ( clipboard )
	{
		PasteboardGetItemCount(clipboard, &numItems);
		
		// Use the first item, if it exists. Multiple items are only for drag-and-drop, AFAIK
		if ( numItems > 0 )
		{
			PasteboardItemID firstItem;
			PasteboardGetItemIdentifier( clipboard, 1, &firstItem );
			PasteboardCopyItemFlavorData( clipboard, firstItem,
										  CFSTR("public.utf16-plain-text"), &clipboardData);
			if ( clipboardData )
			{
				clipboardString = CFStringCreateWithBytes(NULL, CFDataGetBytePtr(clipboardData),
														  CFDataGetLength(clipboardData),
														  kCFStringEncodingUnicode, false);
				
				// Convert to Latin 1 encoding, and copy as much as will fit
				memset(m_key, 0, sizeof(m_key));
				CFStringGetBytes(clipboardString, CFRangeMake(0, CFStringGetLength(clipboardString)),
								 kCFStringEncodingWindowsLatin1, 0, false,
								 (UInt8 *)m_key, AUTHENTICATION_KEYLEN-1, NULL);
				gotClipboardText = true;
				
				CFRelease(clipboardString);
				CFRelease(clipboardData);
			}
		}
	}
	
	CFRelease( clipboard );
#endif // platform specific

	// Cross-platform code, once we've gotten the clipboard contents into m_key
	//
	if ( gotClipboardText )
	{
		strupr( m_key );
		Authentication_SetKey( m_key );
		Authentication_SaveKey( m_key, App::GetAuthKeyPath() );
	}
}