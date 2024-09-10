bool CMinizip::Extract(LPCTSTR FileName, LPCTSTR DestPath, UINT BufSize)
{
    USES_CONVERSION;
    if (unzLocateFile(m_ZipFile, T2CA(FileName), 0) != UNZ_OK)
        return(FALSE);
    if (unzOpenCurrentFile(m_ZipFile) != UNZ_OK)
        return(FALSE);
    CByteArray	ba;
    ba.SetSize(BufSize);
    bool	retc = FALSE;	// assume failure
    TRY {
        CFile	DestFile(DestPath, CFile::modeCreate | CFile::modeWrite);
        int	BytesRead;
        while ((BytesRead = unzReadCurrentFile(m_ZipFile, ba.GetData(), BufSize)) > 0) {
            DestFile.Write(ba.GetData(), BytesRead);
        }
        if (!BytesRead)	// if EOF
            retc = TRUE;	// success provided current file closes OK
    }
    CATCH (CFileException, e) {
        e->ReportError();
    }
    END_CATCH
    if (unzCloseCurrentFile(m_ZipFile) != UNZ_OK)	// close fails if bad CRC
        return(FALSE);
    return(retc);
}