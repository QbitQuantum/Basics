Paragraph::Paragraph(const LEUnicode chars[], int32_t charCount, const FontRuns *fontRuns, LEErrorCode &status)
  : fParagraphLayout(NULL), fParagraphCount(0), fParagraphMax(PARA_GROW), fParagraphGrow(PARA_GROW),
    fLineCount(0), fLinesMax(LINE_GROW), fLinesGrow(LINE_GROW), fLines(NULL), fChars(NULL),
    fLineHeight(-1), fAscent(-1), fWidth(-1), fHeight(-1), fParagraphLevel(UBIDI_DEFAULT_LTR)
{
    static const LEUnicode separators[] = {CH_LF, CH_CR, CH_LSEP, CH_PSEP, 0x0000};

	if (LE_FAILURE(status)) {
		return;
	}

    le_int32 ascent  = 0;
    le_int32 descent = 0;
    le_int32 leading = 0;

	LocaleRuns *locales = NULL;
    FontRuns fr(0);

    fLines = LE_NEW_ARRAY(const ParagraphLayout::Line *, fLinesMax);
    fParagraphLayout = LE_NEW_ARRAY(ParagraphLayout *, fParagraphMax);

    fChars = LE_NEW_ARRAY(LEUnicode, charCount + 1);
    LE_ARRAY_COPY(fChars, chars, charCount);
    fChars[charCount] = 0;

    LEUnicode *pStart = &fChars[0];

    while (*pStart != 0) {
        LEUnicode *pEnd = u_strpbrk(pStart, separators);
        le_int32 pAscent, pDescent, pLeading;
        ParagraphLayout *paragraphLayout = NULL;

        if (pEnd == NULL) {
            pEnd = &fChars[charCount];
        }

        if (pEnd != pStart) {
            subsetFontRuns(fontRuns, pStart - fChars, pEnd - fChars, &fr);

            paragraphLayout = new ParagraphLayout(pStart, pEnd - pStart, &fr, NULL, NULL, locales, fParagraphLevel, FALSE, status);

            if (LE_FAILURE(status)) {
                delete paragraphLayout;
                break; // return? something else?
            }

            if (fParagraphLevel == UBIDI_DEFAULT_LTR) {
                fParagraphLevel = paragraphLayout->getParagraphLevel();
            }

            pAscent  = paragraphLayout->getAscent();
            pDescent = paragraphLayout->getDescent();
            pLeading = paragraphLayout->getLeading();

            if (pAscent > ascent) {
                ascent = pAscent;
            }

            if (pDescent > descent) {
                descent = pDescent;
            }

            if (pLeading > leading) {
                leading = pLeading;
            }
        }

        if (fParagraphCount >= fParagraphMax) {
            fParagraphLayout = (ParagraphLayout **) LE_GROW_ARRAY(fParagraphLayout, fParagraphMax + fParagraphGrow);
            fParagraphMax += fParagraphGrow;
        }

        fParagraphLayout[fParagraphCount++] = paragraphLayout;

        if (*pEnd == 0) {
            break;
        }

        pStart = skipLineEnd(pEnd);
    }

    fLineHeight = ascent + descent + leading;
    fAscent     = ascent;
}