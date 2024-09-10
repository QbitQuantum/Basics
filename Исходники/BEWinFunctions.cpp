WStringAutoPtr ClipboardFormats ( void )
{
	wstring format_list = L"";

	if ( OpenClipboard ( NULL ) ) {
		
		UINT formats = CountClipboardFormats();
		UINT next_format = 0;
		
		for ( UINT i = 0 ; i < formats ; i++ ) {
			
			next_format = EnumClipboardFormats ( next_format );

			const int max_count = 4096;
			wchar_t format_name[max_count];
			int name_length = GetClipboardFormatName ( next_format, format_name, max_count );
			
			if ( name_length > 0 ) {
				format_list += format_name;
				format_list += L"\r";
			}
			
		}

		CloseClipboard();

	}

	return WStringAutoPtr ( new wstring ( format_list ) );
	
} // ClipboardFormats