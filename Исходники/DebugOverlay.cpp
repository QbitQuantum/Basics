// An initialization routine to create and implement the DirectWrite library's interfaces
bool DebugOverlay::Init(Engine2D * eng) {
	// Short term rectangle for ease of use in Init function
	RECT rect = eng->wRect;
	
	// Default a simple empty string for the global display text - may be unnecessary
	displayText = new wchar_t[1] {L""};
	
	// Sets the active window's bounds for referencing later in the DrawText
	// Can manipulate to move text from upper-right corner by default
	lRect = D2D1::RectF(
		static_cast<FLOAT>(rect.left), // dpiScaleX,
		static_cast<FLOAT>(rect.top), // dpiScaleY,
		static_cast<FLOAT>(rect.right - rect.left), // dpiScaleX,
		static_cast<FLOAT>(rect.bottom - rect.top) // dpiScaleY
	);

	// Create the DirectWrite factory and check that it executed okay
	// Function call is virtually the same as the sample given on the
	// MSDN site for how to use the DirectWrite library
	HRESULT hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED, // see MSDN for information about this
		__uuidof(IDWriteFactory), // Also this
		reinterpret_cast<IUnknown**>(&writeFact) // And this
	);
	if (!SUCCEEDED(hr)) { return false; };

	// Create the Text Format for issuing later to the DrawText() function
	// Function call is virtually the same as the sample given on the
	// MSDN site for how to use the DirectWrite library
	hr = writeFact->CreateTextFormat(
		L"Consolas", // Font type
		NULL, // ID Write Font Collection - set to null for default system font collection
		DWRITE_FONT_WEIGHT_REGULAR, // Font weight
		DWRITE_FONT_STYLE_NORMAL, // Font style
		DWRITE_FONT_STRETCH_NORMAL, // Font stretch (?)
		14.0f, // Font size
		L"en-us", // Locale name
		&textFormat // Reference to the text format handle for storing the information
	);
	if (!SUCCEEDED(hr)) { return false; };

	// Set the text alignment of the text format object and check to make sure its okay
	hr = textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
	if (!SUCCEEDED(hr)) { return false; };

	// Set the paragraph alignment for the text format object and check to make sure its okay
	hr = textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	if (!SUCCEEDED(hr)) { return false; };

	// Use the pre-existing D2D render target to create a solid brush for this class
	hr = eng->renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &debugBrush);
	if (!SUCCEEDED(hr)) { return false; };

	return true;
}