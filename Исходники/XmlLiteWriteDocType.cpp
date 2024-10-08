int _tmain(int argc, _TCHAR* argv[])
{
    HRESULT hr;
    CComPtr<IStream> pOutFileStream;
    CComPtr<IXmlWriter> pWriter;

    if (argc != 2)
    {
        wprintf(L"Usage: XmlLiteWriteDocType.exe name-of-output-file\n");
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

    if (FAILED(hr = pWriter->SetOutput(pOutFileStream)))
    {
        wprintf(L"Error, Method: SetOutput, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->SetProperty(XmlWriterProperty_Indent, TRUE)))
    {
        wprintf(L"Error, Method: SetProperty XmlWriterProperty_Indent, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartDocument(XmlStandalone_Omit)))
    {
        wprintf(L"Error, Method: WriteStartDocument, error is %08.8lx", hr);
        return -1;
    }

    const WCHAR * name = L"Employees";
    const WCHAR * pubid = NULL;
    const WCHAR * sysid = NULL;
    const WCHAR * subset =
    L"<!ELEMENT Employees (Employee)+>\n"
    L"<!ELEMENT Employee EMPTY>\n"
    L"<!ATTLIST Employee firstname CDATA #REQUIRED>\n"
    L"<!ENTITY Company 'Microsoft'>\n";

    if (FAILED(hr = pWriter->WriteDocType(name, pubid, sysid, subset)))
    {
        wprintf(L"Error, Method: WriteDocType, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteProcessingInstruction(L"xml-stylesheet",
        L"href=\"mystyle.css\" title=\"Compact\" type=\"text/css\"")))
    {
        wprintf(L"Error, Method: WriteProcessingInstruction, error is %08.8lx", hr);
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
    if (FAILED(hr = pWriter->WriteString(L"Markup is <escaped> for this string")))
    {
        wprintf(L"Error, Method: WriteString, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"anotherChild", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteString(L"some text")))
    {
        wprintf(L"Error, Method: WriteString, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteCData(L"This is CDATA text.")))
    {
        wprintf(L"Error, Method: WriteCData, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"containsCharacterEntity", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteCharEntity(L'a')))
    {
        wprintf(L"Error, Method: WriteCharEntity, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"containsChars", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteChars(L"abcdefghijklm", 5)))
    {
        wprintf(L"Error, Method: WriteChars, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"containsEntity", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteEntityRef(L"myEntity")))
    {
        wprintf(L"Error, Method: WriteEntityRef, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteEndElement()))
    {
        wprintf(L"Error, Method: WriteEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"containsName", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteName(L"myName")))
    {
        wprintf(L"Error, Method: WriteName, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteEndElement()))
    {
        wprintf(L"Error, Method: WriteEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteStartElement(NULL, L"containsNmToken", NULL)))
    {
        wprintf(L"Error, Method: WriteStartElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteNmToken(L"myNmToken")))
    {
        wprintf(L"Error, Method: WriteNmToken, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteEndElement()))
    {
        wprintf(L"Error, Method: WriteEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteComment(L"This is a comment")))
    {
        wprintf(L"Error, Method: WriteComment, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteRaw(L"<elementWrittenRaw/>")))
    {
        wprintf(L"Error, Method: WriteRaw, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteRawChars(L"<rawCharacters/>", 16)))
    {
        wprintf(L"Error, Method: WriteRawChars, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pWriter->WriteElementString(NULL, L"myElement", NULL, L"myValue")))
    {
        wprintf(L"Error, Method: WriteElementString, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteFullEndElement()))
    {
        wprintf(L"Error, Method: WriteFullEndElement, error is %08.8lx", hr);
        return -1;
    }
    if (FAILED(hr = pWriter->WriteWhitespace(L"\n")))
    {
        wprintf(L"Error, Method: WriteWhitespace, error is %08.8lx", hr);
        return -1;
    }

    // WriteEndDocument closes any open elements or attributes and reinitializes
    // the writer so that a new document can be written.
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