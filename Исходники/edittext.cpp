void EditTextWidget::handleMouseDown(int x, int y, int button, int clickCount) {
	// First remove caret
	if (_caretVisible)
		drawCaret(true);

	x += _editScrollOffset;

	int width = 0;
	uint i;

	uint last = 0;
	for (i = 0; i < _editString.size(); ++i) {
		const uint cur = _editString[i];
		width += g_gui.getCharWidth(cur, _font) + g_gui.getKerningOffset(last, cur, _font);
		if (width >= x)
			break;
		last = cur;
	}
	if (setCaretPos(i))
		draw();
}