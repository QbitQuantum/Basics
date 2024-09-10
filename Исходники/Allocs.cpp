void allocCoTaskMem(bool bFree)
{
    void* leaked = CoTaskMemAlloc(7);
    if (bFree)
    {
        CoTaskMemFree(leaked);
    }
    void* leaked2 = CoTaskMemAlloc(7);
    void* realloced = CoTaskMemRealloc(leaked2, 29);
    if (bFree)
    {
        CoTaskMemFree(realloced);
    }
}