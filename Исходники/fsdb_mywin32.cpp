static int recycle (const TCHAR *name)
{
	DWORD dirattr = GetFileAttributesSafe (name);
	bool isdir = dirattr != INVALID_FILE_ATTRIBUTES && (dirattr & FILE_ATTRIBUTE_DIRECTORY);
	const TCHAR *namep;
	TCHAR path[MAX_DPATH];
	
	if (currprefs.win32_filesystem_mangle_reserved_names == false) {
		_tcscpy (path, PATHPREFIX);
		_tcscat (path, name);
		namep = path;
	} else {
		namep = name;
	}

	if (currprefs.win32_norecyclebin || isdir || currprefs.win32_filesystem_mangle_reserved_names == false) {
		if (isdir)
			return RemoveDirectory (namep) ? 0 : -1;
		else
			return DeleteFile (namep) ? 0 : -1;
	} else {
		SHFILEOPSTRUCT fos;
		HANDLE h;
		
		h = CreateFile (namep, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h != INVALID_HANDLE_VALUE) {
			LARGE_INTEGER size;
			if (GetFileSizeEx (h, &size)) {
				if (size.QuadPart == 0) {
					CloseHandle (h);
					return DeleteFile (namep) ? 0 : -1;
				}
			}
			CloseHandle (h);
		}

		/* name must be terminated by \0\0 */
		TCHAR *p = xcalloc (TCHAR, _tcslen (namep) + 2);
		int v;

		_tcscpy (p, namep);
		memset (&fos, 0, sizeof (fos));
		fos.wFunc = FO_DELETE;
		fos.pFrom = p;
		fos.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NORECURSION | FOF_SILENT;
		v = SHFileOperation (&fos);
		xfree (p);
		switch (v)
		{
		case 0xb7: //DE_ERROR_MAX
		case 0x7c: //DE_INVALIDFILES
		case 0x402: // "unknown error"
			v = ERROR_FILE_NOT_FOUND;
			break;
		case 0x75: //DE_OPCANCELLED:
		case 0x10000: //ERRORONDEST:
		case 0x78: //DE_ACCESSDENIEDSRC:
		case 0x74: //DE_ROOTDIR:
			v = ERROR_ACCESS_DENIED;
			break;
		}
		SetLastError (v);
		return v ? -1 : 0;
	}
}