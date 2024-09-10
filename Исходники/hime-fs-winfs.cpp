        void WinNode::stat_impl(NodeStat& dst)
        {
            WIN32_FILE_ATTRIBUTE_DATA attrs = { 0 };
            GetFileAttributesExW(m_nativePath.c_str(), GetFileExInfoStandard, &attrs);

            filetimeToUint64(dst.ctime, attrs.ftCreationTime);
            filetimeToUint64(dst.mtime, attrs.ftLastWriteTime);
            filetimeToUint64(dst.atime, attrs.ftLastAccessTime);

            dst.id = m_id;
            dst.size = ((uint64)attrs.nFileSizeHigh << 32) | attrs.nFileSizeLow;
        }