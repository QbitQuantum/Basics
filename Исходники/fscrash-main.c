static VOID Test(PWSTR Prefix)
{
    static PWSTR Sddl = L"D:P(A;;GA;;;SY)(A;;GA;;;BA)(A;;GA;;;WD)";
    static const GUID ReparseGuid =
        { 0x2cf25cfa, 0x41af, 0x4796, { 0xb5, 0xef, 0xac, 0xa3, 0x85, 0x3, 0xe2, 0xd8 } };
    WCHAR FileName[1024], VolumeName[MAX_PATH];
    PSECURITY_DESCRIPTOR SecurityDescriptor;
    HANDLE Handle;
    BOOL Success;
    UINT8 RdBuffer[4096], WrBuffer[4096];
    REPARSE_GUID_DATA_BUFFER ReparseDataBuf;
    DWORD BytesTransferred, Offset;
    WIN32_FIND_DATAW FindData;
    WIN32_FIND_STREAM_DATA FindStreamData;

    memset(WrBuffer, 'B', sizeof WrBuffer);

    Success = ConvertStringSecurityDescriptorToSecurityDescriptorW(
        Sddl, SDDL_REVISION_1, &SecurityDescriptor, 0);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\", Prefix);
    Success = GetVolumeInformationW(FileName, VolumeName, MAX_PATH, 0, 0, 0, 0, 0);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\", Prefix);
    Success = SetVolumeLabelW(FileName, VolumeName);
    //ASSERT(Success);

    wsprintfW(FileName, L"%s\\fscrash", Prefix);
    Success = CreateDirectoryW(FileName, 0);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\fscrash\\file0", Prefix);
    Handle = CreateFileW(FileName,
        GENERIC_ALL, 0, 0,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    ASSERT(INVALID_HANDLE_VALUE != Handle);
    Success = CloseHandle(Handle);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\fscrash\\file0", Prefix);
    Handle = CreateFileW(FileName,
        GENERIC_ALL, 0, 0,
        CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    ASSERT(INVALID_HANDLE_VALUE != Handle);

    Success = WriteFile(Handle, WrBuffer, sizeof WrBuffer, &BytesTransferred, 0);
    ASSERT(Success);
    ASSERT(sizeof WrBuffer == BytesTransferred);

    Success = FlushFileBuffers(Handle);
    ASSERT(Success);

    Offset = SetFilePointer(Handle, 0, 0, FILE_BEGIN);
    ASSERT(0 == Offset);

    Success = ReadFile(Handle, RdBuffer, sizeof RdBuffer, &BytesTransferred, 0);
    ASSERT(Success);
    ASSERT(sizeof WrBuffer == BytesTransferred);

    Offset = SetFilePointer(Handle, 0, 0, FILE_BEGIN);
    ASSERT(0 == Offset);

    Success = SetEndOfFile(Handle);
    ASSERT(Success);

    Offset = GetFileSize(Handle, 0);
    ASSERT(0 == Offset);

    Success = LockFile(Handle, 0, 0, 1, 0);
    ASSERT(Success);

    Success = UnlockFile(Handle, 0, 0, 1, 0);
    ASSERT(Success);

    Success = SetKernelObjectSecurity(Handle, DACL_SECURITY_INFORMATION, SecurityDescriptor);
    ASSERT(Success);

    Success = GetKernelObjectSecurity(Handle, DACL_SECURITY_INFORMATION, 0, 0, &BytesTransferred);
    ASSERT(!Success);
    ASSERT(ERROR_INSUFFICIENT_BUFFER == GetLastError());

    ReparseDataBuf.ReparseTag = 0x1234;
    ReparseDataBuf.ReparseDataLength = 0;
    ReparseDataBuf.Reserved = 0;
    memcpy(&ReparseDataBuf.ReparseGuid, &ReparseGuid, sizeof ReparseGuid);

    Success = DeviceIoControl(Handle, FSCTL_SET_REPARSE_POINT,
        &ReparseDataBuf, REPARSE_GUID_DATA_BUFFER_HEADER_SIZE + ReparseDataBuf.ReparseDataLength,
        0, 0,
        &BytesTransferred, 0);
    ASSERT(Success);

    Success = CloseHandle(Handle);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\fscrash\\*", Prefix);
    Handle = FindFirstFileW(FileName, &FindData);
    ASSERT(INVALID_HANDLE_VALUE != Handle);
    do
    {
    } while (FindNextFileW(Handle, &FindData));
    ASSERT(ERROR_NO_MORE_FILES == GetLastError());
    Success = FindClose(Handle);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\fscrash\\file0", Prefix);
    Handle = FindFirstStreamW(FileName, FindStreamInfoStandard, &FindStreamData, 0);
    ASSERT(INVALID_HANDLE_VALUE != Handle);
    do
    {
    } while (FindNextStreamW(Handle, &FindStreamData));
    ASSERT(ERROR_HANDLE_EOF == GetLastError());
    Success = FindClose(Handle);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\fscrash\\file0", Prefix);
    Success = DeleteFileW(FileName);
    ASSERT(Success);

    wsprintfW(FileName, L"%s\\fscrash", Prefix);
    Success = RemoveDirectoryW(FileName);
    ASSERT(Success);

    LocalFree(SecurityDescriptor);
}