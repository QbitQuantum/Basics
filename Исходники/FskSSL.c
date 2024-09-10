Boolean FskSSLCheckServerCert(SSL *ssl, char *hostname) {
	long err;
	X509 *peer;
	char peer_CN[256];
	err = SSL_get_verify_result(ssl);
#if 0
	if ((err != X509_V_OK)
		&& (err != X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT)
		&& (err != X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY)) {
		ERR_print_errors_fp(stderr);
fprintf(stderr, "[%s] cert for %s didn't verify %d %s\n", threadTag(FskThreadGetCurrent()), hostname, err, X509_verify_cert_error_string(err));
#else
	if (err != X509_V_OK) {
		if ((NULL != FskStrStr(hostname, "google.com")) 
			|| (NULL != FskStrStr(hostname, "googleapis.com")) 
			|| (NULL != FskStrStr(hostname, "twitter.com"))
			|| (NULL != FskStrStr(hostname, "yammer.com"))
			|| (NULL != FskStrStr(hostname, "facebook.com"))
			|| (NULL != FskStrStr(hostname, "foursquare.com"))
			|| (NULL != FskStrStr(hostname, "akamaihd.net"))
			|| (NULL != FskStrStr(hostname, "fbcdn.net"))
			|| (NULL != FskStrStr(hostname, "radiotime.com"))
			|| (NULL != FskStrStr(hostname, "s3.amazonaws.com"))
			|| (NULL != FskStrStr(hostname, "orb.com"))) {
			if ((err != X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT)
				&& (err != X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY)) {
				return false;
			}
			myprintf((stderr, "b) cert didn't verify because %d %s\n", err, X509_verify_cert_error_string(err)));
			myprintf((stderr, " but since it's %s we'll let it through\n", hostname));
		}
		else {
#endif
			return false;
		}
	}

	peer = SSL_get_peer_certificate(ssl);
	X509_NAME_get_text_by_NID(X509_get_subject_name(peer), NID_commonName,
						peer_CN, 256);
//fprintf(stderr, "comparing peer_CN %s with hostname %s\n", peer_CN, hostname);
	if (FskStrCompareCaseInsensitive(peer_CN, hostname)) {
		int pos, L, subL;
		char *match = peer_CN + 1;

		subL = FskStrLen(match);
		L = FskStrLen(hostname);
		if (peer_CN[0] == '*') {
			pos = L - subL;
			if (0 == FskStrCompareCaseInsensitive(match, hostname + pos)) {
//fprintf(stderr, "Matched wildcard %s and %s\n", match, hostname + pos);
				return true;
			}
		}

		if (	(FskStrEndsWith(match, "akamaihd.net")
				&& FskStrEndsWith(hostname, "akamai.net")) 
			||	(FskStrEndsWith(match, "akamai.net")
				&& FskStrEndsWith(hostname, "akamaihd.net")) ) {
			return true;
		}
			
	

		myprintf((stderr, "cert common name %s and host %s don't match\n", peer_CN, hostname));
		return false;
	}

	return true;
}

//SSL_CTX *FskSSLInitialize(char *keyfile, char *password)
static SSL_CTX *FskOpenSSLInitialize(const char *calistpath)
{
	SSL_METHOD	*method;
	SSL_CTX		*context;

	if (gSSLContext) {
		return gSSLContext;
	}
	else {
		SSL_library_init();
		SSL_load_error_strings();			// not necessary, but useful
	}

	method = SSLv23_method();
	context = SSL_CTX_new(method);

#if 0
	if (FskStrLen(keyfile) > 0) {
		keyfile = FskEnvironmentDoApply(FskStrDoCopy(keyfile));
		if (!SSL_CTX_use_certificate_chain_file(context, keyfile))
			doSSLError("Can't read certificate file");
		fprintf(stderr, "keyfile is %s\n", keyfile);

		if (FskStrLen(password) > 0) {
			gSSLPassword = FskStrDoCopy(password);
			SSL_CTX_set_default_passwd_cb(context, passwordCallback);
			if (!SSL_CTX_use_PrivateKey_file(context, keyfile, SSL_FILETYPE_PEM))
				doSSLError( "Can't read private keyfile");
		}

		FskMemPtrDispose(keyfile);
	}
#endif

#if TARGET_OS_WIN32
	{
	// try to make the path 8.3 safe to avoid nightmares with multibyte character paths, etc.
	UInt16 *nativePath;

	if (kFskErrNone == FskFilePathToNative(calistpath, (char **)&nativePath)) {
		DWORD shortLen;

		shortLen = GetShortPathNameW(nativePath, NULL, 0);
		if (0 != shortLen) {
			UInt16 *eightDotThree;

			if (kFskErrNone == FskMemPtrNewClear(shortLen * 2, (FskMemPtr *)&eightDotThree)) {
				if (0 != GetShortPathNameW(nativePath, eightDotThree, shortLen)) {
					char *utf8;
					UInt32 utf8Len;

					if (kFskErrNone == FskTextUnicode16LEToUTF8(eightDotThree, shortLen * 2, &utf8, &utf8Len)) {
						char *enc;

						if (kFskErrNone == FskTextToPlatform(utf8, utf8Len, &enc, NULL)) {
							FskMemPtrDispose(calistpath);
							calistpath = enc;
						}
						FskMemPtrDispose(utf8);
					}
				}
				FskMemPtrDispose(eightDotThree);
			}
		}
		FskMemPtrDispose(nativePath);
	}
	}
#endif

	if (!(SSL_CTX_load_verify_locations(context, calistpath, 0))) {
		doSSLError("Can't read default CA list");
	}

	SSL_CTX_set_verify_depth(context, 0);

//	SSL_CTX_set_verify(context, SSL_VERIFY_PEER, 0);

	gSSLContext = context;

	return context;
}