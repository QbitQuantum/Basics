HRESULT ClixRenderer::CreateDIR()
{
	HRESULT hr = S_OK;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2Factory);
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory)
			);
	}
	if (SUCCEEDED(hr))
	{
		hr = pDWriteFactory->CreateTextFormat(
			L"Microsoft Sans Serif Regular",                // Font family name.
			NULL,                       // Font collection (NULL sets it to use the system font collection).
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,
			L"en-us",
			&pTextFormat
			);
	}



	// Center align (horizontally) the text.
	if (SUCCEEDED(hr))
	{
		hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	}

	if (SUCCEEDED(hr))
	{
		hr = pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}


#ifdef CONSOLE
	if (SUCCEEDED(hr))
		std::wcout << "DeviceIndependendResources Succesfully created!" << std::endl;
	else
		std::wcout << "DeviceIndependedResources Error: " << std::hex << hr << std::endl;
#endif
	return hr;
}