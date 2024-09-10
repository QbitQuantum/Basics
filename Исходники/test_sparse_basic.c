static void
create_sparse_file(const char *path, const struct sparse *s)
{
	char buff[1024];
	HANDLE handle;
	DWORD dmy;

	memset(buff, ' ', sizeof(buff));

	handle = CreateFileA(path, GENERIC_WRITE, 0,
	    NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
	    NULL);
	assert(handle != INVALID_HANDLE_VALUE);
	assert(DeviceIoControl(handle, FSCTL_SET_SPARSE, NULL, 0,
	    NULL, 0, &dmy, NULL) != 0);
	while (s->type != END) {
		if (s->type == HOLE) {
			LARGE_INTEGER distance;

			distance.QuadPart = s->size;
			assert(SetFilePointerEx(handle, distance,
			    NULL, FILE_CURRENT) != 0);
		} else {
			DWORD w, wr;
			size_t size;

			size = s->size;
			while (size) {
				if (size > sizeof(buff))
					w = sizeof(buff);
				else
					w = (DWORD)size;
				assert(WriteFile(handle, buff, w, &wr, NULL) != 0);
				size -= wr;
			}
		}
		s++;
	}
	assertEqualInt(CloseHandle(handle), 1);
}