bool CCDDAStream::Load(const WCHAR* fnw)
{
    CString path(fnw);

    int iDriveLetter = path.Find(_T(":\\")) - 1;
    int iTrackIndex = CString(path).MakeLower().Find(_T(".cda")) - 1;
    if (iDriveLetter < 0 || iTrackIndex <= iDriveLetter) {
        return false;
    }

    CString drive = CString(_T("\\\\.\\")) + path[iDriveLetter] + _T(":");
    while (iTrackIndex > 0 && _istdigit(path[iTrackIndex - 1])) {
        iTrackIndex--;
    }
    if (1 != _stscanf_s(path.Mid(iTrackIndex), _T("%d"), &iTrackIndex)) {
        return false;
    }

    if (m_hDrive != INVALID_HANDLE_VALUE) {
        CloseHandle(m_hDrive);
        m_hDrive = INVALID_HANDLE_VALUE;
    }

    m_hDrive = CreateFile(drive, GENERIC_READ, FILE_SHARE_READ, nullptr,
                          OPEN_EXISTING, FILE_ATTRIBUTE_READONLY | FILE_FLAG_SEQUENTIAL_SCAN, (HANDLE)nullptr);
    if (m_hDrive == INVALID_HANDLE_VALUE) {
        return false;
    }

    DWORD BytesReturned;
    if (!DeviceIoControl(m_hDrive, IOCTL_CDROM_READ_TOC, nullptr, 0, &m_TOC, sizeof(m_TOC), &BytesReturned, 0)
            || !(m_TOC.FirstTrack <= iTrackIndex && iTrackIndex <= m_TOC.LastTrack)) {
        CloseHandle(m_hDrive);
        m_hDrive = INVALID_HANDLE_VALUE;
        return false;
    }

    // MMC-3 Draft Revision 10g: Table 222 - Q Sub-channel control field
    m_TOC.TrackData[iTrackIndex - 1].Control &= 5;
    if (!(m_TOC.TrackData[iTrackIndex - 1].Control == 0 || m_TOC.TrackData[iTrackIndex - 1].Control == 1)) {
        CloseHandle(m_hDrive);
        m_hDrive = INVALID_HANDLE_VALUE;
        return false;
    }

    if (m_TOC.TrackData[iTrackIndex - 1].Control & 8) {
        m_header.frm.pcm.wf.nChannels = 4;
    }

    m_nStartSector = MSF2UINT(m_TOC.TrackData[iTrackIndex - 1].Address) - 150; //MSF2UINT(m_TOC.TrackData[0].Address);
    m_nStopSector = MSF2UINT(m_TOC.TrackData[iTrackIndex].Address) - 150;//MSF2UINT(m_TOC.TrackData[0].Address);

    m_llLength = LONGLONG(m_nStopSector - m_nStartSector) * RAW_SECTOR_SIZE;

    m_header.riff.hdr.chunkSize = (long)(m_llLength + sizeof(m_header) - 8);
    m_header.data.hdr.chunkSize = (long)(m_llLength);

    do {
        CDROM_READ_TOC_EX TOCEx;
        ZeroMemory(&TOCEx, sizeof(TOCEx));
        TOCEx.Format = CDROM_READ_TOC_EX_FORMAT_CDTEXT;
        TOCEx.SessionTrack = iTrackIndex;
        WORD size = 0;
        ASSERT(MINIMUM_CDROM_READ_TOC_EX_SIZE == sizeof(size));
        if (!DeviceIoControl(m_hDrive, IOCTL_CDROM_READ_TOC_EX, &TOCEx, sizeof(TOCEx), &size, sizeof(size), &BytesReturned, 0)) {
            break;
        }

        size = _byteswap_ushort(size) + sizeof(size);

        CAutoVectorPtr<BYTE> pCDTextData;
        if (!pCDTextData.Allocate(size)) {
            break;
        }
        ZeroMemory(pCDTextData, size);

        if (!DeviceIoControl(m_hDrive, IOCTL_CDROM_READ_TOC_EX, &TOCEx, sizeof(TOCEx), pCDTextData, size, &BytesReturned, 0)) {
            break;
        }

        size = (WORD)(BytesReturned - sizeof(CDROM_TOC_CD_TEXT_DATA));
        CDROM_TOC_CD_TEXT_DATA_BLOCK* pDesc = ((CDROM_TOC_CD_TEXT_DATA*)(BYTE*)pCDTextData)->Descriptors;

        CStringArray str[16];
        for (int i = 0; i < _countof(str); i++) {
            str[i].SetSize(1 + m_TOC.LastTrack);
        }
        CString last;

        for (int i = 0; size >= sizeof(CDROM_TOC_CD_TEXT_DATA_BLOCK); i++, size -= sizeof(CDROM_TOC_CD_TEXT_DATA_BLOCK), pDesc++) {
            if (pDesc->TrackNumber > m_TOC.LastTrack) {
                continue;
            }

            const int lenU = _countof(pDesc->Text);
            const int lenW = _countof(pDesc->WText);

            CString text = !pDesc->Unicode
                           ? CString(CStringA((CHAR*)pDesc->Text, lenU))
                           : CString(CStringW((WCHAR*)pDesc->WText, lenW));

            int tlen = text.GetLength();
            CString tmp = (tlen < 12 - 1)
                          ? (!pDesc->Unicode
                             ? CString(CStringA((CHAR*)pDesc->Text + tlen + 1, lenU - (tlen + 1)))
                             : CString(CStringW((WCHAR*)pDesc->WText + tlen + 1, lenW - (tlen + 1))))
                          : _T("");

            if (pDesc->PackType < 0x80 || pDesc->PackType >= 0x80 + 0x10) {
                continue;
            }
            pDesc->PackType -= 0x80;

            if (pDesc->CharacterPosition == 0) {
                str[pDesc->PackType][pDesc->TrackNumber] = text;
            } else { // pDesc->CharacterPosition <= 0xf since CharacterPosition is a 4-bit field
                if (pDesc->CharacterPosition < 0xf && !last.IsEmpty()) {
                    str[pDesc->PackType][pDesc->TrackNumber] = last + text;
                } else {
                    str[pDesc->PackType][pDesc->TrackNumber] += text;
                }
            }

            last = tmp;
        }

        m_discTitle = str[0][0];
        m_trackTitle = str[0][iTrackIndex];
        m_discArtist = str[1][0];
        m_trackArtist = str[1][iTrackIndex];
    } while (0);


    return true;
}