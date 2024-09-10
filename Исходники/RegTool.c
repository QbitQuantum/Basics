void RegTypeLib(char *file)
{
    WCHAR wfile[STR_SIZE];

    if (MultiByteToWideChar(CP_ACP, 0, file, -1, wfile, STR_SIZE) != 0)
    {
        ITypeLib* tlib;
        if (SUCCEEDED(LoadTypeLib(wfile, &tlib))) {
            RegisterTypeLib(tlib, wfile, NULL);
            tlib->lpVtbl->Release(tlib);
        }
    }
}