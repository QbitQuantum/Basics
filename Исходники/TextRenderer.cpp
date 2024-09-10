void CTextRenderer::UpdateTextCache_BiDi(array<CHarfbuzzGlyph>* pGlyphChain, const char* pText)
{
	//Use ICU for bidirectional text
	//note: bidirectional texts appear for example when a latin username is displayed in a arabic text
	UErrorCode ICUError = U_ZERO_ERROR;
	UnicodeString UTF16Text = icu::UnicodeString::fromUTF8(pText);
	UBiDi* pICUBiDi = ubidi_openSized(UTF16Text.length(), 0, &ICUError);
	
	//Perform the BiDi algorithm
	//TODO: change UBIDI_DEFAULT_LTR by some variable dependend of the user config
	ubidi_setPara(pICUBiDi, UTF16Text.getBuffer(), UTF16Text.length(), (Localization()->GetWritingDirection() == CLocalization::DIRECTION_RTL ? UBIDI_DEFAULT_RTL : UBIDI_DEFAULT_LTR), 0, &ICUError);
	
	if(U_SUCCESS(ICUError))
	{
		UBiDiLevel ICULevel = 1&ubidi_getParaLevel(pICUBiDi);
		UBiDiDirection Direction = ubidi_getDirection(pICUBiDi);

		if(Direction != UBIDI_MIXED)
		{
			UpdateTextCache_Font(pGlyphChain, UTF16Text.getBuffer(), 0, UTF16Text.length(), (Direction == UBIDI_RTL));
		}
		else
		{
			int CharStart = 0;
			UBiDiLevel level;
			int NumberOfParts = ubidi_countRuns(pICUBiDi, &ICUError);
			if(U_SUCCESS(ICUError))
			{
				for(int i=0; i<NumberOfParts; i++)
				{
					int Start;
					int SubLength;
					Direction = ubidi_getVisualRun(pICUBiDi, i, &Start, &SubLength);

					UpdateTextCache_Font(pGlyphChain, UTF16Text.getBuffer(), Start, SubLength, (Direction == UBIDI_RTL));
				}
			}
			else
			{
				dbg_msg("TextRenderer", "BiDi algorithm failed (ubidi_countRuns): %s", u_errorName(ICUError));
				return;
			}
		}
    }
    else
    {
		dbg_msg("TextRenderer", "BiDi algorithm failed: %s", u_errorName(ICUError));
		return;
	}
}