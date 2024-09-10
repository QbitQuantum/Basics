bool CVobFile::GetTitleInfo(LPCTSTR fn, ULONG nTitleNum, ULONG& VTSN, ULONG& TTN)
{
    CFile ifoFile;
    if (!ifoFile.Open(fn, CFile::modeRead | CFile::typeBinary | CFile::shareDenyNone)) {
        return false;
    }

    char hdr[IFO_HEADER_SIZE + 1];
    ifoFile.Read(hdr, IFO_HEADER_SIZE);
    hdr[IFO_HEADER_SIZE] = '\0';
    if (strcmp(hdr, VIDEO_TS_HEADER)) {
        return false;
    }

    ifoFile.Seek(0xC4, CFile::begin);
    DWORD TT_SRPTPosition; // Read a 32-bit unsigned big-endian integer
    ifoFile.Read(&TT_SRPTPosition, sizeof(TT_SRPTPosition));
    TT_SRPTPosition = _byteswap_ulong(TT_SRPTPosition);
    TT_SRPTPosition *= 2048;
    ifoFile.Seek(TT_SRPTPosition + 8 + (nTitleNum - 1) * 12 + 6, CFile::begin);
    BYTE tmp;
    ifoFile.Read(&tmp, sizeof(tmp));
    VTSN = tmp;
    ifoFile.Read(&tmp, sizeof(tmp));
    TTN = tmp;

    ifoFile.Close();

    return true;
}