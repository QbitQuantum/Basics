ForceInline Void main2(Int argc, WChar **argv)
{
    FILE *fp;
    LPVoid lpBuffer, lpEndOfBuffer;
    UInt32 BufferSize, FileSize;

    ConvertScriptToUnicode(argc, argv);
    return;

    BufferSize = 0x1000;
    lpBuffer = malloc(BufferSize);
    _wsetlocale(LC_CTYPE, L"");
    for (Int32 i = 1; i != argc; ++i)
    {
        fp = _wfopen(*++argv, L"rb+");
        if (!fp)
        {
            _wperror(*argv);
            continue;
        }

        FileSize = fsize(fp);
        if (FileSize > BufferSize)
        {
            BufferSize = FileSize;
            lpBuffer = realloc(lpBuffer, BufferSize);
        }

        fread(lpBuffer, FileSize, 1, fp);
        fclose(fp);
        if (*(PUInt16)lpBuffer != 0xFEFF)
        {
            wprintf(L"%s\nsupport unicode only\n\n", *argv);
            fclose(fp);
            continue;
        }

        lpEndOfBuffer = (PByte)lpBuffer + FileSize;
        ProcessFile((PByte)lpBuffer + 2, lpEndOfBuffer, *argv);
    }

    free(lpBuffer);
}