static void DocumentMgr_Destructor(DocumentMgr *This)
{
    ITfThreadMgr *tm;
    TRACE("destroying %p\n", This);

    TF_GetThreadMgr(&tm);
    ThreadMgr_OnDocumentMgrDestruction(tm, &This->ITfDocumentMgr_iface);

    if (This->contextStack[0])
        ITfContext_Release(This->contextStack[0]);
    if (This->contextStack[1])
        ITfContext_Release(This->contextStack[1]);
    CompartmentMgr_Destructor(This->CompartmentMgr);
    HeapFree(GetProcessHeap(),0,This);
}