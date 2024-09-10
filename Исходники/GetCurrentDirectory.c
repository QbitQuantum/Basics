static
VOID
TestGetCurrentDirectoryW(VOID)
{
    WCHAR Buffer[MAX_PATH];
    DWORD Length;
    BOOL Ret;
    BOOLEAN Okay;

    Ret = SetCurrentDirectoryW(L"C:\\");
    ok(Ret == TRUE, "SetCurrentDirectory failed with %lu\n", GetLastError());

    Length = GetCurrentDirectoryW(0, NULL);
    ok(Length == sizeof("C:\\"), "Length = %lu\n", Length);

    RtlFillMemory(Buffer, sizeof(Buffer), 0x55);
    Length = GetCurrentDirectoryW(sizeof(Buffer) / sizeof(WCHAR), Buffer);
    ok(Length == sizeof("C:\\") - 1, "Length = %lu\n", Length);
    Okay = CheckStringBufferW(Buffer, sizeof(Buffer), L"C:\\", 0x55);
    ok(Okay, "CheckStringBufferW failed\n");

    RtlFillMemory(Buffer, sizeof(Buffer), 0x55);
    Length = GetCurrentDirectoryW(0, Buffer);
    ok(Length == sizeof("C:\\"), "Length = %lu\n", Length);
    Okay = CheckBuffer(Buffer, sizeof(Buffer), 0x55);
    ok(Okay, "CheckBuffer failed\n");

    RtlFillMemory(Buffer, sizeof(Buffer), 0x55);
    Length = GetCurrentDirectoryW(1, Buffer);
    ok(Length == sizeof("C:\\"), "Length = %lu\n", Length);
    Okay = CheckBuffer(Buffer, sizeof(Buffer), 0x55);
    ok(Okay, "CheckBuffer failed\n");

    RtlFillMemory(Buffer, sizeof(Buffer), 0x55);
    Length = GetCurrentDirectoryW(2, Buffer);
    ok(Length == sizeof("C:\\"), "Length = %lu\n", Length);
    Okay = CheckBuffer(Buffer, sizeof(Buffer), 0x55);
    ok(Okay, "CheckBuffer failed\n");

    RtlFillMemory(Buffer, sizeof(Buffer), 0x55);
    Length = GetCurrentDirectoryW(3, Buffer);
    ok(Length == sizeof("C:\\"), "Length = %lu\n", Length);
    Okay = CheckBuffer(Buffer, sizeof(Buffer), 0x55);
    ok(Okay, "CheckBuffer failed\n");

    RtlFillMemory(Buffer, sizeof(Buffer), 0x55);
    Length = GetCurrentDirectoryW(4, Buffer);
    ok(Length == sizeof("C:\\") - 1, "Length = %lu\n", Length);
    Okay = CheckStringBufferW(Buffer, sizeof(Buffer), L"C:\\", 0x55);
    ok(Okay, "CheckStringBufferW failed\n");
}