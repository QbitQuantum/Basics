HANDLE RLDecode(char *szFileName)
{
    FILE *In;
    long length;
    HANDLE hMemory;
    LPSTR lpMemory;

    In = fopen(szFileName, "rb");
    if (!In)
        return FALSE;

    fread(&length, sizeof(long), 1, In);

    hMemory = GLOBALALLOC(GHND, length);
    if (!hMemory)
        return NULL;
    
    lpMemory = GLOBALLOCK(hMemory);
    if (!lpMemory)
    {
        GLOBALFREE(hMemory);
        return NULL;
    }
    
    rle_decomp(In, lpMemory);

    fclose(In);
    GLOBALUNLOCK(hMemory);
    
    return hMemory;
}