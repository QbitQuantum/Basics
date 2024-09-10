void* DefaultAlloc::_ReAllocate(LPVOID lpData, size_t dwSize)
{
    return (!lpData) ? _aligned_malloc(dwSize, 16) : _aligned_realloc(lpData, dwSize, 16);
}