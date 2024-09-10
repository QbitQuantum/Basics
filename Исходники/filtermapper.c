static void test_parse_filter_data(void)
{
    static const BYTE data_block[] = {
  0x02,0x00,0x00,0x00,0xff,0xff,0x5f,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x70,0x69,0x33,
  0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x30,0x74,0x79,0x33,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x31,0x70,0x69,0x33,
  0x08,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x30,0x74,0x79,0x33,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x70,0x00,0x00,0x00,0x76,0x69,0x64,0x73,
  0x00,0x00,0x10,0x00,0x80,0x00,0x00,0xaa,0x00,0x38,0x9b,0x71,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    BYTE *prgbRegFilter2 = NULL;
    REGFILTER2 *pRegFilter = NULL;
    IFilterMapper2 *pMapper = NULL;
    SAFEARRAYBOUND saBound;
    SAFEARRAY *psa = NULL;
    LPBYTE pbSAData = NULL;
    HRESULT hr;

    IAMFilterData *pData = NULL;

    hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC_SERVER,
            &IID_IFilterMapper2, (LPVOID*)&pMapper);
    ok((hr == S_OK || broken(hr != S_OK)), "CoCreateInstance failed with %x\n", hr);
    if (FAILED(hr)) goto out;

    hr = IFilterMapper2_QueryInterface(pMapper, &IID_IAMFilterData, (LPVOID*)&pData);
    ok((hr == S_OK || broken(hr != S_OK)), "Unable to find IID_IAMFilterData interface\n");
    if (FAILED(hr)) goto out;

    saBound.lLbound = 0;
    saBound.cElements = sizeof(data_block);
    psa = SafeArrayCreate(VT_UI1, 1, &saBound);
    ok(psa != NULL, "Unable to create safe array\n");
    if (!psa) goto out;
    hr = SafeArrayAccessData(psa, (LPVOID *)&pbSAData);
    ok(hr == S_OK, "Unable to access array data\n");
    if (FAILED(hr)) goto out;
    memcpy(pbSAData, data_block, sizeof(data_block));

    hr = IAMFilterData_ParseFilterData(pData, pbSAData, sizeof(data_block), &prgbRegFilter2);
    /* We cannot do anything here.  prgbRegFilter2 is very unstable */
    /* Pre Vista, this is a stack pointer so anything that changes the stack invalidats it */
    /* Post Vista, it is a static pointer in the data section of the module */
    pRegFilter =((REGFILTER2**)prgbRegFilter2)[0];
    ok (hr==S_OK,"Failed to Parse filter Data\n");

    ok(IsBadReadPtr(prgbRegFilter2,sizeof(REGFILTER2*))==0,"Bad read pointer returned\n");
    ok(IsBadReadPtr(pRegFilter,sizeof(REGFILTER2))==0,"Bad read pointer for FilterData\n");
    ok(pRegFilter->dwMerit == 0x5fffff,"Incorrect merit returned\n");

out:
    if (pRegFilter)
        CoTaskMemFree(pRegFilter);
    if (psa)
    {
        SafeArrayUnaccessData(psa);
        SafeArrayDestroy(psa);
    }
    if (pData)
        IAMFilterData_Release(pData);
    if (pMapper)
        IFilterMapper2_Release(pMapper);
}