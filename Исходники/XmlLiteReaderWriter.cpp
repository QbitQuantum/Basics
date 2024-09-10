int _tmain(int argc, WCHAR* argv[])
{
    HRESULT hr;
    CComPtr<IStream> pFileStream;
    CComPtr<IStream> pOutFileStream;
    CComPtr<IXmlReader> pReader;
    CComPtr<IXmlWriter> pWriter;
    CComPtr<IXmlReaderInput> pReaderInput;
    CComPtr<IXmlWriterOutput> pWriterOutput;

    if (argc != 3)
    {
        wprintf( L"Usage: XmlReaderWriter.exe name-of-input-file name-of-output-file\n");
        return 0;
    }

    //Open read-only input stream
    if (FAILED(hr = FileStream::OpenFile(argv[1], &pFileStream, FALSE)))
    {
        wprintf(L"Error creating file reader, error is %08.8lx", hr);
        return -1;
    }

    //Open writeable output stream
    if (FAILED(hr = FileStream::OpenFile(argv[2], &pOutFileStream, TRUE)))
    {
        wprintf(L"Error creating file writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL)))
    {
        wprintf(L"Error creating xml reader, error is %08.8lx", hr);
        return -1;
    }

    pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);

    if (FAILED(hr = CreateXmlReaderInputWithEncodingCodePage(pFileStream, NULL, 65001, FALSE,
                                                             L"c:\temp", &pReaderInput)))
    {
        wprintf(L"Error creating xml reader with encoding code page, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlWriter(__uuidof(IXmlWriter),(void**) &pWriter, NULL)))
    {
        wprintf(L"Error creating xml writer, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = CreateXmlWriterOutputWithEncodingCodePage(pOutFileStream, NULL, 65001,
                                                              &pWriterOutput)))
    {
        wprintf(L"Error creating xml reader with encoding code page, error is %08.8lx", hr);
        return -1;
    }

    if (FAILED(hr = pReader->SetInput(pReaderInput)))
    {
        wprintf(L"Error setting input for reader, error is %08.8lx", hr);
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

    XmlNodeType nodeType;
    const WCHAR* pQName;
    const WCHAR* pValue;
    double originalPrice = 0.0;
    double newPrice = 0.0;
    WCHAR priceString[100];
    bool inPrice = FALSE;

    /*
     * This quick start reads an XML of the form
     * <books>
     *   <book name="name of book1">
     *    <price>price-of-book1</price>
     *   </book>
     *   <book name="name of book2">
     *    <price>price-of-book2</price>
     *   </book>
     *  </books>
     *
     * and applies a 25% discount to the price of the book. It also adds originalPrice and discount
     * as two attributes to the element price. If the price is empty or an empty element, it does
     * not make any changes. So the transformed XML will be:
     *
     * <books>
     *   <book name="name of book1">
     *    <price originalPrice="price-of-book1" discount="25%">
     *           discounted-price-of-book1
     *       </price>
     *   </book>
     *   <book name="name of book2">
     *    <price originalPrice="price-of-book2" discount="25%">
     *           discounted-price-of-book2
     *       </price>
     *   </book>
     *  </books>
     *
     */

    //read until there are no more nodes
    while (S_OK == (hr = pReader->Read(&nodeType)))
    {

        // WriteNode will move the reader to the next node, so inside the While Read loop, it is
        // essential that we use WriteNodeShallow, which will not move the reader. 
        // If not, a node will be skipped every time you use WriteNode in the while loop.

        switch (nodeType)
        {
        case XmlNodeType_Element:
            {
                if (pReader->IsEmptyElement())
                {
                    if (FAILED(hr = pWriter->WriteNodeShallow(pReader, FALSE)))
                    {
                        wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr);
                        return -1;
                    }
                }
                else
                {
                    // if you are not interested in the length it may be faster to use 
                    // NULL for the length parameter
                    if (FAILED(hr = pReader->GetQualifiedName(&pQName, NULL)))
                    {
                        wprintf(L"Error reading element name, error is %08.8lx", hr);
                        return -1;
                    }
                    
                    //if the element is price, then discount price by 25%   
                    if (wcscmp(pQName, L"price") == 0)
                    {
                        inPrice = TRUE;
                        if (FAILED(hr = pWriter->WriteNodeShallow(pReader, FALSE)))
                        {
                            wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr);
                            return -1;
                        }


                    }
                    else
                    {
                        inPrice = FALSE;
                        if (FAILED(hr = pWriter->WriteNodeShallow(pReader, FALSE)))
                        {
                            wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr);
                            return -1;
                        }

                    }
                }
            }
            break;
        case XmlNodeType_Text:
            if (inPrice == TRUE)
            {
                if (FAILED(hr = pReader->GetValue(&pValue, NULL)))
                {
                    wprintf(L"Error reading value, error is %08.8lx", hr);
                    return -1;
                }
                
                //apply discount to the node
                originalPrice = _wtof(pValue);
                newPrice = originalPrice * 0.75;

                if (FAILED(hr = StringCbPrintfW(priceString, sizeof (priceString), L"%f",
                                                newPrice)))
                {
                    wprintf(L"Error using StringCchPrintfW, error is %08.8lx", hr);
                    return -1;
                }

                //write attributes if any
                if (FAILED(hr = pWriter->WriteAttributeString(NULL, L"originalPrice", NULL,
                                                              pValue)))
                {
                    wprintf(L"Error writing WriteAttributeString, error is %08.8lx", hr);
                    return -1;
                }

                if (FAILED(hr = pWriter->WriteAttributeString(NULL, L"discount", NULL, L"25%")))
                {
                    wprintf(L"Error writing WriteAttributeString, error is %08.8lx", hr);
                    return -1;
                }
                if (FAILED(hr = pWriter->WriteString(priceString)))
                {
                    wprintf(L"Error writing WriteString, error is %08.8lx", hr);
                    return -1;
                }
                inPrice = FALSE;
            }
            else
            {
                if (FAILED(hr = pWriter->WriteNodeShallow(pReader, FALSE)))
                {
                    wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr);
                    return -1;
                }
            }

            break;
        case XmlNodeType_EndElement:
            if (FAILED(hr = pReader->GetQualifiedName(&pQName, NULL)))
            {
                wprintf(L"Error reading element name, error is %08.8lx", hr);
                return -1;
            }
            
            if (wcscmp(pQName, L"price") == 0)  //if the end element is price, then reset inPrice
                inPrice = FALSE;
            
            if (FAILED(hr = pWriter->WriteFullEndElement()))
            {
                wprintf(L"Error writing WriteFullEndElement, error is %08.8lx", hr);
                return -1;
            }
            break;
        default:
            {
                if (FAILED(hr = pWriter->WriteNodeShallow(pReader, FALSE)))
                {
                    wprintf(L"Error writing WriteNodeShallow, error is %08.8lx", hr);
                    return -1;
                }
            }
            break;
        }

    }
    return 0;
}