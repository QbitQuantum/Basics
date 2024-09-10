void * CPEFile::RvaToPtr(DWORD dwRVA)
{
    PIMAGE_NT_HEADERS32 pNth = GetNtHeader();
    return ImageRvaToVa(pNth,m_pFile->ImageBase,dwRVA,NULL);
}