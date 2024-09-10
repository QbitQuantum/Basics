void addRefCount()
{
    if (++g_refCount == 1)
        CoInitialize(NULL);
}