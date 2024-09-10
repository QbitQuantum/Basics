        size_t File::SizeBytes(void)
        {
            #ifdef HT_SYS_LINUX
                //Need to grab size from stat struct in order to allow for
                //files > 2GB in size
                struct stat st;
                stat(m_path.c_str(), &st);
                m_size = st.st_size;
            #else
                WIN32_FILE_ATTRIBUTE_DATA fad;
                if (!GetFileAttributesExA(m_path.c_str(), GetFileExInfoStandard, &fad))
                    return -1;

                LARGE_INTEGER size;
                size.HighPart = fad.nFileSizeHigh;
                size.LowPart = fad.nFileSizeLow;

                m_size = static_cast<size_t>(size.QuadPart);
            #endif

            return m_size;
        }