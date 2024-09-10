LONG gfile_get_length(GFile *gf)
{
    BY_HANDLE_FILE_INFORMATION fi;
    ASSERT(gf != NULL);
    GetFileInformationByHandle((HANDLE)gf->m_hFile, &fi);
    return fi.nFileSizeLow;
}