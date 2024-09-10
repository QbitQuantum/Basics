size_t *graphemes(WCHAR *msg)
{
	size_t len;
	SCRIPT_ITEM *items;
	int i, n;
	size_t *out;
	size_t *op;
	SCRIPT_LOGATTR *logattr;
	int j, nn;
	HRESULT hr;

	len = wcslen(msg);
	hr = itemize(msg, len, &items, &n);
	if (hr != S_OK)
		logHRESULT(L"error itemizing string for finding grapheme cluster boundaries", hr);

	// should be enough; 2 more just to be safe
	out = (size_t *) uiAlloc((len + 2) * sizeof (size_t), "size_t[]");
	op = out;

	// note that there are actually n + 1 elements in items
	for (i = 0; i < n; i++) {
		nn = items[i + 1].iCharPos - items[i].iCharPos;
		logattr = new SCRIPT_LOGATTR[nn];
		hr = ScriptBreak(msg + items[i].iCharPos, nn,
			&(items[i].a), logattr);
		if (hr != S_OK)
			logHRESULT(L"error breaking string for finding grapheme cluster boundaries", hr);
		for (j = 0; j < nn; j++)
			if (logattr[j].fCharStop != 0)
				*op++ = items[i].iCharPos + j;
		delete[] logattr;
	}
	// and handle the last item for the end of the string
	*op++ = items[i].iCharPos;

	delete[] items;
	return out;
}