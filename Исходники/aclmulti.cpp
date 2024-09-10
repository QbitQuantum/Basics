HRESULT STDMETHODCALLTYPE CACLMulti::Remove(IUnknown *punk)
{
    int                                     i;

    TRACE("(%p, %p)\n", this, punk);
    for (i = 0; i < fObjectCount; i++)
        if (fObjects[i].punk == punk)
        {
            release_obj(&fObjects[i]);
            MoveMemory(&fObjects[i], &fObjects[i + 1], (fObjectCount - i - 1) * sizeof(ACLMultiSublist));
            fObjectCount--;
            fObjects = static_cast<ACLMultiSublist *>(
                CoTaskMemRealloc(fObjects, sizeof(fObjects[0]) * fObjectCount));
            return S_OK;
        }

    return E_FAIL;
}