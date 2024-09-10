// <FS:Ansariel> Fix linefeed pasting
//virtual
void LLChatEntry::paste()
{
	LLTextEditor::paste();

	if (mSingleLineMode)
	{
		S32 cursor_pos = getCursorPos();
		LLWString content = getWText();
		LLWStringUtil::replaceChar(content, '\n', llwchar(182));
		setWText(content);
		setCursorPos(cursor_pos);
	}
}