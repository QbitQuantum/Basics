	void RenderContext::CalcStringRectWithFlags(const std::wstring& text, const Font& font, const Rect& rect, int flags, Rect& out, size_t* len, int* lines)
	{
		HDC hdc = GetDC(NULL);
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::Font        gdi_font(hdc, font.ToHFONT());
		Gdiplus::StringFormat format;
		Gdiplus::RectF       rectF(rect.x(), rect.y(), rect.width(), rect.height());

		Gdiplus::RectF outF;

		GetStringFormat(format, flags);
		graphics.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
		graphics.MeasureString(text.c_str(), text.size(), &gdi_font, rectF, &format, &outF, (int*)len, lines);

		out.SetRect(outF.X, outF.Y, outF.Width, outF.Height);
		::ReleaseDC(NULL, hdc);
	}