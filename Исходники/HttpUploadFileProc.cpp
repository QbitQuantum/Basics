BOOL CHttpUploadFileProc::UseHttpSendReqEx(HINTERNET hRequest, CFile &file)
{
    //	生成form-data协议信息	<begin>
    CStringA	straHeader;
    CStringA	straContentHead;
    CStringA	straContentTail;

    straHeader = GetHttpAppendHeader();
    straContentHead = GetContentHead(file.GetFileName());
    straContentTail = GetContentTail();
    //	生成form-data协议信息	<end>

    ULONGLONG	ullFileLength = file.GetLength();
    DWORD	dwContentLength = straContentHead.GetLength() + (DWORD) ullFileLength + straContentTail.GetLength();

    INTERNET_BUFFERS BufferIn = {0};
    BufferIn.dwStructSize = sizeof( INTERNET_BUFFERS ); // Must be set or error will occur
    BufferIn.Next = NULL;
    //BufferIn.lpcszHeader = NULL;
    //BufferIn.dwHeadersLength = 0;
    BufferIn.lpcszHeader = straHeader.LockBuffer();
    straHeader.UnlockBuffer();
    BufferIn.dwHeadersLength = (DWORD)straHeader.GetLength();
    BufferIn.dwHeadersTotal = 0;
    BufferIn.lpvBuffer = NULL;
    BufferIn.dwBufferLength = 0;
    BufferIn.dwBufferTotal = dwContentLength;
    BufferIn.dwOffsetLow = 0;
    BufferIn.dwOffsetHigh = 0;

    if (IsTerminated())	return FALSE;
    NotifyReceiver(P_HUF_SENDING_FILE, 0);
    if(!HttpSendRequestEx( hRequest, &BufferIn, NULL, 0, 0))
        return FALSE;

    UINT	uProgressBegin = 10;
    UINT	uProgressEnd = 90;
    UINT	uProgressCur = 0;
    UINT	uReadCountSum = 0;


    const UINT uBufSize = 1024;
    BYTE pBuffer[uBufSize];
    UINT uReadCount;
    DWORD dwBytesWritten;
    BOOL bRet;
    float	fSendPercent;
    UINT	uProgressScale;


    //	Write Head
    bRet = InternetWriteFile( hRequest, straContentHead.LockBuffer(), straContentHead.GetLength(), &dwBytesWritten);
    straContentHead.UnlockBuffer();
    if(!bRet)
    {
        NotifyReceiver(E_HUF_SEND_FILE_FAILED, 0);
        return FALSE;
    }

    if (IsTerminated())	return FALSE;
    //	Write file contents
    uReadCountSum = 0;
    bRet = TRUE;
    file.SeekToBegin();
    do {
        if (IsTerminated())	return FALSE;
        uReadCount = file.Read(pBuffer, uBufSize);
        if (0 == uReadCount)
            break;

        if(! InternetWriteFile( hRequest, pBuffer, uReadCount, &dwBytesWritten))
        {
            NotifyReceiver(E_HUF_SEND_FILE_FAILED, 0);
            return FALSE;
        }

        uReadCountSum += uReadCount;
        fSendPercent = (float)uReadCountSum / BufferIn.dwBufferTotal;
        uProgressScale = (UINT) ((uProgressEnd - uProgressBegin) * fSendPercent);
        uProgressCur = uProgressBegin + uProgressScale;
        NotifyReceiver(P_HUF_PROGRESS, uProgressCur);

    } while (uReadCount == uBufSize);

    if (IsTerminated())	return FALSE;
    //	Write Tail
    bRet = InternetWriteFile( hRequest, straContentTail.LockBuffer(), straContentTail.GetLength(), &dwBytesWritten);
    straContentTail.UnlockBuffer();
    if(!bRet)
    {
        NotifyReceiver(E_HUF_SEND_FILE_FAILED, 0);
        return FALSE;
    }
    NotifyReceiver(P_HUF_PROGRESS, uProgressEnd);


    if (IsTerminated())	return FALSE;
    NotifyReceiver(P_HUF_WAIT_RESPONSE, 0);
    if (!HttpEndRequest(hRequest, NULL, 0, 0))
    {
        NotifyReceiver(E_HUF_WAIT_RESPONSE_FAILD, 0);
        bRet = FALSE;
    }

    return bRet;
}