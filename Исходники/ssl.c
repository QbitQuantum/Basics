static value cert_load_defaults(){
#if defined(NEKO_WINDOWS)
	value v;
	HCERTSTORE store;
	PCCERT_CONTEXT cert;
	mbedtls_x509_crt *chain = (mbedtls_x509_crt *)alloc(sizeof(mbedtls_x509_crt));
	mbedtls_x509_crt_init( chain );
	if( store = CertOpenSystemStore(0, (LPCSTR)"Root") ){
		cert = NULL;
		while( cert = CertEnumCertificatesInStore(store, cert) )
			mbedtls_x509_crt_parse_der( chain, (unsigned char *)cert->pbCertEncoded, cert->cbCertEncoded );
		CertCloseStore(store, 0);
	}
	v = alloc_abstract(k_cert, chain);
	val_gc(v,free_cert);
	return v;
#elif defined(NEKO_MAC)
	CFMutableDictionaryRef search;
	CFArrayRef result;
	SecKeychainRef keychain;
	SecCertificateRef item;
	CFDataRef dat;
	value v;
	mbedtls_x509_crt *chain = NULL;

	// Load keychain
	if( SecKeychainOpen("/System/Library/Keychains/SystemRootCertificates.keychain",&keychain) != errSecSuccess )
		return val_null;

	// Search for certificates
	search = CFDictionaryCreateMutable( NULL, 0, NULL, NULL );
	CFDictionarySetValue( search, kSecClass, kSecClassCertificate );
	CFDictionarySetValue( search, kSecMatchLimit, kSecMatchLimitAll );
	CFDictionarySetValue( search, kSecReturnRef, kCFBooleanTrue );
	CFDictionarySetValue( search, kSecMatchSearchList, CFArrayCreate(NULL, (const void **)&keychain, 1, NULL) );
	if( SecItemCopyMatching( search, (CFTypeRef *)&result ) == errSecSuccess ){
		CFIndex n = CFArrayGetCount( result );
		for( CFIndex i = 0; i < n; i++ ){
			item = (SecCertificateRef)CFArrayGetValueAtIndex( result, i );

			// Get certificate in DER format
			dat = SecCertificateCopyData( item );
			if( dat ){
				if( chain == NULL ){
					chain = (mbedtls_x509_crt *)alloc(sizeof(mbedtls_x509_crt));
					mbedtls_x509_crt_init( chain );
				}
				mbedtls_x509_crt_parse_der( chain, (unsigned char *)CFDataGetBytePtr(dat), CFDataGetLength(dat) );
				CFRelease( dat );
			}
		}
	}
	CFRelease(keychain);
	if( chain != NULL ){
		v = alloc_abstract(k_cert, chain);
		val_gc(v,free_cert);
		return v;
	}else{
		return val_null;
	}
#else
	return val_null;
#endif
}