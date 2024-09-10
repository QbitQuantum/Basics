bool Gpackage::write_file(const WCHAR *path, const BYTE *filename, const BYTE *uncompr, UINT uncompr_len)
{
    WCHAR wfilename[MAX_FILENAME_LEN * 3 + MAX_PATH];
    size_t path_len = wcsnlen_s(path, MAX_PATH);
    wcscpy_s(wfilename, MAX_PATH-1, path);
    wcscpy_s(wfilename + path_len, 2, L"\\");

    if (!ansi_shift_jis_to_utf16((CHAR*)filename, wfilename+path_len+1, MAX_FILENAME_LEN * 3))
        return false;

    WCHAR *sep = wcsrchr((WCHAR *)wfilename, L'\\');
    HANDLE un_file = INVALID_HANDLE_VALUE;
    if (sep != nullptr) {
        WCHAR temp_char = *sep;
        *sep = L'\0';
        create_directory_r(wfilename);
        *sep = temp_char;
    }
    un_file = CreateFileW(wfilename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    if (un_file == INVALID_HANDLE_VALUE)
        return false;

    DWORD number_of_bytes_written;
    if (!WriteFile(un_file, uncompr, uncompr_len, &number_of_bytes_written, NULL))
        return false;
    return true;
}