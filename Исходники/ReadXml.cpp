// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_XML_READER* xmlReader = NULL;
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create an XML reader
    hr = WsCreateReader(
        NULL,
        0, 
        &xmlReader, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    char* xml = 
    "<?xml version='1.0' encoding='UTF-8' standalone='yes'?>"
    "<Orders xmlns='http://example.com'>"
        "<!-- Order #1 -->"
        "<PurchaseOrder id='1'>"
            "<Quantity>42</Quantity>"
            "<ProductName>Toaster</ProductName>"
        "</PurchaseOrder>"
        "<!-- Order #2 -->"
        "<PurchaseOrder id='2'>"
            "<Quantity>5</Quantity>"
            "<ProductName><![CDATA[Block&Tackle]]></ProductName>"
        "</PurchaseOrder>"
    "</Orders>";
    BYTE* bytes = (BYTE*) xml;
    ULONG byteCount = (ULONG)strlen(xml);
    
    // Setup the source input
    WS_XML_READER_BUFFER_INPUT bufferInput;
    ZeroMemory(&bufferInput, sizeof(bufferInput));
    bufferInput.input.inputType = WS_XML_READER_INPUT_TYPE_BUFFER;
    bufferInput.encodedData = bytes;
    bufferInput.encodedDataSize = byteCount;
    
    // Setup the source encoding
    WS_XML_READER_TEXT_ENCODING textEncoding;
    ZeroMemory(&textEncoding, sizeof(textEncoding));
    textEncoding.encoding.encodingType = WS_XML_READER_ENCODING_TYPE_TEXT;
    textEncoding.charSet = WS_CHARSET_AUTO;
    
    // Setup the reader
    hr = WsSetInput(xmlReader, &textEncoding.encoding, &bufferInput.input, NULL, 0, error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    WS_CHARSET charSet;
    hr = WsGetReaderProperty(xmlReader, WS_XML_READER_PROPERTY_CHARSET, &charSet, sizeof(charSet), error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    switch (charSet)
    {
        case WS_CHARSET_UTF8:
            printf("charSet=utf-8\n");
            break;
        case WS_CHARSET_UTF16LE:
            printf("charSet=utf-16LE\n");
            break;
        case WS_CHARSET_UTF16BE:
            printf("charSet=utf-16BE\n");
            break;
        default:
            printf("<error: Unexpected charset>\n");
            hr = E_FAIL;
            goto Exit;
    }
    
    ULONG depth = 0;
    for (;;)
    {
        // Get the current node of the reader
        const WS_XML_NODE* node;
        hr = WsGetReaderNode(xmlReader, &node, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        for (ULONG i = 0; i < depth; i++)
        {
            printf(" ");
        }
        // Print out the type of node and its contents
        switch (node->nodeType)
        {
        case WS_XML_NODE_TYPE_ELEMENT:
            {
                const WS_XML_ELEMENT_NODE* elementNode = (const WS_XML_ELEMENT_NODE*) node;
                printf("WS_XML_NODE_TYPE_ELEMENT(prefix='");
                PrintString(elementNode->prefix);
                printf("', localName='");
                PrintString(elementNode->localName);
                printf("', ns='");
                PrintString(elementNode->ns);
                printf("', attributes={");
                for (ULONG i = 0; i < elementNode->attributeCount; i++)
                {
                    if (i != 0)
                    {
                        printf(", ");
                    }
                    const WS_XML_ATTRIBUTE* attribute = elementNode->attributes[i];
                    if (attribute->isXmlNs)
                    {
                        printf("(isXmlNs=TRUE, prefix='");
                        PrintString(attribute->prefix);
                        printf("', ns='");
                        PrintString(attribute->ns);
                        printf("')");
                    }
                    else
                    {
                        printf("(isXmlNs=FALSE, prefix='");
                        PrintString(attribute->prefix);
                        printf("', localName='");
                        PrintString(attribute->localName);
                        printf("', ns='");
                        PrintString(attribute->ns);
                        printf("', value=");
                        PrintText(attribute->value);
                        printf(")");
                    }
                }
                printf("})\n");
            }
            depth++;
            break;
        case WS_XML_NODE_TYPE_END_ELEMENT:
            printf("WS_XML_NODE_TYPE_END_ELEMENT\n");
            depth--;
            break;
        case WS_XML_NODE_TYPE_TEXT:
            {
                const WS_XML_TEXT_NODE* textNode = (const WS_XML_TEXT_NODE*) node;
                printf("WS_XML_NODE_TYPE_TEXT(value=");
                PrintText(textNode->text);
                printf(")\n");
            }
            break;
        case WS_XML_NODE_TYPE_CDATA:
            printf("WS_XML_NODE_TYPE_CDATA\n");
            depth++;
            break;
        case WS_XML_NODE_TYPE_END_CDATA:
            printf("WS_XML_NODE_TYPE_END_CDATA\n");
            depth--;
            break;
        case WS_XML_NODE_TYPE_COMMENT:
            {
                const WS_XML_COMMENT_NODE* commentNode = (const WS_XML_COMMENT_NODE*) node;
                printf("WS_XML_NODE_TYPE_COMMENT(value='");
                PrintString(&commentNode->value);
                printf("')\n");
            }
            break;
        case WS_XML_NODE_TYPE_BOF:
            printf("WS_XML_NODE_TYPE_BOF\n");
            depth++;
            break;
        case WS_XML_NODE_TYPE_EOF:
            printf("WS_XML_NODE_TYPE_EOF\n");
            depth--;
            break;
        default:
            printf("<error: Unexpected nodeType>\n");
            hr = E_FAIL;
            goto Exit;
        }
        // See if we've reached the end of the document
        if (node->nodeType == WS_XML_NODE_TYPE_EOF)
        {
            break;
        }
        // Advance the reader
        hr = WsReadNode(xmlReader, error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    }
    
Exit:
    if (FAILED(hr))
    {
        // Print out the error
        PrintError(hr, error);
    }
    
    if (xmlReader != NULL)
    {
        WsFreeReader(xmlReader);
    }
    if (error != NULL)
    {
        WsFreeError(error);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}