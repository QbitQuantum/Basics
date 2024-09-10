void Utf8_16_Read::determineEncoding()
{
	INT uniTest = IS_TEXT_UNICODE_STATISTICS;
	m_eEncoding = uni8Bit;
	m_nSkip = 0;

    // detect UTF-16 big-endian with BOM
	if (m_nLen > 1 && m_pBuf[0] == k_Boms[uni16BE][0] && m_pBuf[1] == k_Boms[uni16BE][1])
	{
		m_eEncoding = uni16BE;
		m_nSkip = 2;
	}
    // detect UTF-16 little-endian with BOM
	else if (m_nLen > 1 && m_pBuf[0] == k_Boms[uni16LE][0] && m_pBuf[1] == k_Boms[uni16LE][1])
	{
		m_eEncoding = uni16LE;
		m_nSkip = 2;
	}
    // detect UTF-8 with BOM
	else if (m_nLen > 2 && m_pBuf[0] == k_Boms[uniUTF8][0] && 
		m_pBuf[1] == k_Boms[uniUTF8][1] && m_pBuf[2] == k_Boms[uniUTF8][2])
	{
		m_eEncoding = uniUTF8;
		m_nSkip = 3;
	}
	// try to detect UTF-16 little-endian without BOM
	else if (m_nLen > 1 && m_nLen % 2 == 0 && m_pBuf[0] != NULL && m_pBuf[1] == NULL && IsTextUnicode(m_pBuf, m_nLen, &uniTest))
	{
		m_eEncoding = uni16LE_NoBOM;
		m_nSkip = 0;
	}
	/* UTF-16 big-endian without BOM detection is taken away scince this detection is very week
    // try to detect UTF-16 big-endian without BOM
    else if (m_nLen > 1 && m_pBuf[0] == NULL && m_pBuf[1] != NULL)
	{
		m_eEncoding = uni16BE_NoBOM;
		m_nSkip = 0;
	}
	*/
	else
	{
		u78 detectedEncoding = utf8_7bits_8bits();
		if (detectedEncoding == utf8NoBOM)
			m_eEncoding = uniCookie;
		else if (detectedEncoding == ascii7bits)
			m_eEncoding = uni7Bit;
		else //(detectedEncoding == ascii8bits)
			m_eEncoding = uni8Bit;
		m_nSkip = 0;
	}
}