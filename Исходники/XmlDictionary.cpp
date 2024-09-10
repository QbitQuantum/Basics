// Main entry point
int __cdecl wmain()
{
    
    HRESULT hr = S_OK;
    WS_ERROR* error = NULL;
    WS_XML_WRITER* writer = NULL;
    WS_XML_READER* reader = NULL;
    WS_HEAP* heap = NULL;
    
    // Create an error object for storing rich error information
    hr = WsCreateError(
        NULL, 
        0, 
        &error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create a heap to store deserialized data
    hr = WsCreateHeap(
        /*maxSize*/ 2048, 
        /*trimSize*/ 512, 
        NULL, 
        0, 
        &heap, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create an XML writer
    hr = WsCreateWriter(
        NULL, 
        0, 
        &writer, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Setup the output
    WS_XML_WRITER_BUFFER_OUTPUT bufferOutput;
    ZeroMemory(&bufferOutput, sizeof(bufferOutput));
    bufferOutput.output.outputType = WS_XML_WRITER_OUTPUT_TYPE_BUFFER;
    
    // Setup the encoding
    WS_XML_WRITER_BINARY_ENCODING writerEncoding;
    ZeroMemory(&writerEncoding, sizeof(writerEncoding));
    writerEncoding.encoding.encodingType = WS_XML_WRITER_ENCODING_TYPE_BINARY;
    writerEncoding.staticDictionary = &objectsDictionary.dictionary;
    writerEncoding.dynamicStringCallback = DynamicStringCallback;
    writerEncoding.dynamicStringCallbackState = NULL;
    
    // Setup the writer
    hr = WsSetOutput(
        writer, 
        &writerEncoding.encoding, 
        &bufferOutput.output, 
        NULL, 
        0, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsWriteStartElement(
        writer, 
        NULL, 
        &objectsDictionary.objects, 
        &objectsDictionary.ns, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Write some xml using strings from all the dictionaries
    static const WS_XML_STRING* shapes[3] = { &shapeDictionary.triangle, &shapeDictionary.square, &shapeDictionary.circle };
    static const WS_XML_STRING* colors[3] = { &colorDictionary.green, &colorDictionary.blue, &colorDictionary.red };
    for (ULONG i = 0; i < 3; i++)
    {
        hr = WsWriteStartElement(
            writer, 
            NULL, 
            shapes[i], 
            &objectsDictionary.ns, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        hr = WsWriteStartAttribute(
            writer, 
            NULL, 
            &objectsDictionary.color, 
            &objectsDictionary.ns, 
            FALSE, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        hr = WsWriteType(
            writer, 
            WS_ATTRIBUTE_TYPE_MAPPING, 
            WS_XML_STRING_TYPE, NULL, 
            WS_WRITE_REQUIRED_VALUE, 
            colors[i], 
            sizeof(*colors[i]), 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        hr = WsWriteEndAttribute(
            writer, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        hr = WsWriteEndElement(
            writer, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    }
    
    hr = WsWriteEndElement(
        writer, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    WS_BYTES bytes;
    hr = WsGetWriterProperty(
        writer, 
        WS_XML_WRITER_PROPERTY_BYTES, 
        &bytes, 
        sizeof(bytes), 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Create an XML reader
    hr = WsCreateReader(
        NULL,
        0, 
        &reader, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    // Setup the input
    WS_XML_READER_BUFFER_INPUT bufferInput;
    ZeroMemory(&bufferInput, sizeof(bufferInput));
    bufferInput.input.inputType = WS_XML_READER_INPUT_TYPE_BUFFER;
    bufferInput.encodedData = bytes.bytes;
    bufferInput.encodedDataSize = bytes.length;
    
    // Setup the encoding
    WS_XML_READER_BINARY_ENCODING readerEncoding;
    ZeroMemory(
        &readerEncoding, 
        sizeof(readerEncoding));
    
    readerEncoding.encoding.encodingType = WS_XML_READER_ENCODING_TYPE_BINARY;
    readerEncoding.staticDictionary = &objectsDictionary.dictionary;
    readerEncoding.dynamicDictionary = &mergedDictionary.dictionary;
    
    // Setup the reader
    hr = WsSetInput(
        reader, 
        &readerEncoding.encoding, 
        &bufferInput.input, 
        NULL, 
        0, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    hr = WsReadToStartElement(
        reader, 
        &objectsDictionary.objects, 
        &objectsDictionary.ns, 
        NULL, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    hr = WsReadStartElement(
        reader, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
    for (;;)
    {
        BOOL found;
        hr = WsReadToStartElement(
            reader, 
            NULL, 
            NULL, 
            &found, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        if (!found)
        {
            break;
        }
    
        const WS_XML_NODE* node;
        hr = WsGetReaderNode(
            reader, 
            &node, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        const WS_XML_ELEMENT_NODE* elementNode = (WS_XML_ELEMENT_NODE*)node;
        printf("%.*s: ", elementNode->localName->length, elementNode->localName->bytes);
    
        ULONG index;
        hr = WsFindAttribute(
            reader, 
            &objectsDictionary.color, 
            &objectsDictionary.ns, 
            TRUE, 
            &index, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        hr = WsReadStartAttribute(
            reader, 
            index, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        WS_XML_STRING color;
        hr = WsReadType(
            reader, 
            WS_ATTRIBUTE_TYPE_MAPPING, 
            WS_XML_STRING_TYPE, 
            NULL, 
            WS_READ_REQUIRED_VALUE, 
            heap, 
            &color, 
            sizeof(color), 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    
        printf(
            "%.*s\n", 
            color.length, 
            color.bytes);
    
        hr = WsReadEndAttribute(
            reader, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
        
        hr = WsSkipNode(
            reader, 
            error);
        if (FAILED(hr))
        {
            goto Exit;
        }
    }
    
    hr = WsReadEndElement(
        reader, 
        error);
    if (FAILED(hr))
    {
        goto Exit;
    }
    
Exit:
    if (FAILED(hr))
    {
        // Print out the error
        PrintError(hr, error);
    }
    
    if (writer != NULL)
    {
        WsFreeWriter(writer);
    }
    if (reader != NULL)
    {
        WsFreeReader(reader);
    }
    if (heap != NULL)
    {
        WsFreeHeap(heap);
    }
    if (error != NULL)
    {
        WsFreeError(error);
    }
    fflush(stdout);
    return SUCCEEDED(hr) ? 0 : -1;
}