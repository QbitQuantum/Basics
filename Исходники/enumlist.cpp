ULONG
WINAPI CEnumIDList::Release()
{
    LPENUMLIST pDelete;
    ULONG refCount = InterlockedDecrement(&ref);

    if (!refCount) 
    {
        while (mpFirst)
        {
            pDelete = mpFirst;
            mpFirst = pDelete->pNext;
            SHFree(pDelete->pidl);
            SHFree(pDelete);
        }
        delete this;
    }
    return refCount;
}