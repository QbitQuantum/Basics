int _tmain(int argc, WCHAR* argv[])
{
    HRESULT hr;
    CComPtr<IStream> pOutFileStream;
    CComPtr<IXmlWriter> pWriter;
    CComPtr<IXmlWriterOutput> pWriterOutput;

    if (argc != 2)
    {
        wprintf(L"Usage: XmlLiteWriteWithEncoding.exe name-of-output-file\n");
        return 0;
    }

    //Open writeable output stream
    if (FAILED(hr = FileStream::OpenFile(argv[1], &pOutFileStream, TRUE)))
    {
        wprintf(L"Error creating file writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlWriter(__uuidof(IXmlWriter), (void**) &pWriter, NULL)))
    {
        wprintf(L"Error creating xml writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlWriterOutputWithEncodingName(pOutFileStream, NULL, L"utf-16",
        &pWriterOutput)))
    {
        wprintf(L"Error creating xml reader with encoding code page, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->SetOutput(pWriterOutput)))
    {
        wprintf(L"Error setting output for writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->SetProperty(XmlWriterProperty_Indent, TRUE)))
    {
        wprintf(L"Error setting indent property in writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartDocument(XmlStandalone_Omit)))
    {
        wprintf(L"Error, Method: WriteStartDocument, error is %08.8lx", hr);
        return -1;
    }
    
    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"root", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"sub", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteAttributeString(NULL, L"myAttr", NULL, L"1234")))
    {
        wprintf(L"Error, Method: WriteAttributeString, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteString(L"This is a string")))
    {
        wprintf(L"Error, Method: WriteString, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteEndDocument()))
    {
        wprintf(L"Error, Method: WriteEndDocument, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->Flush()))
    {
        wprintf(L"Error, Method: Flush, error is %08.8lx", hr);
        return -1;
    }

    return 0;
}