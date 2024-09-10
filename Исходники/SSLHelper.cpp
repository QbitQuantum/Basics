CSSLSession* CSSLSession::Renew(const CSSLContext& sslCtx, LPCSTR lpszHostName)
{
	ASSERT(!IsValid());

	m_ssl		= SSL_new(sslCtx.GetDefaultContext());
	m_bioSend	= BIO_new(BIO_s_mem());
	m_bioRecv	= BIO_new(BIO_s_mem());

	SSL_set_bio(m_ssl, m_bioRecv, m_bioSend);

	if(sslCtx.GetSessionMode() == SSL_SM_SERVER)
		SSL_accept(m_ssl);
	else
	{
		USES_CONVERSION;

		if(lpszHostName && lpszHostName[0] != 0 && !::IsIPAddress(A2CT(lpszHostName)))
			SSL_set_tlsext_host_name(m_ssl, lpszHostName);

		SSL_connect(m_ssl);
	}

	m_pitSend		= m_itPool.PickFreeItem();
	m_pitRecv		= m_itPool.PickFreeItem();
	m_bufSend.buf	= (char*)m_pitSend->Ptr();
	m_bufRecv.buf	= (char*)m_pitRecv->Ptr();
	m_enStatus		= SSL_HSS_PROC;

	return this;
}