wxStreamError wxBackingFileImpl::ReadAt(wxFileOffset pos,
                                        void *buffer,
                                        size_t *size)
{
    size_t reqestedSize = *size;
    *size = 0;

    // size1 is the number of bytes it will read directly from the backing
    // file. size2 is any remaining bytes not yet backed, these are returned
    // from the buffer or read from the parent stream.
    size_t size1, size2;

    if (pos + reqestedSize <= m_filelen + size_t(0)) {
        size1 = reqestedSize;
        size2 = 0;
    } else if (pos < m_filelen) {
        size1 = size_t(m_filelen - pos);
        size2 = reqestedSize - size1;
    } else {
        size1 = 0;
        size2 = reqestedSize;
    }

    if (pos < 0)
        return wxSTREAM_READ_ERROR;

    // read the backing file
    if (size1) {
        if (m_file.Seek(pos) == wxBadSeek)
            return wxSTREAM_READ_ERROR;

        ssize_t n = m_file.Read(buffer, size1);
        if (n > 0) {
            *size = n;
            pos += n;
        }

        if (*size < size1)
            return wxSTREAM_READ_ERROR;
    }

    // read from the buffer or parent stream
    if (size2)
    {
        while (*size < reqestedSize)
        {
            // if pos is further ahead than the parent has been read so far,
            // then read forward in the parent stream
            while (pos - m_filelen + size_t(0) >= m_buflen)
            {
                // if the parent is small enough, don't use a backing file
                // just the buffer memory
                if (!m_stream && m_filelen == 0)
                    return m_parenterror;

                // before refilling the buffer write out the current buffer
                // to the backing file if there is anything in it
                if (m_buflen)
                {
                    if (!m_file.IsOpened())
                        if (!wxCreateTempFile(m_prefix, &m_file, &m_filename))
                            return wxSTREAM_READ_ERROR;

                    if (m_file.Seek(m_filelen) == wxBadSeek)
                        return wxSTREAM_READ_ERROR;

                    size_t count = m_file.Write(m_buf, m_buflen);
                    m_filelen += count;

                    if (count < m_buflen) {
                        wxDELETE(m_stream);
                        if (count > 0) {
                            wxDELETEA(m_buf);
                            m_buflen = 0;
                        }
                        m_parenterror = wxSTREAM_READ_ERROR;
                        return m_parenterror;
                    }

                    m_buflen = 0;

                    if (!m_stream) {
                        wxDELETEA(m_buf);
                    }
                }

                if (!m_stream)
                    return m_parenterror;

                // refill buffer
                m_buflen = m_stream->Read(m_buf, m_bufsize).LastRead();

                if (m_buflen < m_bufsize) {
                    m_parenterror = m_stream->GetLastError();
                    if (m_parenterror == wxSTREAM_NO_ERROR)
                        m_parenterror = wxSTREAM_EOF;
                    wxDELETE(m_stream);
                }
            }

            // copy to the user's buffer
            size_t start = size_t(pos - m_filelen);
            size_t len = wxMin(m_buflen - start, reqestedSize - *size);

            memcpy((char*)buffer + *size, m_buf + start, len);
            *size += len;
            pos += len;
        }
    }

    return wxSTREAM_NO_ERROR;
}