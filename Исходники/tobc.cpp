ForceInline Int main2(Int argc, WChar **argv)
{
    if (argc == 1)
    {
        printf("ToB (Text of Binary) Compiler 0.3 [by dwing] 2009-02-28\n"
               "Usage: tobc <src_file> [dst_file]\n");
        return 1;
    }

    BOOL   Result;
    WCHAR  szCurPath[MAX_PATH], szScriptPath[MAX_PATH];
    LPWSTR fsrcname, fdstname;

    fsrcname = argv[1];
    fdstname = argc > 2 ? argv[2] : NULL;

    lstrcpyW(szScriptPath, fsrcname);
    rmnamew(szScriptPath);
    GetCurrentDirectoryW(countof(szCurPath), szCurPath);
    SetCurrentDirectoryW(szScriptPath);

    setlocale(LC_CTYPE, ".936");
    printf("Compiling %S ... ", (LPCTSTR)fsrcname);

    CTobCompiler compiler;

    Result = compiler.CompileFile(fsrcname, fdstname, &CTobCompiler::ErrorHandlerInternal);
    SetCurrentDirectoryW(szCurPath);
    if (!Result)
        return -1;

    fdstname = fdstname == NULL ? L"" : fdstname;
    printf("%S OK!\n", (LPCTSTR)fdstname);
    return 0;
}