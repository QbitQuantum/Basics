void Win32LockedPageAllocator::FreeLocked(void* addr, size_t len)
{
    len = align_up(len, page_size);
    memory_cleanse(addr, len);
    VirtualUnlock(const_cast<void*>(addr), len);
}