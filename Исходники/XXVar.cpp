XPTSTR XXVar::StringIndex(XPTSTR string, int index)
{
	while (index--) {
		if (IsLeadByte(*string)) {
			string++;
			if (!*string) { break; }
		}
		string++;
	}
	return string;
}