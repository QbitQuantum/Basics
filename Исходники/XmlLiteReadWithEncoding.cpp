int _tmain(int argc, WCHAR* argv[])
{
    HRESULT hr;
    CComPtr<IStream> pFileStream;
    CComPtr<IXmlReader> pReader;
    CComPtr<IXmlReaderInput> pReaderInput;
    XmlNodeType nodetype;
    const WCHAR* pwszPrefix;
    const WCHAR* pwszLocalName;
    const WCHAR* pwszValue;
    UINT cwchPrefix;

    if (argc != 2)
    {
        wprintf(L"Usage: XmlLiteReadWithEncoding.exe name-of-input-file\n");
        return 0;
    }

    // Open read-only input stream
    if (FAILED(hr = FileStream::OpenFile(argv[1], &pFileStream, FALSE)))
    {
        wprintf(L"Error creating file reader, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader),(void**) &pReader, NULL)))
    {
        wprintf(L"Error creating xml reader, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlReaderInputWithEncodingName(pFileStream, NULL, L"utf-16", FALSE,
        L"c:\temp", &pReaderInput)))
    {
        wprintf(L"Error creating xml reader with encoding code page, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pReader->SetInput(pReaderInput)))
    {
        wprintf(L"Error setting input for reader, error is %08.8lx", hr);
        return -1;
    }

    while (TRUE)
    {
        hr = pReader->Read(&nodetype);
        if (S_FALSE == hr)
            break;
        if (S_OK != hr)
        {
            wprintf(L"\nXmlLite Error: %08.8lx\n", hr);
            return -1;
        }
        switch (nodetype)
        {
        case XmlNodeType_XmlDeclaration:
            wprintf(L"<?xml ");
            if (FAILED(hr = WriteAttributes(pReader)))
            {
                wprintf(L"Error, Method: WriteAttributes, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"?>\r\n");
            break;
        case XmlNodeType_Element:
            if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
            {
                wprintf(L"Error, Method: GetPrefix, error is %08.8lx", hr);
                return -1;
            }
            if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
            {
                wprintf(L"Error, Method: GetLocalName, error is %08.8lx", hr);
                return -1;
            }
            if (cwchPrefix > 0)
                wprintf(L"<%s:%s ", pwszPrefix, pwszLocalName);
            else
                wprintf(L"<%s ", pwszLocalName);

            if (FAILED(hr = WriteAttributes(pReader)))
            {
                wprintf(L"Error, Method: WriteAttributes, error is %08.8lx", hr);
                return -1;
            }

            if (pReader->IsEmptyElement() )
                wprintf(L"/>");
            else
                wprintf(L">");
            break;
        case XmlNodeType_EndElement:
            if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
            {
                wprintf(L"Error, Method: GetPrefix, error is %08.8lx", hr);
                return -1;
            }
            if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
            {
                wprintf(L"Error, Method: GetLocalName, error is %08.8lx", hr);
                return -1;
            }
            if (cwchPrefix > 0)
                wprintf(L"</%s:%s>", pwszPrefix, pwszLocalName);
            else
                wprintf(L"</%s>", pwszLocalName);
            break;
        case XmlNodeType_Text:
        case XmlNodeType_Whitespace:
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error, Method: GetValue, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"%s", pwszValue);
            break;
        case XmlNodeType_CDATA:
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error, Method: GetValue, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"<![CDATA[%s]]>", pwszValue);
            break;
        case XmlNodeType_ProcessingInstruction:
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error, Method: GetValue, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"<?%s?>", pwszValue);
            break;
        case XmlNodeType_Comment:
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error, Method: GetValue, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"<!--%s-->", pwszValue);
            break;
        case XmlNodeType_DocumentType:
            wprintf(L"<!-- DOCTYPE is not printed -->\r\n");
            break;
        }
    }
    wprintf(L"\n");
    return 0;
}