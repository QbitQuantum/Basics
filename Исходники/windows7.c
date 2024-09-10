int
freeWriteable(void* address, size_t sz)
{
    // MEM_DECOMMIT = 0x4000
    res = VirtualFreeEX(
        0, address, page_aligned(sz), MEM_DECOMMIT
    );
    return res;
}