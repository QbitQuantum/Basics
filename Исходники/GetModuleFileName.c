static
VOID
TestGetModuleFileNameW(VOID)
{
    WCHAR Buffer[MAX_PATH];
    DWORD Length;
    BOOL Relative;

    Length = GetModuleFileNameW(NULL, Buffer, sizeof(Buffer) / sizeof(WCHAR));
    ok(Length != 0, "Length = %lu\n", Length);
    ok(Length < sizeof(Buffer) / sizeof(WCHAR), "Length = %lu\n", Length);
    ok(Buffer[Length] == 0, "Buffer not null terminated\n");
    Relative = PathIsRelativeW(Buffer);
    ok(Relative == FALSE, "GetModuleFileNameW returned relative path: %ls\n", Buffer);
}