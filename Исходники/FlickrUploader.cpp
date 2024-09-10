//
// Parse the XML data returned from Flickr, if error happens, return the error message.
//
std::wstring FlickrUploader::GetXmlElementValueByName(const std::wstring& xmlContent, const std::wstring& elementName, bool* errorFound)
{
    *errorFound = false;
    HGLOBAL memory;
    // Allocate a global memory for the xml content
    memory = ::GlobalAlloc(GMEM_MOVEABLE, xmlContent.length() * sizeof(wchar_t));
    void* data = ::GlobalLock(memory);
    // Fill memory
    ::memcpy(data, xmlContent.c_str(), xmlContent.length() * sizeof(wchar_t));
    ::GlobalUnlock(memory);

    // Create stream based on the allocated memory
    ComPtr<IStream> stream;
    HRESULT hr = ::CreateStreamOnHGlobal(memory, FALSE, &stream);

    // Create Xml Reader Input based on the stream
    ComPtr<IXmlReaderInput> readerInput;
    if (SUCCEEDED(hr))
    {
        hr = CreateXmlReaderInputWithEncodingCodePage(stream, 0, CP_WINNEUTRAL, false, 0, &readerInput);
    }
    // Create Xml Reader
    ComPtr<IXmlReader> reader;
    if (SUCCEEDED(hr))
    {
        hr = CreateXmlReader(IID_IXmlReader, reinterpret_cast<void**>(&reader), 0);
    }
    if (SUCCEEDED(hr))
    {
        hr = reader->SetInput(readerInput);
    }
    std::wstring resultString;
    if (SUCCEEDED(hr))
    {
        XmlNodeType nodeType;
        // Parse xml file
        bool found = false;
        while (S_OK == (hr = reader->Read(&nodeType)) && !found) 
        {
            switch (nodeType)
            {
            case XmlNodeType_Element:
                {
                    const wchar_t* name;
                    if (FAILED(hr = reader->GetQualifiedName(&name, nullptr)))
                    {
                        *errorFound = true;
                        resultString = L"Parsing content from Flickr failed unexpectedly.";
                        break;
                    }

                    if (wcscmp(name, elementName.c_str()) == 0)
                    {
                        // Read next node
                        reader->Read(&nodeType);
                        unsigned int len = 0;
                        const wchar_t* element = nullptr;
                        if (SUCCEEDED(reader->GetValue(&element, &len)))
                        {
                            // Find the value
                            resultString = element;
                            found = true;
                        }
                    }
                    else if (wcscmp(name, L"err") == 0) // We got an error code
                    {
                        *errorFound = true;
                    }
                    break;
                }
            case XmlNodeType_Attribute:
                {
                    if (*errorFound)
                    {
                        const wchar_t* name;
                        if (FAILED(hr = reader->GetQualifiedName(&name, nullptr)))
                        {
                            *errorFound = true;
                            resultString = L"Parsing content from Flickr failed unexpectedly.";
                            break;
                        }

                        if (wcscmp(name, L"msg") == 0)
                        {
                            unsigned int len = 0;
                            const wchar_t* element = nullptr;
                            if (SUCCEEDED(reader->GetValue(&element, &len)))
                            {
                                // Get the error message
                                resultString = element;
                                found = true;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    return resultString;
}