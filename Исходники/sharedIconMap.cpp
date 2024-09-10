// if name not contain dot { return false; } else { if (ext) *ext = toLower(name[head:tail]); return true; }
//inline bool findNormalizedExt(wchar_t const *name, std::wstring *ext) { return name; } // pass traling spaces, slashes
inline bool findNormalizedExt(wchar_t const *name, std::wstring *ext) {
	if (!name)
		return false;

	wchar_t const *badTralingCharacters = L"\\/\t ";
	wchar_t const *v = name + ::wcslen(name);
	if (v == name)
		return false;
	--v;

	while ((v != name) && (::wcschr(badTralingCharacters, *v)))
		--v;
	if (v == name)
		return false;

	wchar_t const *tail = v;
	while ((v != name) && (L'.' != *v))
		--v;
	if ((L'.' != *v) || (v == tail))
		return false;

	if (ext) {
		ext->assign(++v, ++tail);
		_wcslwr(const_cast<wchar_t*>(ext->c_str()));
		// _wcslwr_s(const_cast<wchar_t*>(ext->c_str()), ext->size() + 1);
	}
	return true;
}