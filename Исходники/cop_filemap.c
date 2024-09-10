int cop_filemap_open(struct cop_filemap *map, const char *filename, unsigned flags)
{
	DWORD faccess;
	DWORD mapprotect;
	DWORD mapaccess;
	LARGE_INTEGER fsz;
	LPWSTR wfn;
	int fnlen;

	if ((flags & COP_FILEMAP_FLAG_W) == 0) {
		/* read only access */
		faccess    = GENERIC_READ;
		mapprotect = PAGE_READONLY;
		mapaccess  = FILE_MAP_READ;
	} else if ((flags & COP_FILEMAP_SHARED)) {
		/* shared write access */
		faccess    = GENERIC_READ | GENERIC_WRITE;
		mapprotect = PAGE_READWRITE;
		mapaccess  = FILE_MAP_WRITE;
	} else {
		/* unshared write access */
		faccess    = GENERIC_READ;
		mapprotect = PAGE_READONLY;
		mapaccess  = FILE_MAP_COPY;
	}

	fnlen = MultiByteToWideChar(CP_UTF8, 0, filename, -1, NULL, 0);
	if (fnlen == 0)
		return -1;

	wfn = malloc(sizeof(*wfn) * fnlen);
	if (wfn == NULL)
		return -1;

	if (MultiByteToWideChar(CP_UTF8, 0, filename, -1, wfn, fnlen) != fnlen) {
		free(wfn);
		return -1;
	}

	map->filehandle = CreateFileW(wfn, faccess, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (map->filehandle == INVALID_HANDLE_VALUE) {
		free(wfn);
		return -1;
	}

	free(wfn);

	if (!GetFileSizeEx(map->filehandle, &fsz)) {
		CloseHandle(map->filehandle);
		return -1;
	}

	if (fsz.QuadPart > SIZE_MAX) {
		CloseHandle(map->filehandle);
		return -1;
	}

	map->size = (size_t)fsz.QuadPart;

	map->maphandle = CreateFileMapping(map->filehandle, NULL, mapprotect, 0, 0, NULL);
	if (map->maphandle == INVALID_HANDLE_VALUE) {
		CloseHandle(map->filehandle);
		return -1;
	}

	map->ptr = MapViewOfFile(map->maphandle, mapaccess, 0, 0, 0);
	if (map->ptr == NULL) {
		CloseHandle(map->maphandle);
		CloseHandle(map->filehandle);
		return -1;
	}

	return 0;
}