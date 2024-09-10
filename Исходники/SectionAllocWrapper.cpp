void UnmapView(HANDLE process, PVOID address)
{
#if USEFILEMAP2
    UnmapViewOfFile2(process, address, 0);
#else
    NtdllLibrary::Instance->UnmapViewOfSection(process, address);
#endif
}