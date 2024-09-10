int _tmain(int argc, _TCHAR* argv[])
{
    HRESULT hr;
    CComPtr<IStream> pOutFileStream;
    CComPtr<IXmlWriter> pWriter;

    if (argc != 2)
    {
        printf("Usage: XmlLiteNamespaceWriter4.exe name-of-output-file\n");
        return 0;
    }

    //Open writeable output stream
    if (FAILED(hr = FileStream::OpenFile(argv[1], &pOutFileStream, TRUE)))
    {
        wprintf(L"Error creating file writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlWriter(__uuidof(IXmlWriter),(void**) &pWriter, NULL)))
    {
        wprintf(L"Error creating xml writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->SetOutput(pOutFileStream)))
    {
        wprintf(L"Error setting output for writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->SetProperty(XmlWriterProperty_Indent, TRUE)))
    {
        wprintf(L"Error, Method: SetProperty, XmlWriterProperty_Indent, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartDocument(XmlStandalone_Omit)))
    {
        wprintf(L"Error, Method: WriteStartDocument, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(L"ab", L"parent", L"urn:abc")))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteStartElement(L"ab", L"child", L"urn:abc")))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteStartElement(L"xy", L"grandchild", L"urn:xyz")))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteStartElement(L"ab", L"grandchild2", L"urn:abc")))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }

    return 0;
}