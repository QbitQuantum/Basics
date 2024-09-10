void
NotificationView::SetText(float newMaxWidth)
{
	if (newMaxWidth < 0 && Parent())
		newMaxWidth = Parent()->Bounds().IntegerWidth();
	if (newMaxWidth <= 0)
		newMaxWidth = kDefaultWidth;

	// Delete old lines
	LineInfoList::iterator lIt;
	for (lIt = fLines.begin(); lIt != fLines.end(); lIt++)
		delete (*lIt);
	fLines.clear();

	float iconRight = kIconStripeWidth;
	if (fBitmap != NULL)
		iconRight += fParent->IconSize();
	else
		iconRight += 32;

	font_height fh;
	be_bold_font->GetHeight(&fh);
	float fontHeight = ceilf(fh.leading) + ceilf(fh.descent)
		+ ceilf(fh.ascent);
	float y = 2 * fontHeight;

	// Title
	LineInfo* titleLine = new LineInfo;
	titleLine->text = fNotification->Title();
	titleLine->font = *be_bold_font;

	titleLine->location = BPoint(iconRight + kEdgePadding, y);

	fLines.push_front(titleLine);
	y += fontHeight;

	// Rest of text is rendered with be_plain_font.
	be_plain_font->GetHeight(&fh);
	fontHeight = ceilf(fh.leading) + ceilf(fh.descent)
		+ ceilf(fh.ascent);

	// Split text into chunks between certain characters and compose the lines.
	const char kSeparatorCharacters[] = " \n-\\";
	BString textBuffer = fNotification->Content();
	textBuffer.ReplaceAll("\t", "    ");
	const char* chunkStart = textBuffer.String();
	float maxWidth = newMaxWidth - kEdgePadding - iconRight;
	LineInfo* line = NULL;
	ssize_t length = textBuffer.Length();
	while (chunkStart - textBuffer.String() < length) {
		size_t chunkLength = strcspn(chunkStart, kSeparatorCharacters) + 1;

		// Start a new line if we didn't start one before
		BString tempText;
		if (line != NULL)
			tempText.SetTo(line->text);
		tempText.Append(chunkStart, chunkLength);

		if (line == NULL || chunkStart[0] == '\n'
			|| StringWidth(tempText) > maxWidth) {
			line = new LineInfo;
			line->font = *be_plain_font;
			line->location = BPoint(iconRight + kEdgePadding, y);

			fLines.push_front(line);
			y += fontHeight;

			// Skip the eventual new-line character at the beginning of this chunk
			if (chunkStart[0] == '\n') {
				chunkStart++;
				chunkLength--;
			}

			// Skip more new-line characters and move the line further down
			while (chunkStart[0] == '\n') {
				chunkStart++;
				chunkLength--;
				line->location.y += fontHeight;
				y += fontHeight;
			}

			// Strip space at beginning of a new line
			while (chunkStart[0] == ' ') {
				chunkLength--;
				chunkStart++;
			}
		}

		if (chunkStart[0] == '\0')
			break;

		// Append the chunk to the current line, which was either a new
		// line or the one from the previous iteration
		line->text.Append(chunkStart, chunkLength);

		chunkStart += chunkLength;
	}

	fHeight = y + (kEdgePadding * 2);

	// Make sure icon fits
	if (fBitmap != NULL) {
		float minHeight = fBitmap->Bounds().Height() + 2 * kEdgePadding;

		if (fHeight < minHeight)
			fHeight = minHeight;
	}

	// Make sure the progress bar is below the text, and the window is big
	// enough.
	static_cast<BGroupLayout*>(GetLayout())->SetInsets(kIconStripeWidth + 8,
		fHeight, 8, 8);

	_CalculateSize();
}