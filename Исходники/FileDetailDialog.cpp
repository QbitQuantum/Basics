void ReplaceWord(wxString& str, const wxString& replaceFrom, const wxString& replaceTo, bool numbers = false)
{
	unsigned int i = 0;
	unsigned int l = replaceFrom.Length();
	while (i < str.Length()) {
		if (str.Mid(i, l) == replaceFrom) {
			if ((i == 0 || IsWordSeparator(str.GetChar(i-1))) &&
				((i == str.Length() - l || IsWordSeparator(str.GetChar(i+l))) ||
					(numbers && IsDigit(str.GetChar(i+l))))) {
				str.replace(i, l, replaceTo);
			}
			i += replaceTo.Length() - 1;
		}
		i++;
	}
}