static HRESULT CALLBACK CB_Save(DPASTREAMINFO *pInfo, IStream *pStm, LPVOID lp)
{
    HRESULT hRes;

    ok(lp == (LPVOID)0xdeadbeef, "lp=%p\n", lp);
    hRes = IStream_Write(pStm, &pInfo->iPos, sizeof(INT), NULL);
    expect(S_OK, hRes);
    hRes = IStream_Write(pStm, &pInfo->pvItem, sizeof(PVOID), NULL);
    expect(S_OK, hRes);
    return S_OK;
}