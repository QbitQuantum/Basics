size_t xrMemory::mem_usage()
{
    _HEAPINFO hinfo = {};
    int status;
    size_t bytesUsed = 0;
    while ((status = _heapwalk(&hinfo)) == _HEAPOK)
    {
        if (hinfo._useflag == _USEDENTRY)
            bytesUsed += hinfo._size;
    }
    switch (status)
    {
    case _HEAPEMPTY:
        break;
    case _HEAPEND:
        break;
    case _HEAPBADPTR:
        FATAL("bad pointer to heap");
        break;
    case _HEAPBADBEGIN:
        FATAL("bad start of heap");
        break;
    case _HEAPBADNODE:
        FATAL("bad node in heap");
        break;
    }
    return bytesUsed;
}