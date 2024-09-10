bool MemoryPageLocker::Unlock(const void* addr, size_t len)
{
#ifdef WIN32
    return VirtualUnlock(const_cast<void*>(addr), len) != 0;
#else
    return munlock(addr, len) == 0;
#endif
}