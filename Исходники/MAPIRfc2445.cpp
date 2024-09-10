HRESULT MAPIRfc2445::ExtractAttachments()
{
    // may need to break this up so we can call for exceptions, cancel exceptions

    LPCWSTR errMsg;
    Zimbra::Util::ScopedInterface<IStream> pIStream;
    UINT mimeLen = 0;
    HRESULT hr = ConvertIt( m_pMessage, pIStream.getptr(), mimeLen );
    if (FAILED(hr))
    {
        errMsg = FormatExceptionInfo(hr, L"Mime conversion of message with attachments failed", __FILE__, __LINE__);
        dlogw(errMsg);
        return hr;
    }

    mimepp::Message mimeMsg;
    Zimbra::Util::ScopedBuffer<CHAR> pszMimeMsg;

    // go to the beginning of the stream
    LARGE_INTEGER li = { 0 };

    hr = pIStream->Seek(li, STREAM_SEEK_SET, NULL);
    if (FAILED(hr))
    {
        errMsg = FormatExceptionInfo(hr, L"Stream seek failed", __FILE__, __LINE__);
        dlogw(errMsg);
        return hr;
    }

    // +1 for NULL terminator
    Zimbra::Mapi::Memory::AllocateBuffer(mimeLen + 1, (LPVOID *)pszMimeMsg.getptr());
    if (!pszMimeMsg.get())
    {
        errMsg = FormatExceptionInfo(S_OK, L"Mime msg Memory alloc failed", __FILE__, __LINE__);
        dlogw(errMsg);
        return hr;
    }

    ULONG ulNumRead = 0;

    hr = pIStream->Read((LPVOID)(pszMimeMsg.get()), mimeLen, &ulNumRead);
    if (FAILED(hr))
    {
        errMsg = FormatExceptionInfo(hr, L"Mime msg read failed", __FILE__, __LINE__);
        dlogw(errMsg);
        return hr;
    }
    if (ulNumRead != mimeLen)
    {
        errMsg = FormatExceptionInfo(hr, L"Mime msg read error", __FILE__, __LINE__);
        dlogw(errMsg);
        return hr;
    }

    // terminating string
    pszMimeMsg.get()[mimeLen] = '\0';

    mimeMsg.setString(pszMimeMsg.get());
    mimeMsg.parse();

    // let's see if this message is a multipart alternative before we continue
    mimepp::Headers &theHeaders = mimeMsg.headers();

    LPSTR pszContentType;
    GetContentType(theHeaders, &pszContentType);

    if(strncmp(pszContentType, "multipart/mixed", strlen("multipart/mixed")) != 0) 
    {
        // not what we are looking for
        delete[] pszContentType;
        return S_OK;
    }

    const mimepp::Body& theBody = mimeMsg.body();
    int numParts = theBody.numBodyParts();

    // FBS bug 73682 -- 5/23/12
    int numHiddenAttachments = GetNumHiddenAttachments();
    int totalAttachments = numParts - 1;
    if (totalAttachments == numHiddenAttachments)
    {
        return S_OK;
    }

    // let's look for a multipart mixed and grab the attachments
    int ctr = numHiddenAttachments;
    for(int i = 0; i < numParts; i++) 
    {
        // now look for attachments
        const mimepp::BodyPart& thePart = theBody.bodyPartAt(i);
        mimepp::DispositionType& disposition = thePart.headers().contentDisposition();
        if(disposition.asEnum() == mimepp::DispositionType::ATTACHMENT) 
        {
            const mimepp::String& theFilename = disposition.filename();

            LPSTR pszAttachContentType;
            LPSTR pszCD;
            LPSTR lpszRealName = new char[256];
            GetContentType(thePart.headers(), &pszAttachContentType);

            // FBS bug 73682 -- Exceptions are at the beginning.  Don't make attachments for those
            if (ctr > 0)
            {
                if (0 == strcmpi(pszAttachContentType, "message/rfc822"))
                {
                    ctr--;
                    continue;
                }
            }
            //

            if((LPSTR)theFilename.length()>0)
            {
                GenerateContentDisposition(&pszCD, (LPSTR)theFilename.c_str());
                strcpy(lpszRealName, (LPSTR)theFilename.c_str());
            }
            else
            {
                char cfilename[64];
                sprintf(cfilename,"attachment-%d",i);
                GenerateContentDisposition(&pszCD, cfilename);
                strcpy(lpszRealName, cfilename);
            }

            // now deal with the encoding
            LPSTR pContent = NULL;
            const mimepp::String &theContent = thePart.body().getString();
            mimepp::String outputString;
            UINT size = 0;

            mimepp::TransferEncodingType& transferEncoding = thePart.headers().contentTransferEncoding();

            if(transferEncoding.asEnum() == mimepp::TransferEncodingType::BASE64) 
            {
                // let's decode the buffer
                mimepp::Base64Decoder decoder;
                outputString = decoder.decode(theContent);
                pContent = (LPSTR)outputString.c_str();
                size = (UINT)outputString.size();
            } 
            else if(transferEncoding.asEnum() == mimepp::TransferEncodingType::QUOTED_PRINTABLE) 
            {
                mimepp::QuotedPrintableDecoder decoder;
                outputString  = decoder.decode(theContent);
                pContent = (LPSTR)outputString.c_str();
                size = (UINT)outputString.size();
            } 
            else 
            {
                pContent = (LPSTR)theContent.c_str();
                size = (UINT)theContent.size();
            }

	    // Save stream to temp file in temp dir.  We'll delete in ZimbraAPI //
            LPCWSTR errMsg;
            HRESULT hr = S_OK;

            wstring wstrTempAppDirPath;
            LPSTR lpszFQFileName = new char[256];
            LPSTR lpszDirName = NULL;
            LPSTR lpszUniqueName = NULL;
            Zimbra::Util::ScopedInterface<IStream> pStream;

            if (!Zimbra::MAPI::Util::GetAppTemporaryDirectory(wstrTempAppDirPath))
            {
                errMsg = FormatExceptionInfo(S_OK, L"GetAppTemporaryDirectory Failed", __FILE__, __LINE__);
                dloge("MAPIRfc2445 -- exception");
                dloge(errMsg);
                return E_FAIL;
            }
            WtoA((LPWSTR)wstrTempAppDirPath.c_str(), lpszDirName);
            WtoA((LPWSTR)Zimbra::MAPI::Util::GetUniqueName().c_str(), lpszUniqueName);
            strcpy(lpszFQFileName, lpszDirName);
            strcat(lpszFQFileName, "\\");
            strcat(lpszFQFileName, lpszUniqueName);

            SafeDelete(lpszDirName);
            SafeDelete(lpszUniqueName);

            // Open stream on file
            if (FAILED(hr = OpenStreamOnFile(MAPIAllocateBuffer, MAPIFreeBuffer, STGM_CREATE |
                    STGM_READWRITE, (LPTSTR)lpszFQFileName, NULL, pStream.getptr())))
            {
                errMsg = FormatExceptionInfo(hr, L"Error: OpenStreamOnFile Failed.", __FILE__, __LINE__);
                dloge("MAPIRfc2445 -- exception");
                dloge(errMsg);
                return hr;
            }

            ULONG nBytesToWrite = size;
            ULONG nBytesWritten = 0;
            LPBYTE pCur = (LPBYTE)pContent;
            while (!FAILED(hr) && nBytesToWrite > 0) 
            {
                hr = pStream->Write(pCur, nBytesToWrite, &nBytesWritten);
                pCur += nBytesWritten;
                nBytesToWrite -= nBytesWritten;
            }
            if (FAILED(hr = pStream->Commit(0)))
            {
                errMsg = FormatExceptionInfo(hr, L"Error: Stream Write Failed.", __FILE__, __LINE__);
                dloge("MAPIRfc2445 -- exception");
                dloge(errMsg);
            }
            ///////////

            // delete all this in MAPIAccessWrap
            AttachmentInfo* pAttachmentInfo = new AttachmentInfo();
            pAttachmentInfo->pszTempFile = lpszFQFileName;
            pAttachmentInfo->pszRealName = lpszRealName;
            pAttachmentInfo->pszContentDisposition = pszCD;
            pAttachmentInfo->pszContentType = pszAttachContentType;
            m_vAttachments.push_back(pAttachmentInfo);
        }
    }
    delete[] pszContentType;
    return S_OK;
}