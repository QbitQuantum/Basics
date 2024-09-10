void ZLTextView::PositionIndicator::draw() {
	ZLPaintContext &context = this->context();

	ZLTextWordCursor endCursor = myTextView.textArea().endCursor();
	bool isEndOfText = false;
	if (endCursor.isEndOfParagraph()) {
		isEndOfText = !endCursor.nextParagraph();
	}

	myExtraWidth = 0;
	if (myInfo.isTimeShown()) {
		drawExtraText(timeString());
	}
	if (myInfo.isTextPositionShown()) {
		drawExtraText(textPositionString());
	}

	const long bottom = this->bottom();
	const long top = this->top();
	const long left = this->left();
	const long right = this->right();

	if (left >= right) {
		return;
	}

	size_t fillWidth = right - left - 1;

	if (!isEndOfText) {
		fillWidth =
			muldiv(fillWidth, sizeOfTextBeforeCursor(myTextView.textArea().endCursor()), sizeOfTextBeforeParagraph(endTextIndex()));
	}

	context.setColor(myTextView.color());
	context.setFillColor(myInfo.color());
	context.fillRectangle(left + 1, top + 1, left + fillWidth + 1, bottom - 1);
	context.drawLine(left, top, right, top);
	context.drawLine(left, bottom, right, bottom);
	context.drawLine(left, bottom, left, top);
	context.drawLine(right, bottom, right, top);
}