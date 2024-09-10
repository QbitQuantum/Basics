PassRefPtr<SharedBuffer> MHTMLArchive::generateMHTMLData(Page* page, bool useBinaryEncoding)
{
    Vector<PageSerializer::Resource> resources;
    PageSerializer pageSerializer(&resources);
    pageSerializer.serialize(page);

    String boundary = generateRandomBoundary();
    String endOfResourceBoundary = makeString("--", boundary, "\r\n");

    String dateString;
    time_t localTime = time(0);
    tm localTM;
    getLocalTime(&localTime, &localTM);
    dateString = makeRFC2822DateString(localTM.tm_wday, localTM.tm_mday, localTM.tm_mon, 1900 + localTM.tm_year, localTM.tm_hour, localTM.tm_min, localTM.tm_sec, calculateUTCOffset() / (1000 * 60));

    StringBuilder stringBuilder;
    stringBuilder.append("From: <Saved by WebKit>\r\n");
    stringBuilder.append("Subject: ");
    // We replace non ASCII characters with '?' characters to match IE's behavior.
    stringBuilder.append(replaceNonPrintableCharacters(page->mainFrame()->document()->title()));
    stringBuilder.append("\r\nDate: ");
    stringBuilder.append(dateString);
    stringBuilder.append("\r\nMIME-Version: 1.0\r\n");
    stringBuilder.append("Content-Type: multipart/related;\r\n");
    stringBuilder.append("\ttype=\"");
    stringBuilder.append(page->mainFrame()->document()->suggestedMIMEType());
    stringBuilder.append("\";\r\n");
    stringBuilder.append("\tboundary=\"");
    stringBuilder.append(boundary);
    stringBuilder.append("\"\r\n\r\n");

    // We use utf8() below instead of ascii() as ascii() replaces CRLFs with ?? (we still only have put ASCII characters in it).
    ASSERT(stringBuilder.toString().containsOnlyASCII());
    CString asciiString = stringBuilder.toString().utf8();
    RefPtr<SharedBuffer> mhtmlData = SharedBuffer::create();
    mhtmlData->append(asciiString.data(), asciiString.length());

    for (size_t i = 0; i < resources.size(); ++i) {
        const PageSerializer::Resource& resource = resources[i];

        stringBuilder.clear();
        stringBuilder.append(endOfResourceBoundary);
        stringBuilder.append("Content-Type: ");
        stringBuilder.append(resource.mimeType);

        const char* contentEncoding = useBinaryEncoding ? binary : base64;
        stringBuilder.append("\r\nContent-Transfer-Encoding: ");
        stringBuilder.append(contentEncoding);
        stringBuilder.append("\r\nContent-Location: ");
        stringBuilder.append(resource.url);
        stringBuilder.append("\r\n\r\n");

        asciiString = stringBuilder.toString().utf8();
        mhtmlData->append(asciiString.data(), asciiString.length());

        if (!strcmp(contentEncoding, binary)) {
            const char* data;
            size_t position = 0;
            while (size_t length = resource.data->getSomeData(data, position)) {
                mhtmlData->append(data, length);
                position += length;
            }
        } else {
            // FIXME: ideally we would encode the content as a stream without having to fetch it all.
            const char* data = resource.data->data();
            size_t dataLength = resource.data->size();
            Vector<char> encodedData;
            if (!strcmp(contentEncoding, quotedPrintable)) {
                quotedPrintableEncode(data, dataLength, encodedData);
                mhtmlData->append(encodedData.data(), encodedData.size());
                mhtmlData->append("\r\n", 2);
            } else {
                ASSERT(!strcmp(contentEncoding, base64));
                // We are not specifying insertLFs = true below as it would cut the lines with LFs and MHTML requires CRLFs.
                base64Encode(data, dataLength, encodedData);
                const size_t maximumLineLength = 76;
                size_t index = 0;
                size_t encodedDataLength = encodedData.size();
                do {
                    size_t lineLength = std::min(encodedDataLength - index, maximumLineLength);
                    mhtmlData->append(encodedData.data() + index, lineLength);
                    mhtmlData->append("\r\n", 2);
                    index += maximumLineLength;
                } while (index < encodedDataLength);
            }
        }
    }

    asciiString = makeString("--", boundary, "--\r\n").utf8();
    mhtmlData->append(asciiString.data(), asciiString.length());

    return mhtmlData.release();
}