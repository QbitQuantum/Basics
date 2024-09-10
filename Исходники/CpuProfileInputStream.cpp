bool CpuProfileInputStream::open(const gtString& path)
{
    if (path.isEmpty())
    {
        return false;
    }

    // Check if file is already open
    if (m_fileStream.isOpened())
    {
        if (path != m_path)
        {
            // Close and open a new file
            close();
        }
        else
        {
            return true;
        }
    }

    // Windows Note:
    // The profile files are opened with UTF-8 encoding.
    //
    if (!m_fileStream.open(path.asCharArray(), WINDOWS_SWITCH(FMODE_TEXT("r, ccs=UTF-8"), FMODE_TEXT("rb"))))
    {
        return false;
    }

    // Set path name
    m_path = path;

#if AMDT_BUILD_TARGET == AMDT_LINUX_OS

    if (fwide(m_fileStream.getHandler(), 1) <= 0)
    {
        close();
        return false;
    }

    // Note: For Linux
    // Due to a bug in some version of gcc,
    // we add this to make sure that we are
    // starting from the beginning of the file.
    m_fileStream.seekCurrentPosition(CrtFile::ORIGIN_BEGIN, 0);
#endif
    getCurrentPosition(&m_bof);

    // Get length of file
    m_fileStream.seekCurrentPosition(CrtFile::ORIGIN_END, 0);
    getCurrentPosition(&m_eof);

    // Back to the beginning of file
    setCurrentPosition(&m_bof);
    return true;
}