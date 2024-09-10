static int
_win32_create_temp_file(_zip_source_win32_read_file_t *ctx)
{
    zip_uint32_t value;
    /*
    Windows has GetTempFileName(), but it closes the file after
    creation, leaving it open to a horrible race condition. So
    we reinvent the wheel.
    */
    int i;
    HANDLE th = INVALID_HANDLE_VALUE;
    void *temp = NULL;
    SECURITY_INFORMATION si;
    SECURITY_ATTRIBUTES sa;
    PSECURITY_DESCRIPTOR psd = NULL;
    PSECURITY_ATTRIBUTES psa = NULL;
    DWORD len;
    BOOL success;

    /*
    Read the DACL from the original file, so we can copy it to the temp file.
    If there is no original file, or if we can't read the DACL, we'll use the
    default security descriptor.
    */
    if (ctx->h != INVALID_HANDLE_VALUE && GetFileType(ctx->h) == FILE_TYPE_DISK) {
	si = DACL_SECURITY_INFORMATION | UNPROTECTED_DACL_SECURITY_INFORMATION;
	len = 0;
	success = GetUserObjectSecurity(ctx->h, &si, NULL, len, &len);
	if (!success && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
	    if ((psd = (PSECURITY_DESCRIPTOR)malloc(len)) == NULL) {
		zip_error_set(&ctx->error, ZIP_ER_MEMORY, 0);
		return -1;
	    }
	    success = GetUserObjectSecurity(ctx->h, &si, psd, len, &len);
	}
	if (success) {
	    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	    sa.bInheritHandle = FALSE;
	    sa.lpSecurityDescriptor = psd;
	    psa = &sa;
	}
    }

    value = GetTickCount();
    for (i = 0; i < 1024 && th == INVALID_HANDLE_VALUE; i++) {
	th = ctx->ops->op_create_temp(ctx, &temp, value + i, psa);
	if (th == INVALID_HANDLE_VALUE && GetLastError() != ERROR_FILE_EXISTS)
	    break;
    }

    if (th == INVALID_HANDLE_VALUE) {
	free(temp);
	free(psd);
	zip_error_set(&ctx->error, ZIP_ER_TMPOPEN, _zip_win32_error_to_errno(GetLastError()));
	return -1;
    }

    free(psd);
    ctx->hout = th;
    ctx->tmpname = temp;

    return 0;
}