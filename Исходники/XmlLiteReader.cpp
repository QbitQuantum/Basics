int _tmain(int argc, WCHAR* argv[])
{
    HRESULT hr;
    CComPtr<IStream> pFileStream;
    CComPtr<IXmlReader> pReader;
    XmlNodeType nodeType;
    const WCHAR* pwszPrefix;
    const WCHAR* pwszLocalName;
    const WCHAR* pwszValue;
    UINT cwchPrefix;

    if (argc != 2)
    {
        wprintf(L"Usage: XmlLiteReader.exe name-of-input-file\n");
        return 0;
    }

    //Open read-only input stream
    if (FAILED(hr = SHCreateStreamOnFile(argv[1], STGM_READ, &pFileStream)))
    {
        wprintf(L"Error creating file reader, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL)))
    {
        wprintf(L"Error creating xml reader, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit)))
    {
        wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pReader->SetInput(pFileStream)))
    {
        wprintf(L"Error setting input for reader, error is %08.8lx", hr);
        return -1;
    }

    //read until there are no more nodes
    while (S_OK == (hr = pReader->Read(&nodeType)))
    {
        switch (nodeType)
        {
        case XmlNodeType_XmlDeclaration:
            wprintf(L"XmlDeclaration\n");
            if (FAILED(hr = WriteAttributes(pReader)))
            {
                wprintf(L"Error writing attributes, error is %08.8lx", hr);
                return -1;
            }
            break;
        case XmlNodeType_Element:
            if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
            {
                wprintf(L"Error getting prefix, error is %08.8lx", hr);
                return -1;
            }
            if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
            {
                wprintf(L"Error getting local name, error is %08.8lx", hr);
                return -1;
            }
            if (cwchPrefix > 0)
                wprintf(L"Element: %s:%s\n", pwszPrefix, pwszLocalName);
            else
                wprintf(L"Element: %s\n", pwszLocalName);

            if (FAILED(hr = WriteAttributes(pReader)))
            {
                wprintf(L"Error writing attributes, error is %08.8lx", hr);
                return -1;
            }

            if (pReader->IsEmptyElement() )
                wprintf(L" (empty)");
            break;
        case XmlNodeType_EndElement:
            if (FAILED(hr = pReader->GetPrefix(&pwszPrefix, &cwchPrefix)))
            {
                wprintf(L"Error getting prefix, error is %08.8lx", hr);
                return -1;
            }
            if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
            {
                wprintf(L"Error getting local name, error is %08.8lx", hr);
                return -1;
            }
            if (cwchPrefix > 0)
                wprintf(L"End Element: %s:%s\n", pwszPrefix, pwszLocalName);
            else
                wprintf(L"End Element: %s\n", pwszLocalName);
            break;
        case XmlNodeType_Text:
        case XmlNodeType_Whitespace:
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error getting value, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"Text: >%s<\n", pwszValue);
            break;
        case XmlNodeType_CDATA:
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error getting value, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"CDATA: %s\n", pwszValue);
            break;
        case XmlNodeType_ProcessingInstruction:
            if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL)))
            {
                wprintf(L"Error getting name, error is %08.8lx", hr);
                return -1;
            }
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error getting value, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"Processing Instruction name:%S value:%S\n", pwszLocalName, pwszValue);
            break;
        case XmlNodeType_Comment:
            if (FAILED(hr = pReader->GetValue(&pwszValue, NULL)))
            {
                wprintf(L"Error getting value, error is %08.8lx", hr);
                return -1;
            }
            wprintf(L"Comment: %s\n", pwszValue);
            break;
        case XmlNodeType_DocumentType:
            wprintf(L"DOCTYPE is not printed\n");
            break;
        }
    }

    return 0;
}