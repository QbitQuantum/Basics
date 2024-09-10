static void test_IMalloc(void)
{
    LPVOID lpMem;
    ULONG ulRef;
    int iRet;
    HRESULT hRet;
    LPMALLOC lpMalloc;
    LPVOID lpVoid;

    pMAPIGetDefaultMalloc = (void*)GetProcAddress(hMapi32,
                            "MAPIGetDefaultMalloc@0");
    if (!pMAPIGetDefaultMalloc)
    {
        win_skip("MAPIGetDefaultMalloc is not available\n");
        return;
    }

    lpMalloc = pMAPIGetDefaultMalloc();
    ok(lpMalloc != NULL, "Expected MAPIGetDefaultMalloc to return non-NULL\n");
    if (!lpMalloc)
    {
        skip("MAPIGetDefaultMalloc failed\n");
        return;
    }

    lpVoid = NULL;
    hRet = IMalloc_QueryInterface(lpMalloc, &IID_IUnknown, &lpVoid);
    ok (hRet == S_OK && lpVoid != NULL,
        "IID_IUnknown: expected S_OK, non-null, got 0x%08x, %p\n",
        hRet, lpVoid);

    lpVoid = NULL;
    hRet = IMalloc_QueryInterface(lpMalloc, &IID_IMalloc, &lpVoid);
    ok (hRet == S_OK && lpVoid != NULL,
        "IID_IIMalloc: expected S_OK, non-null, got 0x%08x, %p\n",
        hRet, lpVoid);

    /* Prove that native mapi uses LocalAlloc/LocalFree */
    lpMem = IMalloc_Alloc(lpMalloc, 61);
    ok (lpMem && IMalloc_GetSize(lpMalloc, lpMem) == LocalSize(lpMem),
        "Expected non-null, same size, got %p, %s size\n", lpMem,
        lpMem ? "different" : "same");

    iRet = IMalloc_DidAlloc(lpMalloc, lpMem);
    ok (iRet == -1, "DidAlloc, expected -1. got %d\n", iRet);

    IMalloc_HeapMinimize(lpMalloc);

    LocalFree(lpMem);

    ulRef = IMalloc_AddRef(lpMalloc);
    ok (ulRef == 1u, "AddRef expected 1, returned %d\n", ulRef);

    ulRef = IMalloc_Release(lpMalloc);
    ok (ulRef == 1u, "AddRef expected 1, returned %d\n", ulRef);

    IMalloc_Release(lpMalloc);
}