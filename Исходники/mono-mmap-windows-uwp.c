void*
mono_file_map (size_t length, int flags, int fd, guint64 offset, void **ret_handle)
{
	void *ptr;
	int mflags = 0;
	HANDLE file, mapping;
	int prot = mono_mmap_win_prot_from_flags (flags);

	mflags = FILE_MAP_READ;
	if (flags & MONO_MMAP_WRITE)
		mflags = FILE_MAP_COPY;

	file = (HANDLE) _get_osfhandle (fd);
	mapping = CreateFileMappingFromApp (file, NULL, prot, length, NULL);

	if (mapping == NULL)
		return NULL;

	ptr = MapViewOfFileFromApp (mapping, mflags, offset, length);

	if (ptr == NULL) {
		CloseHandle (mapping);
		return NULL;
	}

	*ret_handle = (void*)mapping;
	return ptr;
}