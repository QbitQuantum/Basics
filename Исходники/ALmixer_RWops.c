static int64_t ALMIXER_CALL
windows_file_size(ALmixer_RWops * context)
{
    LARGE_INTEGER size;

    if (!context || context->hidden.windowsio.h == INVALID_HANDLE_VALUE) {
        ALmixer_SetError("windows_file_size: invalid context/file not opened");
		return -1;
	}

    if (!GetFileSizeEx(context->hidden.windowsio.h, &size)) {
#if 1
        return WIN_SetError("windows_file_size");
#else
		/* There are a lot of dependencies on iconv/UTF16 stuff just for WIN_SetError to print the HRESULT. I'd rather avoid it */
		ALmixer_SetError("windows_file_size failed calling GetFileSizeEx()");
		return -1;
#endif
    }

    return size.QuadPart;
}