/*
================
CSyntaxRichEditCtrl::FindNext
================
*/
bool CSyntaxRichEditCtrl::FindNext(const char *find, bool matchCase, bool matchWholeWords, bool searchForward)
{
	long selStart, selEnd, flags, search, length, start;
	tom::ITextRange *range;

	if (find[0] == '\0') {
		return false;
	}

	GetSel(selStart, selEnd);

	flags = 0;
	flags |= matchCase ? tom::tomMatchCase : 0;
	flags |= matchWholeWords ? tom::tomMatchWord : 0;

	if (searchForward) {
		m_TextDoc->Range(selEnd, GetTextLength(), &range);
		search = GetTextLength() - selEnd;
	} else {
		m_TextDoc->Range(0, selStart, &range);
		search = -selStart;
	}

	if (range->FindShit(A2BSTR(find), search, flags, &length) == S_OK) {

		m_TextDoc->Freeze(NULL);

		range->get_Start(&start);
		range->Release();

		SetSel(start, start + length);

		int line = Max((int) LineFromChar(start) - 5, 0);
		LineScroll(line - GetFirstVisibleLine(), 0);

		UpdateVisibleRange();

		m_TextDoc->Unfreeze(NULL);
		return true;
	} else {
		range->Release();
		return false;
	}
}