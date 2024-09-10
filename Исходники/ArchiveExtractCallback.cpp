        void ArchiveExtractCallback::GetPropertyFilePath(UInt32 index)
        {
            CPropVariant prop;
            HRESULT hr = m_archiveHandler->GetProperty(index, kpidPath, &prop);
            if (hr != S_OK)
            {
                _com_issue_error(hr);
            }

            if ( prop.vt == VT_EMPTY )
            {
                m_relPath = EmptyFileAlias;
            }
            else if (prop.vt != VT_BSTR)
            {
                _com_issue_error(E_FAIL);
            }
            else
            {
                _bstr_t bstr = prop.bstrVal;
#ifdef _UNICODE
                m_relPath = bstr;
#else
                char relPath[MAX_PATH];
                int size = WideCharToMultiByte(CP_UTF8, 0, bstr, bstr.length(), relPath, MAX_PATH, NULL, NULL);
                m_relPath.assign(relPath, size);
#endif
            }
        }