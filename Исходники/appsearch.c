static LPWSTR app_search_file(LPWSTR path, MSISIGNATURE *sig)
{
    VS_FIXEDFILEINFO *info;
    DWORD attr, handle, size;
    LPWSTR val = NULL;
    LPBYTE buffer;

    if (!sig->File)
    {
        PathRemoveFileSpecW(path);
        PathAddBackslashW(path);

        attr = GetFileAttributesW(path);
        if (attr != INVALID_FILE_ATTRIBUTES &&
            (attr & FILE_ATTRIBUTE_DIRECTORY))
            return strdupW(path);

        return NULL;
    }

    attr = GetFileAttributesW(path);
    if (attr == INVALID_FILE_ATTRIBUTES ||
        (attr & FILE_ATTRIBUTE_DIRECTORY))
        return NULL;

    size = GetFileVersionInfoSizeW(path, &handle);
    if (!size)
        return strdupW(path);

    buffer = msi_alloc(size);
    if (!buffer)
        return NULL;

    if (!GetFileVersionInfoW(path, 0, size, buffer))
        goto done;

    if (!VerQueryValueW(buffer, szBackSlash, (LPVOID)&info, &size) || !info)
        goto done;

    if (sig->MinVersionLS || sig->MinVersionMS)
    {
        if (info->dwFileVersionMS < sig->MinVersionMS)
            goto done;

        if (info->dwFileVersionMS == sig->MinVersionMS &&
            info->dwFileVersionLS < sig->MinVersionLS)
            goto done;
    }

    if (sig->MaxVersionLS || sig->MaxVersionMS)
    {
        if (info->dwFileVersionMS > sig->MaxVersionMS)
            goto done;

        if (info->dwFileVersionMS == sig->MaxVersionMS &&
            info->dwFileVersionLS > sig->MaxVersionLS)
            goto done;
    }

    val = strdupW(path);

done:
    msi_free(buffer);
    return val;
}