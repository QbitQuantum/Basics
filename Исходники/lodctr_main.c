int wmain(int argc, WCHAR *argv[])
{
    return LoadPerfCounterTextStringsW(GetCommandLineW(), FALSE);
}