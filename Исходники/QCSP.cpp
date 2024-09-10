QStringList QCSP::containers( SslCertificate::KeyUsage usage )
{
	qWarning() << "Start enumerationg providers";
	QHash<QString,QPair<QString,QString> > certs;
	HCRYPTPROV h = 0;
	DWORD index = 0, type = 0, size = 0;
	while( CryptEnumProvidersW( index, 0, 0, &type, 0, &size ) )
	{
		QString provider( size / sizeof(wchar_t) - 1, 0 );
		if( !CryptEnumProvidersW( index++, 0, 0, &type, LPWSTR(provider.data()), &size ) )
			continue;

		qWarning() << "Found provider" << provider << "type" << type;
		if( type != PROV_RSA_FULL )
			continue;

		// its broken and does not play well with pkcs11
		if( provider.toLower().contains( "esteid" ) )
			continue;

		qWarning() << "Acquiring provider" << provider << "context";
		if( h )
			CryptReleaseContext( h, 0 );
		h = 0;
		if( !CryptAcquireContextW( &h, 0, LPCWSTR(provider.utf16()), type, CRYPT_SILENT ) )
			continue;

		qWarning() << "Checking if provider" << provider << "is HW";
		QByteArray imptype = QCSPPrivate::provParam( h, PP_IMPTYPE );
		if( imptype.isEmpty() || !(imptype[0] & CRYPT_IMPL_HARDWARE) )
			continue;

		qWarning() << "Enumerating provider " << provider << "containers";
		QStringList containers;
		QByteArray container = QCSPPrivate::provParam( h, PP_ENUMCONTAINERS, CRYPT_FIRST );
		while( !container.isEmpty() )
		{
			containers << container;
			container = QCSPPrivate::provParam( h, PP_ENUMCONTAINERS, CRYPT_NEXT );
		}
		qWarning() << "Provider" << provider << "containers" << containers;

		Q_FOREACH( const QString &container, containers )
		{
			if( h )
				CryptReleaseContext( h, 0 );
			h = 0;
			qWarning() << "Acquiring provider" << provider << "container" << container << "context";
			if( !CryptAcquireContextW( &h, LPCWSTR(container.utf16()), LPCWSTR(provider.utf16()), type, CRYPT_SILENT ) )
				continue;

			qWarning() << "Geting provider" << provider << "container" << container << "key";
			HCRYPTKEY key = 0;
			if( !CryptGetUserKey( h, usage == SslCertificate::NonRepudiation ? AT_SIGNATURE : AT_KEYEXCHANGE, &key ) )
				continue;

			qWarning() << "Reading provider" << provider << "container" << container << "cert";
			QSslCertificate cert( QCSPPrivate::keyParam( key, KP_CERTIFICATE, 0 ), QSsl::Der );
			CryptDestroyKey( key );

			if( cert.isNull() )
				continue;

			qWarning() << "Adding provider" << provider << "container" << container << "list";
			certs.insert( cert.subjectInfo( QSslCertificate::CommonName ), QPair<QString,QString>( provider, container ) );
		}
	}
	if( h )
		CryptReleaseContext( h, 0 );
	qWarning() << "End enumerationg providers";

	d->certs = certs;
	return d->certs.keys();
}