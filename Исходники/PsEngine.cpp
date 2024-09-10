static PdfEngine *ps2pdf(const WCHAR *fileName)
{
    // TODO: read from gswin32c's stdout instead of using a TEMP file
    ScopedMem<WCHAR> shortPath(path::ShortPath(fileName));
    ScopedMem<WCHAR> tmpFile(path::GetTempPath(L"PsE"));
    ScopedFile tmpFileScope(tmpFile);
    ScopedMem<WCHAR> gswin32c(GetGhostscriptPath());
    if (!shortPath || !tmpFile || !gswin32c)
        return NULL;
    ScopedMem<WCHAR> cmdLine(str::Format(L"\"%s\" -q -dSAFER -dNOPAUSE -dBATCH -dEPSCrop -sOutputFile=\"%s\" -sDEVICE=pdfwrite -c .setpdfwrite -f \"%s\"", gswin32c, tmpFile, shortPath));

    if (GetEnvironmentVariable(L"MULOG", NULL, 0)) {
        wprintf(L"ps2pdf: using Ghostscript from '%s'\n", gswin32c.Get());
        wprintf(L"ps2pdf: for creating '%s'\n", tmpFile.Get());
    }

    // TODO: the PS-to-PDF conversion can hang the UI for several seconds
    HANDLE process = LaunchProcess(cmdLine, NULL, CREATE_NO_WINDOW);
    if (!process)
        return NULL;

    DWORD exitCode = EXIT_FAILURE;
    WaitForSingleObject(process, 10000);
    GetExitCodeProcess(process, &exitCode);
    TerminateProcess(process, 1);
    CloseHandle(process);
    if (exitCode != EXIT_SUCCESS)
        return NULL;

    size_t len;
    ScopedMem<char> pdfData(file::ReadAll(tmpFile, &len));
    if (!pdfData)
        return NULL;

    ScopedComPtr<IStream> stream(CreateStreamFromData(pdfData, len));
    if (!stream)
        return NULL;

    if (GetEnvironmentVariable(L"MULOG", NULL, 0))
        printf("ps2pdf: PDF conversion successful\n");

    return PdfEngine::CreateFromStream(stream);
}