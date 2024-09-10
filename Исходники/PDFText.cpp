void
PDFWriter::DrawString(char *string, float escapementNoSpace,
	float escapementSpace)
{
	REPORT(kDebug, fPage, "DrawString string=\"%s\", escapementNoSpace=%f, "
		"escapementSpace=%f, at %f, %f", string, escapementNoSpace,
		escapementSpace, fState->penX, fState->penY);

	if (IsDrawing()) {
		// text color is always the high color and not the pattern!
		SetColor(fState->foregroundColor);
	}
	// convert string to UTF8
	BString utf8;
	if (fState->beFont.Encoding() == B_UNICODE_UTF8) {
		utf8 = string;
	} else {
		ToUtf8(fState->beFont.Encoding()-1, string, utf8);
	}

	// convert string in UTF8 to unicode UCS2
	BString unicode;
	ToUnicode(utf8.String(), unicode);
	// need font object to calculate width of utf8 code point
	BFont font = fState->beFont;
	font.SetEncoding(B_UNICODE_UTF8);
	// constants to calculate position of next character
	const double rotation = DEGREE2RAD(fState->beFont.Rotation());
	const bool rotate = rotation != 0.0;
	const double cos1 = rotate ? cos(rotation) : 1;
	const double sin1 = rotate ? -sin(rotation) : 0;

	BPoint start(fState->penX, fState->penY);

	BeginTransparency();
	// If !MakesPDF() all the effort below just for the bounding box!
	// draw each character
	const char *c = utf8.String();
	const unsigned char *u = (unsigned char*)unicode.String();
	for (int i = 0; i < unicode.Length(); i += 2) {
		int s = CodePointSize((char*)c);

		float w = font.StringWidth(c, s);

		if (MakesPDF() && IsClipping()) {
			ClipChar(&font, (char*)u, c, s, w);
		} else {
			DrawChar(u[0]*256+u[1], c, s);
		}

		// position of next character
		if (*(unsigned char*)c <= 0x20) { // should test if c is a white-space!
			w += escapementSpace;
		} else {
			w += escapementNoSpace;
		}

		fState->penX += w * cos1;
		fState->penY += w * sin1;

		// next character
		c += s; u += 2;
	}
	EndTransparency();

	// text line processing (for non rotated text only!)
	BPoint end(fState->penX, fState->penY);
	BRect bounds;
	font_height height;

	font.GetHeight(&height);

	bounds.left = start.x;
	bounds.right = end.x;
	bounds.top = start.y - height.ascent;
	bounds.bottom = end.y   + height.descent;

	TextSegment* segment = new TextSegment(utf8.String(), start, escapementSpace,
		escapementNoSpace, &bounds, &font, pdfSystem());

	fTextLine.Add(segment);
}