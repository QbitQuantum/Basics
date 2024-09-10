PVIRUSTOTAL_FILE_REPORT_RESULT VirusTotalSendHttpFileReportRequest(
    _In_ PPH_STRING FileHash
    )
{
    NTSTATUS status = STATUS_SUCCESS;
    HANDLE fileHandle = INVALID_HANDLE_VALUE;
    HINTERNET httpSessionHandle = NULL;
    HINTERNET connectHandle = NULL;
    HINTERNET requestHandle = NULL;
    PSTR subRequestBuffer = NULL;
    PPH_STRING phVersion = NULL;
    PPH_STRING userAgent = NULL;
    PPH_STRING urlString = NULL;

    phVersion = PhGetPhVersion();
    userAgent = PhConcatStrings2(L"ProcessHacker_", phVersion->Buffer);

    if (!(httpSessionHandle = WinHttpOpen(
        userAgent->Buffer,
        WindowsVersion >= WINDOWS_8_1 ? WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY : WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0
        )))
    {
        goto CleanupExit;
    }

    if (WindowsVersion >= WINDOWS_8_1)
    {
        WinHttpSetOption(
            httpSessionHandle,
            WINHTTP_OPTION_DECOMPRESSION, 
            &(ULONG){ WINHTTP_DECOMPRESSION_FLAG_GZIP | WINHTTP_DECOMPRESSION_FLAG_DEFLATE }, 
            sizeof(ULONG)
            );
    }

    if (!(connectHandle = WinHttpConnect(
        httpSessionHandle,
        L"www.virustotal.com",
        INTERNET_DEFAULT_HTTPS_PORT,
        0
        )))
    {
        goto CleanupExit;
    }

    PPH_BYTES resourceString = VirusTotalGetCachedDbHash();

    urlString = PhFormatString(
        L"%s%s%s%s%S%s%s",
        L"/vtapi",
        L"/v2",
        L"/file",
        L"/report",
        L"?apikey=",
        resourceString->Buffer,
        L"&resource=",
        PhGetString(FileHash)
        );

    PhClearReference(&resourceString);

    if (!(requestHandle = WinHttpOpenRequest(
        connectHandle,
        L"POST",
        PhGetString(urlString),
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        WINHTTP_FLAG_SECURE
        )))
    {
        goto CleanupExit;
    }

    if (!WinHttpAddRequestHeaders(requestHandle, L"Content-Type: application/json", -1L, 0))
        goto CleanupExit;

    if (!WinHttpSendRequest(
        requestHandle,
        WINHTTP_NO_ADDITIONAL_HEADERS,
        0,
        WINHTTP_NO_REQUEST_DATA,
        0,
        WINHTTP_IGNORE_REQUEST_TOTAL_LENGTH,
        0
        ))
    {
        goto CleanupExit;
    }

    if (WinHttpReceiveResponse(requestHandle, NULL))
    {
        BYTE buffer[PAGE_SIZE];
        ULONG allocatedLength;
        ULONG dataLength;
        ULONG returnLength;

        allocatedLength = sizeof(buffer);
        subRequestBuffer = PhAllocate(allocatedLength);
        dataLength = 0;

        while (WinHttpReadData(requestHandle, buffer, PAGE_SIZE, &returnLength))
        {
            if (returnLength == 0)
                break;

            if (allocatedLength < dataLength + returnLength)
            {
                allocatedLength *= 2;
                subRequestBuffer = PhReAllocate(subRequestBuffer, allocatedLength);
            }

            memcpy(subRequestBuffer + dataLength, buffer, returnLength);
            dataLength += returnLength;
        }

        if (allocatedLength < dataLength + 1)
        {
            allocatedLength++;
            subRequestBuffer = PhReAllocate(subRequestBuffer, allocatedLength);
        }

        subRequestBuffer[dataLength] = 0;
    }

CleanupExit:

    PhClearReference(&urlString);

    if (requestHandle)
        WinHttpCloseHandle(requestHandle);

    if (connectHandle)
        WinHttpCloseHandle(connectHandle);

    if (httpSessionHandle)
        WinHttpCloseHandle(httpSessionHandle);


    PVOID jsonRootObject;
    //PVOID jsonScanObject;
    PVIRUSTOTAL_FILE_REPORT_RESULT result;

    if (!(jsonRootObject = CreateJsonParser(subRequestBuffer)))
        goto CleanupExit;

    if (!GetJsonValueAsUlong(jsonRootObject, "response_code"))
        goto CleanupExit;

    result = PhAllocate(sizeof(VIRUSTOTAL_FILE_REPORT_RESULT));
    memset(result, 0, sizeof(VIRUSTOTAL_FILE_REPORT_RESULT));

    result->Total = PhFormatUInt64(GetJsonValueAsUlong(jsonRootObject, "total"), FALSE);
    result->Positives = PhFormatUInt64(GetJsonValueAsUlong(jsonRootObject, "positives"), FALSE);
    result->Resource = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "resource"));
    result->ScanId = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "scan_id"));
    result->Md5 = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "md5"));
    result->Sha1 = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "sha1"));
    result->Sha256 = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "sha256"));
    result->ScanDate = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "scan_date"));
    result->Permalink = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "permalink"));
    result->StatusMessage = PhZeroExtendToUtf16(GetJsonValueAsString(jsonRootObject, "verbose_msg"));

    //if (jsonScanObject = JsonGetObject(jsonRootObject, "scans"))
    //{
    //    PPH_LIST jsonArrayList;
    //
    //    if (jsonArrayList = JsonGetObjectArrayList(jsonScanObject))
    //    {
    //        result->ScanResults = PhCreateList(jsonArrayList->Count);
    //
    //        for (ULONG i = 0; i < jsonArrayList->Count; i++)
    //        {
    //            PJSON_ARRAY_LIST_OBJECT object = jsonArrayList->Items[i];
    //            //BOOLEAN detected = GetJsonValueAsBool(object->Entry, "detected") == TRUE;
    //            //PSTR version = GetJsonValueAsString(object->Entry, "version");
    //            //PSTR result = GetJsonValueAsString(object->Entry, "result");
    //            //PSTR update = GetJsonValueAsString(object->Entry, "update");
    //
    //            PhFree(object);
    //        }
    //
    //        PhDereferenceObject(jsonArrayList);
    //    }
    //}

    return result;
}