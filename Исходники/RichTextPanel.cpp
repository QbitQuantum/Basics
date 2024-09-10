// FIXME: leaks
result RichTextPanel::Construct(const Dimension& dim, const String & text) {
	result r = E_SUCCESS;
	TextElement* textElement;
	int width, height;
	Color color = Color::GetColor(COLOR_ID_WHITE);
	Font font;

	Dimension textDim;
	int textActualLen;

	enrichedText = new EnrichedText();
	r = enrichedText->Construct(dim);
	TryCatch(r == E_SUCCESS, , "Failed Construct EnrichedText");

	r = font.Construct(FONT_STYLE_PLAIN, TEXT_FONT_SIZE);
	TryCatch(r == E_SUCCESS, , "Failed Construct Font");

	textElement = new TextElement();
	r = textElement->Construct(text);
	TryCatch(r == E_SUCCESS, , "Failed TextElement");
	r = textElement->SetTextColor(color);
	TryCatch(r == E_SUCCESS, , "Failed SetTextColor");
	r = textElement->SetFont(font);
	TryCatch(r == E_SUCCESS, , "Failed SetFont");

	r = enrichedText->Add(*textElement);
	TryCatch(r == E_SUCCESS, , "Failed Add textElement");


	height = enrichedText->GetTotalLineHeight();

	r = enrichedText->GetTextExtent(0, text.GetLength(), textDim, textActualLen);
	TryCatch(r == E_SUCCESS, , "Failed GetTextExtent");
	width = dim.width < textDim.width ? dim.width : textDim.width;

	r = Panel::Construct(Rectangle(0, 0, width, height));
	TryCatch(r == E_SUCCESS, , "Failed Construct RichTextPanel parent");

	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed GetSize");
	AppLog("Size received: %d x %d", width, height);

	r = SetSize(width, height);
	TryCatch(r == E_SUCCESS, , "Failed SetSize");

//	SetBackgroundColor(color);
	TryCatch(GetLastResult() == E_SUCCESS, r = GetLastResult(), "Failed SetBackgroundColor");

	return r;

	CATCH:
	    AppLogException("$${Function:Construct} is failed.", GetErrorMessage(r));

	    if (textElement)
	    	delete textElement;

	    return r;
}