/*****************************************************************************************
Initialize
*****************************************************************************************/
int CUnMAC::Initialize(IAPEDecompress *pAPEDecompress) 
{
    // uninitialize if it is currently initialized
    if (m_bInitialized)
        Uninitialize();

    if (pAPEDecompress == NULL)
    {
        Uninitialize();
        return ERROR_INITIALIZING_UNMAC;
    }

    // set the member pointer to the IAPEDecompress class
    m_pAPEDecompress = pAPEDecompress;

    // set the last decode frame to -1 so it forces a seek on start
    m_LastDecodedFrameIndex = -1;

    m_pAPEDecompressCore = new CAPEDecompressCore(GET_IO(pAPEDecompress), pAPEDecompress);
    m_pPrepare = new CPrepare;

    // set the initialized flag to TRUE
    m_bInitialized = TRUE;
    
    m_pAPEDecompress->GetInfo(APE_INFO_WAVEFORMATEX, (long) &m_wfeInput);

    // return a successful value
    return ERROR_SUCCESS;
}