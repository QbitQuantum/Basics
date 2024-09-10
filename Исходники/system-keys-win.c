/*-
 * _gnutls_privkey_import_system:
 * @pkey: The private key
 * @url: The URL of the key
 *
 * This function will import the given private key to the abstract
 * #gnutls_privkey_t type. 
 *
 * Returns: On success, %GNUTLS_E_SUCCESS (0) is returned, otherwise a
 *   negative error value.
 *
 * Since: 3.4.0
 *
 -*/
int
_gnutls_privkey_import_system_url(gnutls_privkey_t pkey,
			          const char *url)
{
	uint8_t id[MAX_WID_SIZE];
	HCERTSTORE store = NULL;
	size_t id_size;
	const CERT_CONTEXT *cert = NULL;
	CRYPT_HASH_BLOB blob;
	CRYPT_KEY_PROV_INFO *kpi = NULL;
	NCRYPT_KEY_HANDLE nc = NULL;
	NCRYPT_PROV_HANDLE sctx = NULL;
	DWORD kpi_size;
	SECURITY_STATUS r;
	int ret, enc_too = 0;
	WCHAR algo_str[64];
	DWORD algo_str_size = 0;
	priv_st *priv;

	if (ncrypt_init == 0)
		return gnutls_assert_val(GNUTLS_E_UNIMPLEMENTED_FEATURE);

	if (url == NULL)
		return gnutls_assert_val(GNUTLS_E_INVALID_REQUEST);

	priv = gnutls_calloc(1, sizeof(*priv));
	if (priv == NULL)
		return gnutls_assert_val(GNUTLS_E_MEMORY_ERROR);

	id_size = sizeof(id);
	ret = get_id(url, id, &id_size, 0);
	if (ret < 0)
		return gnutls_assert_val(ret);

	blob.cbData = id_size;
	blob.pbData = id;

	store = CertOpenSystemStore(0, "MY");
	if (store == NULL) {
		gnutls_assert();
		ret = GNUTLS_E_FILE_ERROR;
		goto cleanup;
	}

	cert = CertFindCertificateInStore(store,
				X509_ASN_ENCODING,
				0,
				CERT_FIND_KEY_IDENTIFIER,
				&blob,
				NULL);

	if (cert == NULL) {
		char buf[64];
		_gnutls_debug_log("cannot find ID: %s from %s\n",
			      _gnutls_bin2hex(id, id_size,
					      buf, sizeof(buf), NULL),
				url);
		ret = gnutls_assert_val(GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE);
		goto cleanup;
	}

	kpi_size = 0;
	r = CertGetCertificateContextProperty(cert, CERT_KEY_PROV_INFO_PROP_ID,
					      NULL, &kpi_size);
	if (r == 0) {
		_gnutls_debug_log("error in getting context: %d from %s\n",
			      	  (int)GetLastError(), url);
		ret = gnutls_assert_val(GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE);
		goto cleanup;
	}

	kpi = gnutls_malloc(kpi_size);
	if (kpi == NULL) {
		gnutls_assert();
		ret = GNUTLS_E_MEMORY_ERROR;
		goto cleanup;
	}

	r = CertGetCertificateContextProperty(cert, CERT_KEY_PROV_INFO_PROP_ID,
					      kpi, &kpi_size);
	if (r == 0) {
		_gnutls_debug_log("error in getting context: %d from %s\n",
			      	  (int)GetLastError(), url);
		ret = gnutls_assert_val(GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE);
		goto cleanup;
	}

	r = pNCryptOpenStorageProvider(&sctx, kpi->pwszProvName, 0);
	if (FAILED(r)) {
		ret = gnutls_assert_val(GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE);
		goto cleanup;
	}

	r = pNCryptOpenKey(sctx, &nc, kpi->pwszContainerName, 0, 0);
	if (FAILED(r)) {
		ret = gnutls_assert_val(GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE);
		goto cleanup;
	}

	r = pNCryptGetProperty(nc, NCRYPT_ALGORITHM_PROPERTY,
				(BYTE*)algo_str, sizeof(algo_str),
				&algo_str_size, 0);
	if (FAILED(r)) {
		ret = gnutls_assert_val(GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE);
		goto cleanup;
	}

	if (StrCmpW(algo_str, BCRYPT_RSA_ALGORITHM) == 0) {
		priv->pk = GNUTLS_PK_RSA;
		priv->sign_algo = GNUTLS_SIGN_RSA_SHA256;
		enc_too = 1;
	} else if (StrCmpW(algo_str, BCRYPT_DSA_ALGORITHM) == 0) {
		priv->pk = GNUTLS_PK_DSA;
		priv->sign_algo = GNUTLS_SIGN_DSA_SHA1;
	} else if (StrCmpW(algo_str, BCRYPT_ECDSA_P256_ALGORITHM) == 0) {
		priv->pk = GNUTLS_PK_EC;
		priv->sign_algo = GNUTLS_SIGN_ECDSA_SHA256;
	} else if (StrCmpW(algo_str, BCRYPT_ECDSA_P384_ALGORITHM) == 0) {
		priv->pk = GNUTLS_PK_EC;
		priv->sign_algo = GNUTLS_SIGN_ECDSA_SHA384;
	} else if (StrCmpW(algo_str, BCRYPT_ECDSA_P521_ALGORITHM) == 0) {
		priv->pk = GNUTLS_PK_EC;
		priv->sign_algo = GNUTLS_SIGN_ECDSA_SHA512;
	} else {
		_gnutls_debug_log("unknown key algorithm: %ls\n", algo_str);
		ret = gnutls_assert_val(GNUTLS_E_UNKNOWN_PK_ALGORITHM);
		goto cleanup;
	}
	priv->nc = nc;

	ret = gnutls_privkey_import_ext3(pkey, priv, cng_sign,
					 (enc_too!=0)?cng_decrypt:NULL,
					 cng_deinit,
					 cng_info, 0);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = 0;
 cleanup:
	if (ret < 0) {
		if (nc != 0)
			pNCryptFreeObject(nc);
		gnutls_free(priv);
	}
	if (sctx != 0)
		pNCryptFreeObject(sctx);

	gnutls_free(kpi);
	CertCloseStore(store, 0);
	return ret;
}