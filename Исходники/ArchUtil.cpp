FILETIME ArchFile::GetFileTime(size_t fileindex)
{
    FILETIME ft = { (DWORD)-1, (DWORD)-1 };
    if (ar && fileindex < filepos.Count() && ar_parse_entry_at(ar, filepos.At(fileindex))) {
        time64_t filetime = ar_entry_get_filetime(ar);
        LocalFileTimeToFileTime((FILETIME *)&filetime, &ft);
    }
    return ft;
}