DWRITE_TEXT_METRICS TextFormatD2D::GetMetrics(
	const WCHAR* str, UINT strLen, bool gdiEmulation, float maxWidth)
{
	// GDI+ compatibility: If the last character is a newline, GDI+ measurements seem to ignore it.
	bool strippedLastNewLine = false;
	if (strLen > 2 && str[strLen - 1] == L'\n')
	{
		strippedLastNewLine = true;
		--strLen;

		if (str[strLen - 1] == L'\r')
		{
			--strLen;
		}
	}

	DWRITE_TEXT_METRICS metrics = {0};
	Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout;
	HRESULT hr = CanvasD2D::c_DWFactory->CreateTextLayout(
		str,
		strLen,
		m_TextFormat.Get(),
		maxWidth,
		10000,
		textLayout.GetAddressOf());
	if (SUCCEEDED(hr))
	{
		const float xOffset = m_TextFormat->GetFontSize() / 6.0f;
		if (gdiEmulation)
		{
			Microsoft::WRL::ComPtr<IDWriteTextLayout1> textLayout1;
			textLayout.As(&textLayout1);

			const float emOffset = xOffset / 24.0f;
			const DWRITE_TEXT_RANGE range = {0, strLen};
			textLayout1->SetCharacterSpacing(emOffset, emOffset, 0.0f, range);
		}

		textLayout->GetMetrics(&metrics);
		if (metrics.width > 0.0f)
		{
			if (gdiEmulation)
			{
				metrics.width += xOffset * 2;
				metrics.height += m_ExtraHeight;

				// GDI+ compatibility: If the string contains a newline (even if it is the
				// stripped last character), GDI+ adds the line gap to the overall height.
				if (strippedLastNewLine || wmemchr(str, L'\n', strLen) != nullptr)
				{
					metrics.height += m_LineGap;
				}
			}
			else
			{
				// GDI+ compatibility: With accurate metrics, the line gap needs to be subtracted
				// from the overall height if the string does not contain newlines.
				if (!strippedLastNewLine && wmemchr(str, L'\n', strLen) == nullptr)
				{
					metrics.height -= m_LineGap;
				}
			}
		}
		else
		{
			// GDI+ compatibility: Get rid of the height that DirectWrite assigns to zero-width
			// strings.
			metrics.height = 0.0f;
		}
	}

	return metrics;
}