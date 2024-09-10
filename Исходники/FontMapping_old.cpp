	void map_font()
	{
        HDC hDC = GetDC( NULL );
		//errno_t   err ;

		//err = _wfopen_s(&out, L"font_dump.txt", L"w, ccs=UNICODE" ) ;

        //LOGFONT lf = { 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0,
         //0, NULL };
         //EnumFontFamiliesEx( hDC, &lf, (FONTENUMPROC)EnumFontFamiliesExProc, 0, 0 );
	    //fclose( out ); 
		
		HFONT	hfont;
        TEXTMETRIC          tm;
        LOGFONTA             lf;
		TCHAR   szFaceName[LF_FACESIZE];
		CHOOSEFONTA   choose_font;


		LPCTSTR lpszFilename = "c:\\Code39Barcode.ttf";
		int err;
		bool success;

        // load font 
		err = AddFontResourceA(lpszFilename);
		SendMessageA(HWND_BROADCAST,WM_FONTCHANGE,0,0);

		choose_font.lStructSize = sizeof(CHOOSEFONT);
		choose_font.hwndOwner = NULL;
		choose_font.lpLogFont = &lf;
		choose_font.Flags = CF_SCREENFONTS;
		success = ChooseFontA( &choose_font );

		/*
		for( indx=0; indx<num_fonts; indx++)
		{

			hfont = CreateFontA(0,0,0,0,0,0,0,0,DEFAULT_CHARSET, 0,0,0,0, font_table[indx]);
			SelectObject(hDC, hfont);



			GetObjectA( GetCurrentObject( hdc, OBJ_FONT ), 
						sizeof(lf), 
						(LPVOID) &lf );

		// Get the info for the currently realized font.
		//GetTextMetrics( hdc, &tm );
		GetTextFace( hdc, sizeof(szFaceName), szFaceName );
		cout << "Font: " << font_table[indx] << "  Mapping: " << szFaceName << endl;
*/

/*
		// get logical font information

		hfont = CreateFontA(0,0,0,0,0,0,0,0,DEFAULT_CHARSET, 0,0,0,0, "Code39Barcode");
		SelectObject(hDC, hfont);
		GetObjectA( GetCurrentObject( hDC, OBJ_FONT ), 
					sizeof(lf), 
					(LPVOID) &lf );
		GetTextFace( hDC, sizeof(szFaceName), szFaceName );
*/




		// unload font

		err = RemoveFontResourceA(lpszFilename);
		SendMessageA(HWND_BROADCAST,WM_FONTCHANGE,0,0);

		hfont = CreateFontIndirectA(&lf);
		SelectObject(hDC, hfont);
		GetObjectA( GetCurrentObject( hDC, OBJ_FONT ), 
					sizeof(lf), 
					(LPVOID) &lf );
		GetTextFace( hDC, sizeof(szFaceName), szFaceName );
		GetTextMetrics( hDC, &tm );
		//cout << "Font: " << "Arial" << "  Mapping: " << szFaceName << endl;
		
		ReleaseDC( NULL, hDC );

        return;
	}