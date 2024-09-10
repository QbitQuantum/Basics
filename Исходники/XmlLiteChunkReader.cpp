int _tmain(int argc, WCHAR* argv[])
{
    HRESULT hr;
    CComPtr<IStream> pFileStream;
    CComPtr<IXmlReader> pReader;
    XmlNodeType nodetype;

    if (argc != 2)
    {
        wprintf(L"Usage: XmlLiteChunkReader.exe name-of-input-file\n");
        return 0;
    }
    
    //Open read-only input stream
    if (FAILED(hr = FileStream::OpenFile(argv[1], &pFileStream, FALSE)))
    {
        wprintf(L"Error creating file   reader, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL)))
    {
        wprintf(L"Error creating xml reader, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pReader->SetInput(pFileStream)))
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
        case XmlNodeType_Element:
            if (FAILED(hr = WriteAttributes(pReader)))
            {
                wprintf(L"Error, Method: WriteAttributes, error is %08.8lx", hr);
                return -1;
            }
            break;
        case XmlNodeType_Text:
        case XmlNodeType_Whitespace:
            const UINT buffSize = 24;
            WCHAR buff[buffSize];
            UINT charsRead;

            while (TRUE)
            {
                hr = pReader->ReadValueChunk(buff, buffSize - 1, &charsRead);
                if (S_FALSE == hr || 0 == charsRead)
                    break;
                if (S_OK != hr)
                {
                    wprintf(L"\nXmlLite Error: %08.8lx\n", hr);
                    return -1;
                }
                buff[charsRead] = L'\0';
                dotWhiteSpace(buff, charsRead);
                wprintf(L"element chunk size:%d >%s<\n", charsRead, buff);
            }
            break;
        }
    }
    wprintf(L"\n");
    return 0;
}