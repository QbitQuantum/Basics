/*
 * Do not use Windows tmpfile() function.
 * It will make a temporary file under the root directory
 * and it'll cause permission error if a user who is
 * non-Administrator creates temporary files.
 * Also Windows version of mktemp family including _mktemp_s
 * are not secure.
 */
int
__archive_mktemp(const char *tmpdir)
{
	static const wchar_t *prefix = L"libarchive_";
	static const wchar_t *suffix = L"XXXXXXXXXX";
	static const wchar_t num[] = {
		L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7',
		L'8', L'9', L'A', L'B', L'C', L'D', L'E', L'F',
		L'G', L'H', L'I', L'J', L'K', L'L', L'M', L'N',
		L'O', L'P', L'Q', L'R', L'S', L'T', L'U', L'V',
		L'W', L'X', L'Y', L'Z', L'a', L'b', L'c', L'd',
		L'e', L'f', L'g', L'h', L'i', L'j', L'k', L'l',
		L'm', L'n', L'o', L'p', L'q', L'r', L's', L't',
		L'u', L'v', L'w', L'x', L'y', L'z'
	};
	HCRYPTPROV hProv;
	struct archive_wstring temp_name;
	wchar_t *ws;
	DWORD attr;
	wchar_t *xp, *ep;
	int fd;

	hProv = (HCRYPTPROV)NULL;
	fd = -1;
	ws = NULL;
	archive_string_init(&temp_name);

	/* Get a temporary directory. */
	if (tmpdir == NULL) {
		size_t l;
		wchar_t *tmp;

		l = GetTempPathW(0, NULL);
		if (l == 0) {
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}
		tmp = malloc(l*sizeof(wchar_t));
		if (tmp == NULL) {
			errno = ENOMEM;
			goto exit_tmpfile;
		}
		GetTempPathW((DWORD)l, tmp);
		archive_wstrcpy(&temp_name, tmp);
		free(tmp);
	} else {
		if (archive_wstring_append_from_mbs(&temp_name, tmpdir,
		    strlen(tmpdir)) < 0)
			goto exit_tmpfile;
		if (temp_name.s[temp_name.length-1] != L'/')
			archive_wstrappend_wchar(&temp_name, L'/');
	}

	/* Check if temp_name is a directory. */
	attr = GetFileAttributesW(temp_name.s);
	if (attr == (DWORD)-1) {
		if (GetLastError() != ERROR_FILE_NOT_FOUND) {
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}
		ws = __la_win_permissive_name_w(temp_name.s);
		if (ws == NULL) {
			errno = EINVAL;
			goto exit_tmpfile;
		}
		attr = GetFileAttributesW(ws);
		if (attr == (DWORD)-1) {
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}
	}
	if (!(attr & FILE_ATTRIBUTE_DIRECTORY)) {
		errno = ENOTDIR;
		goto exit_tmpfile;
	}

	/*
	 * Create a temporary file.
	 */
	archive_wstrcat(&temp_name, prefix);
	archive_wstrcat(&temp_name, suffix);
	ep = temp_name.s + archive_strlen(&temp_name);
	xp = ep - wcslen(suffix);

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
		CRYPT_VERIFYCONTEXT)) {
		la_dosmaperr(GetLastError());
		goto exit_tmpfile;
	}

	for (;;) {
		wchar_t *p;
		HANDLE h;

		/* Generate a random file name through CryptGenRandom(). */
		p = xp;
		if (!CryptGenRandom(hProv, (DWORD)(ep - p)*sizeof(wchar_t),
		    (BYTE*)p)) {
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}
		for (; p < ep; p++)
			*p = num[((DWORD)*p) % (sizeof(num)/sizeof(num[0]))];

		free(ws);
		ws = __la_win_permissive_name_w(temp_name.s);
		if (ws == NULL) {
			errno = EINVAL;
			goto exit_tmpfile;
		}
		/* Specifies FILE_FLAG_DELETE_ON_CLOSE flag is to
		 * delete this temporary file immediately when this
		 * file closed. */
		h = CreateFileW(ws,
		    GENERIC_READ | GENERIC_WRITE | DELETE,
		    0,/* Not share */
		    NULL,
		    CREATE_NEW,/* Create a new file only */
		    FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE,
		    NULL);
		if (h == INVALID_HANDLE_VALUE) {
			/* The same file already exists. retry with
			 * a new filename. */
			if (GetLastError() == ERROR_FILE_EXISTS)
				continue;
			/* Otherwise, fail creation temporary file. */
			la_dosmaperr(GetLastError());
			goto exit_tmpfile;
		}
		fd = _open_osfhandle((intptr_t)h, _O_BINARY | _O_RDWR);
		if (fd == -1) {
			CloseHandle(h);
			goto exit_tmpfile;
		} else
			break;/* success! */
	}
exit_tmpfile:
	if (hProv != (HCRYPTPROV)NULL)
		CryptReleaseContext(hProv, 0);
	free(ws);
	archive_wstring_free(&temp_name);
	return (fd);
}