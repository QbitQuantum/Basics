size_t file_storage::file_size(int file_handle)
{
    if (file_handle == INVALID_HANDLE)
        return 0;

    // This is required because off_t is defined as long, which is 32 bits in
    // msvc and 64 bits in linux/osx, and stat contains off_t.
#ifdef _WIN32
#ifdef _WIN64
    struct _stat64 sbuf;
    if (_fstat64(file_handle, &sbuf) == FAIL)
        return 0;
#else
    struct _stat32 sbuf;
    if (_fstat32(file_handle, &sbuf) == FAIL)
        return 0;
#endif
#else
    // Limited to 32 bit files on 32 bit systems, see linux.die.net/man/2/open
    struct stat sbuf;
    if (fstat(file_handle, &sbuf) == FAIL)
        return 0;
#endif

    // Convert signed to unsigned size.
    BITCOIN_ASSERT_MSG(sbuf.st_size > 0, "File size cannot be 0 bytes.");
    return static_cast<size_t>(sbuf.st_size);
}