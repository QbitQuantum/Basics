static HANDLE
_win32_open_w(_zip_source_win32_read_file_t *ctx)
{
#ifdef WINRT
    CREATEFILE2_EXTENDED_PARAMETERS extParams = { 0 };
    extParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
    extParams.dwFileFlags = FILE_FLAG_RANDOM_ACCESS;
    extParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
    extParams.dwSize = sizeof(extParams);
    extParams.hTemplateFile = NULL;
    extParams.lpSecurityAttributes = NULL;

    return CreateFile2(ctx->fname, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING, &extParams);
#else
    return CreateFileW(ctx->fname, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
#endif
}