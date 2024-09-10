TextEdit::TextEdit(const UString &Text, sp<BitmapFont> font)
    : Control(), caretDraw(false), caretTimer(0), text(Text), cursor("*"), font(font),
      editing(false), SelectionStart(Text.length()), TextHAlign(HorizontalAlignment::Left),
      TextVAlign(VerticalAlignment::Centre)
{
	if (font)
	{
		palette = font->getPalette();
	}
}