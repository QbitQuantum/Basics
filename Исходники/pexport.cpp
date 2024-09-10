// Import a file in the portable format and return a pointer to the root object.
PolyObject *ImportPortable(const TCHAR *fileName)
{
    PImport pImport;
#if (defined(_WIN32) && defined(UNICODE))
    pImport.f = _wfopen(fileName, L"r");
    if (pImport.f == 0)
    {
        fprintf(stderr, "Unable to open file: %S\n", fileName);
        return 0;
    }
#else
    pImport.f = fopen(fileName, "r");
    if (pImport.f == 0)
    {
        fprintf(stderr, "Unable to open file: %s\n", fileName);
        return 0;
    }
#endif
    if (pImport.DoImport())
        return pImport.Root();
    else
        return 0;
}