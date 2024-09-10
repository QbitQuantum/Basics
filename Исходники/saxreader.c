static void test_saxreader(void)
{
    HRESULT hr;
    ISAXXMLReader *reader = NULL;
    VARIANT var;
    ISAXContentHandler *lpContentHandler;
    ISAXErrorHandler *lpErrorHandler;
    SAFEARRAY *pSA;
    SAFEARRAYBOUND SADim[1];
    char *pSAData = NULL;
    IStream *iStream;
    ULARGE_INTEGER liSize;
    LARGE_INTEGER liPos;
    ULONG bytesWritten;
    HANDLE file;
    static const CHAR testXmlA[] = "test.xml";
    static const WCHAR testXmlW[] = {'t','e','s','t','.','x','m','l',0};
    IXMLDOMDocument *domDocument;
    BSTR bstrData;
    VARIANT_BOOL vBool;

    hr = CoCreateInstance(&CLSID_SAXXMLReader, NULL, CLSCTX_INPROC_SERVER,
            &IID_ISAXXMLReader, (LPVOID*)&reader);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = ISAXXMLReader_getContentHandler(reader, NULL);
    ok(hr == E_POINTER, "Expected E_POINTER, got %08x\n", hr);

    hr = ISAXXMLReader_getErrorHandler(reader, NULL);
    ok(hr == E_POINTER, "Expected E_POINTER, got %08x\n", hr);

    hr = ISAXXMLReader_getContentHandler(reader, &lpContentHandler);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(lpContentHandler == NULL, "Expected %p, got %p\n", NULL, lpContentHandler);

    hr = ISAXXMLReader_getErrorHandler(reader, &lpErrorHandler);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(lpErrorHandler == NULL, "Expected %p, got %p\n", NULL, lpErrorHandler);

    hr = ISAXXMLReader_putContentHandler(reader, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = ISAXXMLReader_putContentHandler(reader, &contentHandler);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = ISAXXMLReader_putErrorHandler(reader, &errorHandler);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = ISAXXMLReader_getContentHandler(reader, &lpContentHandler);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(lpContentHandler == &contentHandler, "Expected %p, got %p\n", &contentHandler, lpContentHandler);

    V_VT(&var) = VT_BSTR;
    V_BSTR(&var) = SysAllocString(szSimpleXML);

    expectCall = contentHandlerTest1;
    hr = ISAXXMLReader_parse(reader, var);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    test_expect_call(CH_ENDTEST);

    VariantClear(&var);

    SADim[0].lLbound= 0;
    SADim[0].cElements= sizeof(szTestXML)-1;
    pSA = SafeArrayCreate(VT_UI1, 1, SADim);
    SafeArrayAccessData(pSA, (void**)&pSAData);
    memcpy(pSAData, szTestXML, sizeof(szTestXML)-1);
    SafeArrayUnaccessData(pSA);
    V_VT(&var) = VT_ARRAY|VT_UI1;
    V_ARRAY(&var) = pSA;

    expectCall = contentHandlerTest1;
    hr = ISAXXMLReader_parse(reader, var);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    test_expect_call(CH_ENDTEST);

    SafeArrayDestroy(pSA);

    CreateStreamOnHGlobal(NULL, TRUE, &iStream);
    liSize.QuadPart = strlen(szTestXML);
    IStream_SetSize(iStream, liSize);
    IStream_Write(iStream, szTestXML, strlen(szTestXML), &bytesWritten);
    liPos.QuadPart = 0;
    IStream_Seek(iStream, liPos, STREAM_SEEK_SET, NULL);
    V_VT(&var) = VT_UNKNOWN|VT_DISPATCH;
    V_UNKNOWN(&var) = (IUnknown*)iStream;

    expectCall = contentHandlerTest1;
    hr = ISAXXMLReader_parse(reader, var);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    test_expect_call(CH_ENDTEST);

    IStream_Release(iStream);

    V_VT(&var) = VT_BSTR;
    V_BSTR(&var) = SysAllocString(szCarriageRetTest);

    expectCall = contentHandlerTest2;
    hr = ISAXXMLReader_parse(reader, var);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    test_expect_call(CH_ENDTEST);

    VariantClear(&var);

    file = CreateFileA(testXmlA, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    ok(file != INVALID_HANDLE_VALUE, "Could not create file: %u\n", GetLastError());
    WriteFile(file, szTestXML, sizeof(szTestXML)-1, &bytesWritten, NULL);
    CloseHandle(file);

    expectCall = contentHandlerTest1;
    hr = ISAXXMLReader_parseURL(reader, testXmlW);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    test_expect_call(CH_ENDTEST);

    DeleteFileA(testXmlA);

    hr = CoCreateInstance(&CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
            &IID_IXMLDOMDocument, (LPVOID*)&domDocument);
    if(FAILED(hr))
    {
        skip("Failed to create DOMDocument instance\n");
        return;
    }
    bstrData = SysAllocString(szSimpleXML);
    hr = IXMLDOMDocument_loadXML(domDocument, bstrData, &vBool);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    V_VT(&var) = VT_UNKNOWN;
    V_UNKNOWN(&var) = (IUnknown*)domDocument;

    expectCall = contentHandlerTest2;
    hr = ISAXXMLReader_parse(reader, var);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    test_expect_call(CH_ENDTEST);
    IXMLDOMDocument_Release(domDocument);

    ISAXXMLReader_Release(reader);
    SysFreeString(bstrData);
}