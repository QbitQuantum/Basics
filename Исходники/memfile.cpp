void CMemFile::Write( const void *lpBuf, UINT nCount )
/****************************************************/
{
    if( m_nPosition + nCount >= m_nFileSize ) {
        m_nFileSize = m_nPosition + nCount;
        GrowFile( m_nFileSize );
    }
    Memcpy( m_lpBuffer + m_nPosition, (const BYTE *)lpBuf, nCount );
    m_nPosition += nCount;
}