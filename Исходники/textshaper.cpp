QList<TextShaper::TextRun> TextShaper::itemizeBiDi()
{
	QList<TextRun> textRuns;
	UBiDi *obj = ubidi_open();
	UErrorCode err = U_ZERO_ERROR;

	UBiDiLevel parLevel = UBIDI_LTR;
	ParagraphStyle style = m_story.paragraphStyle(m_firstChar);
	if (style.direction() == ParagraphStyle::RTL)
		parLevel = UBIDI_RTL;

	ubidi_setPara(obj, (const UChar*) m_text.utf16(), m_text.length(), parLevel, NULL, &err);
	if (U_SUCCESS(err))
	{
		int32_t count = ubidi_countRuns(obj, &err);
		if (U_SUCCESS(err))
		{
			textRuns.reserve(count);
			for (int32_t i = 0; i < count; i++)
			{
				int32_t start, length;
				UBiDiDirection dir = ubidi_getVisualRun(obj, i, &start, &length);
				textRuns.append(TextRun(start, length, dir));
			}
		}
	}

	ubidi_close(obj);
	return textRuns;
}