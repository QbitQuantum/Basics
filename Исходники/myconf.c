int _qdbm_msync(const void *start, size_t length, int flags) {
    if(!FlushViewOfFile(start, length)) return -1;
    return 0;
}