void
CSharedSecret::Commit( CString zone )
{
	char	zoneUTF8[ 256 ];
	char	keyUTF8[ 256 ];
	char	secretUTF8[ 256 ];

	StringObjectToUTF8String( zone, zoneUTF8, sizeof( zoneUTF8 ) );
	StringObjectToUTF8String( m_key, keyUTF8, sizeof( keyUTF8 ) );
	StringObjectToUTF8String( m_secret, secretUTF8, sizeof( secretUTF8 ) );

	LsaSetSecret( zoneUTF8, keyUTF8, secretUTF8 );
}