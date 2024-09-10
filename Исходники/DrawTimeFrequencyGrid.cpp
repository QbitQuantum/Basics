BOOL DrawTimeFrequencyGrid::Initialize( float aFontSize )
{
	static const WCHAR msc_fontName[] = L"Verdana";
	fontSize = aFontSize;

	// Added code for factory here--odd place to put it.
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
	if ( FAILED(hr)) return FALSE;
	
	// Create a DirectWrite factory.
	hr = DWriteCreateFactory( DWRITE_FACTORY_TYPE_SHARED, __uuidof(pDWriteFactory),
            reinterpret_cast<IUnknown **>(&pDWriteFactory) );
	 if ( FAILED(hr)) return FALSE;

	 // Create a DirectWrite text format object.
     hr = pDWriteFactory->CreateTextFormat( msc_fontName, NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            fontSize,
            L"", //locale
            &pTextFormat );
	 if ( FAILED(hr)) return FALSE;

	// Center the text horizontally and vertically.
	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	return TRUE;
}