SourceFile* SourceFile::Create(
    DWORD_PTR ModuleToken,
    wstring& ModuleName,
    wstring& FileName
    )
{
    BOOL Success;
    FILE_STANDARD_INFO Info;
    LPCWSTR Path = FileName.c_str();
    HANDLE FileMappingHandle;
    PVOID Data;
    PVOID Buffer;
    DWORD FileSize;
    HANDLE FileHandle;

    FileHandle = CreateFile(
        Path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_READONLY,
        NULL
    );

    if (FileHandle == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    Success = GetFileInformationByHandleEx(
        FileHandle,
        (FILE_INFO_BY_HANDLE_CLASS)FileStandardInfo,
        &Info,
        sizeof(Info)
    );
    if (!Success) {
        CloseHandle(FileHandle);
        return NULL;
    }

    // Don't support source files greater than 2GB.
    if (Info.EndOfFile.HighPart != 0) {
        CloseHandle(FileHandle);
        return NULL;
    }
    FileSize = Info.EndOfFile.LowPart;

    FileMappingHandle = CreateFileMapping(
        FileHandle,
        NULL,
        PAGE_READONLY,
        0,
        0,
        NULL
    );

    if (FileMappingHandle == INVALID_HANDLE_VALUE) {
        CloseHandle(FileHandle);
        return NULL;
    }

    Data = MapViewOfFile(FileMappingHandle, FILE_MAP_READ, 0, 0, 0);
    if (Data == NULL) {
        CloseHandle(FileMappingHandle);
        CloseHandle(FileHandle);
        return NULL;
    }

    Buffer = VirtualAlloc(0, FileSize, MEM_COMMIT, PAGE_READWRITE);
    if (Buffer == NULL) {
        UnmapViewOfFile(Data);
        CloseHandle(FileMappingHandle);
        CloseHandle(FileHandle);
        return NULL;
    }

    PCHAR Source = (PCHAR)Data;
    PCHAR Dest = (PCHAR)Buffer;
    DWORD Lines = 0;
    DWORD NextLine = 0;
    DWORD InitialSize = (FileSize >= 30 ? FileSize / 30 : 3);

    vector<DWORD> LineOffsets(InitialSize);
    // LineOffsets[0] = 0 -> dummy entry.
    // LineOffsets[1] = 0 -> byte offset of first line will always be 0.
    LineOffsets[Lines++] = 0;
    LineOffsets[Lines++] = 0;
    // Copy the file contents from Source to Dest, converting \r and \n
    // to \0 as we go (allowing the underlying buffer to be cast as a
    // NUL-terminated C string).
    for (DWORD i = 0; i < FileSize; i++) {
        CHAR c = Source[i];
        if (c == '\r') {
            Dest[i] = 0;
            continue;
        } else if (c == '\n') {
            NextLine = i + 1;
            Dest[i] = 0;
        } else {
            Dest[i] = Source[i];
            continue;
        }

        if (Lines == LineOffsets.size()) {
            LineOffsets.resize(LineOffsets.size() + 100);
        }
        LineOffsets[Lines++] = i + 1;
    }

    LineOffsets.resize(Lines);

    UnmapViewOfFile(Data);
    CloseHandle(FileMappingHandle);
    CloseHandle(FileHandle);

    SourceFile *pSourceFile = new SourceFile(
        ModuleToken,
        ModuleName,
        FileName,
        FileSize,
        (PCHAR)Buffer,
        Lines,
        LineOffsets
    );

    return pSourceFile;
}