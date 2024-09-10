void CDoWaveConvert::OnButton1()
//------------------------------
{
    //XXXih:  onbutton1          :   -   (
    FILE *f;
    WAVEFILEHEADER header;
    WAVEDATAHEADER datahdr, fmthdr;
    MSG msg;
    uint8_t buffer[WAVECONVERTBUFSIZE];
    CHAR s[80];
    HWND progress = ::GetDlgItem(m_hWnd, IDC_PROGRESS1);
    UINT ok = IDOK, pos;
    ULONGLONG ullSamples, ullMaxSamples;
    uint32_t dwDataOffset;
    LONG lMax = 256;

    if ((!m_pSndFile) || (!m_lpszFileName) || ((f = fopen(m_lpszFileName, "w+b")) == NULL))
    {
        ::AfxMessageBox("Could not open file for writing. Is it open in another application?");
        EndDialog(IDCANCEL);
        return;
    }
    SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
    int oldVol = m_pSndFile->GetMasterVolume();
    int nOldRepeat = m_pSndFile->GetRepeatCount();
    module_renderer::deprecated_global_sound_setup_bitmask |= SNDMIX_DIRECTTODISK;
    if ((!m_dwFileLimit) && (!m_dwSongLimit)) module_renderer::deprecated_global_sound_setup_bitmask |= SNDMIX_NOBACKWARDJUMPS;
    module_renderer::deprecated_global_mixing_freq = m_pWaveFormat->nSamplesPerSec;
    module_renderer::deprecated_global_bits_per_sample = m_pWaveFormat->wBitsPerSample;
    module_renderer::deprecated_global_channels = m_pWaveFormat->nChannels;
// -> CODE#0024
// -> DESC="wav export update"
//    if ((m_bNormalize) && (m_pWaveFormat->wBitsPerSample <= 16))
    if ((m_bNormalize) && (m_pWaveFormat->wBitsPerSample <= 24))
// -! NEW_FEATURE#0024
    {
        m_pSndFile->deprecated_global_bits_per_sample = 24;
        if (oldVol > 128) m_pSndFile->SetMasterVolume(128);
    } else
    {
        m_bNormalize = false;
    }
    m_pSndFile->ResetChannels();
    module_renderer::InitPlayer(TRUE);
    m_pSndFile->SetRepeatCount(0);
    if ((!m_dwFileLimit) || (m_dwFileLimit > 2047*1024)) m_dwFileLimit = 2047*1024; // 2GB
    m_dwFileLimit <<= 10;
    // File Header
    header.id_RIFF = IFFID_RIFF;
    header.filesize = sizeof(WAVEFILEHEADER) - 8;
    header.id_WAVE = IFFID_WAVE;
    // Wave Format Header
    fmthdr.id_data = IFFID_fmt;
    fmthdr.length = 16;
    if (m_pWaveFormat->cbSize) fmthdr.length += 2 + m_pWaveFormat->cbSize;
    header.filesize += sizeof(fmthdr) + fmthdr.length;
    // Data header
    datahdr.id_data = IFFID_data;
    datahdr.length = 0;
    header.filesize += sizeof(datahdr);
    // Writing Headers
    fwrite(&header, 1, sizeof(header), f);
    fwrite(&fmthdr, 1, sizeof(fmthdr), f);
    fwrite(m_pWaveFormat, 1, fmthdr.length, f);
    fwrite(&datahdr, 1, sizeof(datahdr), f);
    dwDataOffset = ftell(f);
    pos = 0;
    ullSamples = 0;
    ullMaxSamples = m_dwFileLimit / (m_pWaveFormat->nChannels * m_pWaveFormat->wBitsPerSample / 8);
    if (m_dwSongLimit)
    {
        ULONGLONG l = (ULONGLONG)m_dwSongLimit * m_pWaveFormat->nSamplesPerSec;
        if (l < ullMaxSamples) ullMaxSamples = l;
    }

    // calculate maximum samples
    ULONGLONG bad_max = ullMaxSamples;
    ULONGLONG l = ((ULONGLONG)m_pSndFile->GetSongTime()) * m_pWaveFormat->nSamplesPerSec;
    if (m_nMaxPatterns > 0)
    {
        uint32_t dwOrds = m_pSndFile->Order.GetLengthFirstEmpty();
        if ((m_nMaxPatterns < dwOrds) && (dwOrds > 0)) l = (l*m_nMaxPatterns) / dwOrds;
    }

    if (l < bad_max) bad_max = l;

    if (progress != NULL)
    {
        ::SendMessage(progress, PBM_SETRANGE, 0, MAKELPARAM(0, (uint32_t)(bad_max >> 14)));
    }