void
DebugPrint(
    const char *format,
    ...
    )
{
    char output[1024];
    va_list argList;

    va_start(argList, format);
    StringCchVPrintfA(output, ARRAYSIZE(output), format, argList);
    OutputDebugStringA(output);
    va_end(argList);
}