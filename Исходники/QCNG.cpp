QList<TokenData> QCNG::tokens() const
{
	qWarning() << "Start enumerationg providers";
	QHash<SslCertificate,QCNGCache> cache;
	DWORD count = 0;
	NCryptProviderName *names = nullptr;
	NCryptEnumStorageProviders( &count, &names, NCRYPT_SILENT_FLAG );
	for( DWORD i = 0; i < count; ++i )
	{
		qWarning() << "Found provider" << QString::fromWCharArray(names[i].pszName);
		if( wcscmp( names[i].pszName, MS_SMART_CARD_KEY_STORAGE_PROVIDER ) == 0 )
		{
			for( const QString &reader: QPCSC::instance().readers() )
			{
				qWarning() << reader;
				QString scope = QString(R"(\\.\%1\)").arg(reader);
				d->enumKeys( cache, names[i].pszName, LPCWSTR(scope.utf16()) );
			}
		}
		else
			d->enumKeys( cache, names[i].pszName );
	}
	NCryptFreeBuffer( names );
	d->cache = cache;
	qWarning() << "End enumerationg providers";

	QList<TokenData> result;
	for(QHash<SslCertificate,QCNGCache>::const_iterator i = cache.constBegin(); i != cache.constEnd(); ++i)
	{
		TokenData t;
		t.setCard(i.key().type() & SslCertificate::EstEidType || i.key().type() & SslCertificate::DigiIDType ?
			i.value().guid : i.key().subjectInfo(QSslCertificate::CommonName));
		t.setCert(i.key());
		result << t;
	}
	return result;
}

TokenData QCNG::selectCert( const SslCertificate &cert )
{
	qWarning() << "Select:" << cert.subjectInfo( "CN" );
	if( !d->cache.contains( cert ) )
		return TokenData();

	d->selected = d->cache[cert];
	qWarning() << "Found:" << d->selected.guid << d->selected.key;
	TokenData t;
	t.setCard( cert.type() & SslCertificate::EstEidType || cert.type() & SslCertificate::DigiIDType ?
		d->selected.guid : cert.subjectInfo( QSslCertificate::CommonName ) );
	t.setCert( cert );

	return t;
}

QByteArray QCNG::sign( int method, const QByteArray &digest ) const
{
	d->err = PinUnknown;
	BCRYPT_PKCS1_PADDING_INFO padInfo = { NCRYPT_SHA256_ALGORITHM };
	switch( method )
	{
	case NID_sha224: padInfo.pszAlgId = L"SHA224"; break;
	case NID_sha256: padInfo.pszAlgId = NCRYPT_SHA256_ALGORITHM; break;
	case NID_sha384: padInfo.pszAlgId = NCRYPT_SHA384_ALGORITHM; break;
	case NID_sha512: padInfo.pszAlgId = NCRYPT_SHA512_ALGORITHM; break;
	case NID_md5_sha1: //padInfo.pszAlgId = L"SHAMD5"; break;
	default: break;
	}

	DWORD size = 0;
	QByteArray res;
	NCRYPT_KEY_HANDLE k = d->key();
	QString algo(5, 0);
	SECURITY_STATUS err = NCryptGetProperty(k, NCRYPT_ALGORITHM_GROUP_PROPERTY, PBYTE(algo.data()), DWORD((algo.size() + 1) * 2), &size, 0);
	algo.resize(size/2 - 1);
	bool isRSA = algo == "RSA";
	err = NCryptSignHash(k, isRSA ? &padInfo : nullptr, PBYTE(digest.constData()), DWORD(digest.size()),
		nullptr, 0, &size, isRSA ? BCRYPT_PAD_PKCS1 : 0);
	if(FAILED(err))
		return res;
	res.resize(int(size));
	err = NCryptSignHash(k, isRSA ? &padInfo : nullptr, PBYTE(digest.constData()), DWORD(digest.size()),
		PBYTE(res.data()), DWORD(res.size()), &size, isRSA ? BCRYPT_PAD_PKCS1 : 0);
	NCryptFreeObject( k );
	switch( err )
	{
	case ERROR_SUCCESS:
		d->err = PinOK;
		return res;
	case SCARD_W_CANCELLED_BY_USER:
		d->err = PinCanceled; break;
	default:
		res.clear();
		break;
	}
	return res;
}