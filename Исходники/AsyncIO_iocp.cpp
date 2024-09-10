        virtual result_t process()
        {
            int32_t nError;

            m_DataBuf.len = (DWORD)m_buf.length();
            m_DataBuf.buf = &m_buf[0];
            m_dwFlags = 0;
            sz = sizeof(addr_info);

            if (WSARecvFrom(m_s, &m_DataBuf, 1, NULL, &m_dwFlags,
                            (sockaddr*)&addr_info, &sz, this, NULL) != SOCKET_ERROR)
                return CHECK_ERROR(CALL_E_PENDDING);

            nError = GetLastError();

            if (nError == ERROR_BROKEN_PIPE)
                return CALL_RETURN_NULL;

            if (nError == ERROR_IO_PENDING)
                return CHECK_ERROR(CALL_E_PENDDING);

            return CHECK_ERROR(-nError);
        }