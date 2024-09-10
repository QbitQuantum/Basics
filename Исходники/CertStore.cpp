bool CertStore::remove( const QSslCertificate &cert )
{
	if( !d->s )
		return false;

	PCCERT_CONTEXT context = d->certContext( cert );
	if( !context )
		return false;
	bool result = false;
	PCCERT_CONTEXT scontext = 0;
	while( (scontext = CertEnumCertificatesInStore( d->s, scontext )) )
	{
		if( CertCompareCertificate( X509_ASN_ENCODING,
				context->pCertInfo, scontext->pCertInfo ) )
			result = CertDeleteCertificateFromStore( CertDuplicateCertificateContext( scontext ) );
	}
	CertFreeCertificateContext( context );
	return result;
}