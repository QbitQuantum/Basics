    /// @brief 获取图像数据
    bool GetImage(IN unsigned int startIndex, IN unsigned int imageNum, OUT unsigned char* pBuffer) const
    {
        if (0 == m_pFile || 0 == m_imageNum || 0 == m_imageRow || 0 == m_imageCol)
            return false;

        unsigned int imageSize = m_imageRow * m_imageCol;
        unsigned int offset = IMAGE_FILE_HEADER_SIZE + startIndex * imageSize;
        fseek(m_pFile, offset, SEEK_SET);
        size_t count = fread_s(pBuffer, imageSize * imageNum, imageSize, imageNum, m_pFile);
        if (count != imageNum)
            return false;

        return true;
    }