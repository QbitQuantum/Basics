void CEDPacket::Debug(LPCTSTR pszReason) const
{
#ifdef _DEBUG
	if ( m_nType == ED2K_C2C_SENDINGPART ) return;
	if ( m_nType == ED2K_C2C_HASHSETANSWER ) return;
	if ( m_nType == ED2K_C2C_COMPRESSEDPART ) return;

	CString strOutput;
	strOutput.Format( L"[ED2K]: '%s' %s %s", pszReason, GetType(), (LPCTSTR)ToASCII() );
	CPacket::Debug( strOutput );

#endif
}