/*
    nInterval is in SECONDS.  The buffer we create is 3 times the interval,
    so we make three notifications that will be placed at every interval.

    pProc will be called at approximately the interval specified.
*/
HRESULT WaveCapture::Initialize(int nDevice, WAVEFORMATEX* pFormat, WAVECAPTUREPROC pProc, PVOID pUser, int nInterval)
{
    DSCCAPS dsc;
    DSCBUFFERDESC1 dscbDesc;
    HRESULT hr;
    DSBPOSITIONNOTIFY NotifyPositions[3];
    IDirectSoundNotify* pdsn;

    this->Uninitialize();

    this->pProc = pProc;
    this->pUser = pUser;
    this->nInterval = nInterval;

    // Validation.
    if(pFormat->wFormatTag != WAVE_FORMAT_PCM)
    {
        return E_FAIL;
    }

    // Copy the wave format for our own purposes.
    memcpy(&this->Format, pFormat, sizeof(WAVEFORMATEX));

    m_iDevice = nDevice;
    memset(&m_Device, 0, sizeof(GUID));
    DirectSoundCaptureEnumerate(WaveCapture::DSEnumCallback, this);

    // Create DirectSoundCapture object.
    if(FAILED(hr = DirectSoundCaptureCreate(&m_Device, &this->pdsc, NULL)))
    {
        return E_FAIL;
    }

    /*
        Here is where we should check the capabilities of the sound card against
        the format that was passed in.
    */
    dsc.dwSize = sizeof(DSCCAPS);
    if(FAILED(hr = this->pdsc->GetCaps(&dsc)))
    {
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    /*
        Create the capture buffer.
    */
    dscbDesc.dwSize = sizeof(dscbDesc);
    dscbDesc.dwFlags = DSCBCAPS_WAVEMAPPED;
    dscbDesc.dwBufferBytes = (pFormat->nAvgBytesPerSec * nInterval) * 3;
    dscbDesc.dwReserved = 0;
    dscbDesc.lpwfxFormat = &this->Format;

    if(FAILED(hr = this->pdsc->CreateCaptureBuffer((DSCBUFFERDESC*)&dscbDesc, &this->pdsb, NULL)))
    {
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    /*
        Create the notifications
    */
    this->hEvents[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
    this->hEvents[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
    this->hEvents[2] = CreateEvent(NULL, FALSE, FALSE, NULL);
    this->hEvents[3] = CreateEvent(NULL, FALSE, FALSE, NULL);

    NotifyPositions[0].dwOffset = 0;
    NotifyPositions[0].hEventNotify = this->hEvents[0];

    NotifyPositions[1].dwOffset = (this->Format.nAvgBytesPerSec * nInterval);
    NotifyPositions[1].hEventNotify = this->hEvents[1];

    NotifyPositions[2].dwOffset = (this->Format.nAvgBytesPerSec * nInterval) * 2;
    NotifyPositions[2].hEventNotify = this->hEvents[2];

    if(FAILED(hr = this->pdsb->QueryInterface(IID_IDirectSoundNotify, (PVOID*)&pdsn)))
    {
        SAFE_RELEASE(this->pdsb);
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    if(FAILED(hr = pdsn->SetNotificationPositions(3, NotifyPositions)))
    {
        SAFE_RELEASE(pdsn);
        SAFE_RELEASE(this->pdsb);
        SAFE_RELEASE(this->pdsc);
        return E_FAIL;
    }

    SAFE_RELEASE(pdsn);

    /*
        Create our own buffer so when we pass data to pProc, the data is ALWAYS
        contiguous.
    */
    this->nBufferSize = (pFormat->nAvgBytesPerSec * nInterval) * 3;
    this->pBuffer = (PBYTE)malloc(this->nBufferSize);

    /*
        Initialize our own information.
    */
    this->dwLastPosition = 0;
    this->nPassesLeft = 1;

    /*
        Now create our recording thread so life can continue.
    */
    UINT dwThreadId;
	this->hThread = (HANDLE)_beginthreadex(
        0, 0, WaveCapture::RecordingThread, this, 0, &dwThreadId);

    return S_OK;
}