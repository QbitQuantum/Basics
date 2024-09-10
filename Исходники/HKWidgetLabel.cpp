void HKWidgetLabel::SetProperty(const char *pProperty, const char *pValue)
{
	if(!MFString_CaseCmp(pProperty, "text"))
		SetText(pValue);
	else if(!MFString_CaseCmp(pProperty, "text_colour"))
		SetTextColour(HKWidget_GetColourFromString(pValue));
	else if(!MFString_CaseCmp(pProperty, "text_height"))
		SetTextHeight(MFString_AsciiToFloat(pValue));
	else if(!MFString_CaseCmp(pProperty, "text_shadowDepth"))
		SetShadowDepth(MFString_AsciiToFloat(pValue));
	else if(!MFString_CaseCmp(pProperty, "text_font"))
	{
		if(bOwnFont)
			MFFont_Release(pFont);
		pFont = MFFont_Create(pValue);
		bOwnFont = true;

		if(bAutoTextHeight)
			textHeight = MFFont_GetFontHeight(pFont);

		AdjustSize();
	}
	else if(!MFString_CaseCmp(pProperty, "text_align"))
		SetTextJustification((MFFontJustify)HKWidget_GetEnumValue(pValue, sJustifyKeys));
	else
		HKWidget::SetProperty(pProperty, pValue);
}