int munlock(const void* addr, size_t len)
{
    if (VirtualUnlock((LPVOID)addr, len) != FALSE)
    {
        errno = 0;
        return 0;
    }

    errno = last_error(EPERM);
    return -1;
}