/*
 * Note: We should use wide-character for findng '\' character,
 * a directory separator on Windows, because some character-set have
 * been using the '\' character for a part of its multibyte character
 * code.
 */
static size_t
dir_len(struct archive_entry *entry)
{
	wchar_t wc;
	const char *path;
	const char *p, *rp;
	size_t al, l, size;

	path = tk_archive_entry_pathname(entry);
	al = l = -1;
	for (p = path; *p != '\0'; ++p) {
		if (*p == '\\')
			al = l = p - path;
		else if (*p == '/')
			al = p - path;
	}
	if (l == -1)
		goto alen;
	size = p - path;
	rp = p = path;
	while (*p != '\0') {
		l = mbtowc(&wc, p, size);
		if (l == -1)
			goto alen;
		if (l == 1 && (wc == L'/' || wc == L'\\'))
			rp = p;
		p += l;
		size -= l;
	}
	return (rp - path + 1);
alen:
	if (al == -1)
		return (0);
	return (al + 1);
}