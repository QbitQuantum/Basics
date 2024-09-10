cDxCapture::cDxCapture() :
	m_width(0)
	, m_height(0)
	, m_cameraIndex(0)
	, m_pFrameBuffer(NULL)
	, m_frameBufferSize(0)
	, m_pCloneFrameBuffer(NULL)
	, m_isThreadMode(false)
	, m_threadLoop(true)
	, m_isUpdateBuffer(false)
	, m_isUnpluggedInit(false)
{
	m_dwGraphRegister = 0;
	m_pVW = NULL;
	m_pMC = NULL;
	m_pME = NULL;
	m_pGraph = NULL;
	m_pCapture = NULL;
	m_pGrabberF = NULL;
	m_pGrabber = NULL;
	m_pNullF = NULL;
	m_psCurrent = STOPPED;
	ZeroMemory(&m_mt, sizeof(m_mt));

	InitializeCriticalSectionAndSpinCount(&m_criticalSection, 0x00000400);

}