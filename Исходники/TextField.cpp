void cTextField::replaceSelection(const QCString &replacement) {
	// Delete the selection, reposition caret_, then reinsert
	if (selection_ != 0) {
		if (selection_ < 0) {
			setCaret(caret_ + selection_); // Place the caret at the start of the selection
			selection_ = - selection_;
		}
		for (int i = 0; i < selection_ && caret_ < text_.length(); ++i) {
			text_.remove(caret_, 1);
		}
		selection_ = 0;
		invalidateText();
	}

	// Insert text at the caret
	int i;
	for (i = 0; i < (int)replacement.length() && text_.length() + 1 <= maxLength_; ++i) {
		text_.insert(caret_ + i, replacement.at(i));
	}
	setCaret(caret_ + i);
}