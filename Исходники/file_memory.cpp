bool File::Open(const wchar *Name, uint Mode) {
    wcsncpy(FileName, Name, wcsnlen(Name, 2048));
    if (part > 0) {
        shared_stream->next_stream_file();
    }

    part++;

    return true;
}