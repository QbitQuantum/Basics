void platformInit(int*, char***)
{
    // Set stdout/stderr binary mode.
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stderr), _O_BINARY);

    // Set theme engine.
    webkit_support::SetThemeEngine(&themeEngine);

    // Load Ahem font.
    // AHEM____.TTF is copied to the directory of DumpRenderTree.exe by WebKit.gyp.
    WCHAR path[_MAX_PATH];
    if (!::GetModuleFileName(0, path, _MAX_PATH)) {
        fprintf(stderr, "Can't get the module path.\n");
        exit(1);
    }
    ::PathRemoveFileSpec(path);
    wcscat_s(path, _MAX_PATH, L"/AHEM____.TTF");
    struct _stat ahemStat;
    if (_wstat(path, &ahemStat) == -1) {
        fprintf(stderr, "Can't access: '%S'\n", path);
        exit(1);
    }

    FILE* fp = _wfopen(path, L"rb");
    if (!fp) {
        _wperror(path);
        exit(1);
    }
    size_t size = ahemStat.st_size;
    char* fontBuffer = new char[size];
    if (fread(fontBuffer, 1, size, fp) != size) {
        fprintf(stderr, "Can't read the font: '%S'\n", path);
        fclose(fp);
        exit(1);
    }
    fclose(fp);
    DWORD numFonts = 1;
    HANDLE fontHandle = ::AddFontMemResourceEx(fontBuffer, size, 0, &numFonts);
    delete[] fontBuffer; // OS owns a copy of the buffer.
    if (!fontHandle) {
        fprintf(stderr, "Failed to register Ahem font: '%S'\n", path);
        exit(1);
    }
    // We don't need to release the font explicitly.
}