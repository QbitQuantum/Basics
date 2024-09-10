int EbrStat64i32(const char* filename, struct _stat64i32* ret) {
    CPathMapper map(filename);
    if (!map) {
        TraceError(TAG, L"EbrStat failure!");
        return -1;
    }

    if (_EbrIsDir(map)) {
        memset(ret, 0, sizeof(struct _stat64i32));
        ret->st_size = 0;
        ret->st_mode = 0x1B6 | 0040000;
        return 0;
    }

    return _wstat64i32(map, ret);
}