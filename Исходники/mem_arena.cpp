void *MemArena::CreateView(s64 offset, size_t size, void *base)
{
#ifdef _WIN32
    size = roundup(size);
    void *ptr = MapViewOfFileEx(hMemoryMapping, FILE_MAP_ALL_ACCESS, 0, (DWORD)((u64)offset), size, base);
    return ptr;
#else
    void *retval = mmap(base, size, PROT_READ | PROT_WRITE, MAP_SHARED |
        // Do not sync memory to underlying file. Linux has this by default.
#ifdef __FreeBSD__
        MAP_NOSYNC |
#endif
        ((base == nullptr) ? 0 : MAP_FIXED), fd, offset);

    if (retval == MAP_FAILED)
    {
        LOG_ERROR(Common_Memory, "mmap failed");
        return nullptr;
    }
    return retval;
#endif
}