void CTag::AssertValid() const
{
	CObject::AssertValid();

	ASSERT( m_uType != 0 );
	ASSERT( m_uName != 0 && m_pszName == NULL || m_uName == 0 && m_pszName != NULL );
	ASSERT( m_pszName == NULL || AtlIsValidString(m_pszName) );
	if (IsStr())
		ASSERT( m_pstrVal != NULL && AtlIsValidString(*m_pstrVal) );
	else if (IsHash())
		ASSERT( m_pData != NULL && AtlIsValidAddress(m_pData, 16) );
	else if (IsBlob())
		ASSERT( m_pData != NULL && AtlIsValidAddress(m_pData, m_nBlobSize) );
}