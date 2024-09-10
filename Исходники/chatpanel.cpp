static size_t FirstSpecialChar(const wxString& str)
{
	for (size_t pos = 0; pos < str.Len(); pos++) {
		if (!str.GetChar(pos).IsAscii()) {
			continue;
		}
		const unsigned char uc = str.GetChar(pos);
		if (uc == 0x1f || uc == 0x1d || uc == 0x03 || uc == 0x02 || uc == 0x016 || uc == 0x0F) { //get all text until first irc color is found
			return pos;
		}
	}
	return -1;
}