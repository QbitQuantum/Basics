wxString inline_string_encode(wxString &input)
{
	const size_t inlen = input.length();
	wxString output(_T(""));
	output.Alloc(inlen);
	for (size_t i = 0; i < inlen; i++) {
		wxChar c = input[i];
		if (c <= 0x1F || c == 0x23 || c == 0x2C || c == 0x3A || c == 0x7C) {
			output << wxString::Format(_T("#%02X"), c);
		} else {
			output << c;
		}
	}
	return output;
}