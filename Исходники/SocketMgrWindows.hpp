XStreamNode* XSocketMgr::CreateStream(
    SOCKET nSocket, const char cszRemoteIP[], int nRemotePort, time_t nTimeNow, size_t uMaxPackLen
)
{
    XStreamNode*        pResult     = NULL;
    int                 nRetCode    = 0;
    int                 nSocketOpt  = 0;
    XStreamNode*        pNode       = NULL;
    BYTE*               pbyBuffer   = NULL;

    XY_FAILED_JUMP(m_pStreamNodeFree);
    pNode = m_pStreamNodeFree;
    m_pStreamNodeFree = m_pStreamNodeFree->pNext;

    pbyBuffer = new BYTE[uMaxPackLen];
    XY_FAILED_JUMP(pbyBuffer);

    nRetCode = BindIoCompletionCallback((HANDLE)nSocket, IOCompletionCallBack, 0);
    XY_FAILED_JUMP(nRetCode);

    nRetCode = SafeCopyString(pNode->szRemoteIP, sizeof(pNode->szRemoteIP), cszRemoteIP);
    XY_FAILED_JUMP(nRetCode);

    pNode->bListener        = false;
    pNode->nSocket          = nSocket;
    pNode->bUsrClose        = false;
    pNode->pbyBuffer        = pbyBuffer;
    pNode->uBufferSize      = uMaxPackLen;
    pNode->pbyDataBegin     = pbyBuffer;
    pNode->pbyDataEnd       = pbyBuffer;
    pNode->nRemotePort      = nRemotePort;
    pNode->bErrNotified     = false;
    pNode->nSysErr          = 0;
    pNode->nUsrErr          = 0;
    pNode->nTimeoutSeconds  = -1;
    pNode->uLastPackTime    = nTimeNow;
    pNode->pDataProc        = NULL;
    pNode->pErrProc         = NULL;
    pNode->pvUsrData        = NULL;
    pNode->bComplete        = true;
	pNode->nSendRetryCount	= 0;
	pNode->nSendRetrySleep	= 0;

    pNode->pNext = m_StreamHeadNode.pNext;
    m_StreamHeadNode.pNext = pNode;

    pResult = pNode;
Exit0:
    if (pResult == NULL)
    {
        XY_DELETE_ARRAY(pbyBuffer);

        if (pNode)
        {
            pNode->pNext = m_pStreamNodeFree;
            m_pStreamNodeFree = pNode;
            pNode = NULL;
        }
    }
    return pResult;
}