static void test_MFCreateMediaType(void)
{
    HRESULT hr;
    IMFMediaType *mediatype;

    hr = MFStartup(MAKELONG( MF_API_VERSION, 0xdead ), MFSTARTUP_FULL);
    ok(hr == MF_E_BAD_STARTUP_VERSION, "got 0x%08x\n", hr);

    hr = MFStartup(MF_VERSION, MFSTARTUP_FULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

if(0)
{
    /* Crash on Windows Vista/7 */
    hr = MFCreateMediaType(NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
}

    hr = MFCreateMediaType(&mediatype);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IMFMediaType_SetGUID(mediatype, &MF_MT_MAJOR_TYPE, &MFMediaType_Video);
    todo_wine ok(hr == S_OK, "got 0x%08x\n", hr);

    IMFMediaType_Release(mediatype);

    MFShutdown();
}