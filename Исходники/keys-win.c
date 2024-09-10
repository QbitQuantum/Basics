/**
 * gnutls_system_key_add_x509:
 * @crt: the certificate to be added
 * @privkey: the key to be added
 * @label: the friendly name to describe the key
 * @cert_url: if non-NULL it will contain an allocated value with the certificate URL
 * @key_url: if non-NULL it will contain an allocated value with the key URL
 *
 * This function will added the given key and certificate pair,
 * to the system list.
 *
 * Returns: On success, %GNUTLS_E_SUCCESS (0) is returned, otherwise a
 *   negative error value.
 *
 * Since: 3.4.0
 **/
int gnutls_system_key_add_x509(gnutls_x509_crt_t crt,
			       gnutls_x509_privkey_t privkey, const char *label,
			       char **cert_url, char **key_url)
{
	HCERTSTORE store = NULL;
	CRYPT_DATA_BLOB pfx;
	gnutls_datum_t _pfx = { NULL, 0 };
	gnutls_pkcs12_t p12 = NULL;
	gnutls_pkcs12_bag_t bag1 = NULL, bag2 = NULL;
	uint8_t id[MAX_WID_SIZE];
	size_t id_size;
	gnutls_datum_t kid;
	int ret;

	if (ncrypt_init == 0)
		return gnutls_assert_val(GNUTLS_E_UNIMPLEMENTED_FEATURE);

	if (label == NULL)
		return gnutls_assert_val(GNUTLS_E_INVALID_REQUEST);

	id_size = sizeof(id);
	ret = gnutls_x509_crt_get_key_id(crt, 0, id, &id_size);
	if (ret < 0)
		return gnutls_assert_val(ret);

	kid.data = id;
	kid.size = id_size;

	/* the idea: import the cert and private key into PKCS #12
	 * format, export it into pfx, and import it into store */
	ret = gnutls_pkcs12_init(&p12);
	if (ret < 0)
		return gnutls_assert_val(ret);

	ret = gnutls_pkcs12_bag_init(&bag1);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = gnutls_pkcs12_bag_set_crt(bag1, crt);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = gnutls_pkcs12_bag_set_key_id(bag1, 0, &kid);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	if (label)
		gnutls_pkcs12_bag_set_friendly_name(bag1, 0, label);

	ret = gnutls_pkcs12_bag_init(&bag2);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = gnutls_pkcs12_bag_set_privkey(bag2, privkey, NULL, 0);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = gnutls_pkcs12_bag_set_key_id(bag2, 0, &kid);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	if (label)
		gnutls_pkcs12_bag_set_friendly_name(bag2, 0, label);

	ret = gnutls_pkcs12_set_bag(p12, bag1);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = gnutls_pkcs12_set_bag(p12, bag2);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = gnutls_pkcs12_generate_mac(p12, "123456");
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	ret = gnutls_pkcs12_export2(p12, GNUTLS_X509_FMT_DER, &_pfx);
	if (ret < 0) {
		gnutls_assert();
		goto cleanup;
	}

	pfx.cbData = _pfx.size;
	pfx.pbData = _pfx.data;

	store = PFXImportCertStore(&pfx, L"123456", 0);
	if (store == NULL) {
		gnutls_assert();
		ret = GNUTLS_E_INVALID_REQUEST;
		goto cleanup;
	}

	if (cert_url || key_url) {
		unsigned char sha[20];
		CRYPT_HASH_BLOB blob;
		const CERT_CONTEXT *cert = NULL;
		gnutls_datum_t data;

		ret = gnutls_x509_crt_export2(crt, GNUTLS_X509_FMT_DER, &data);
		if (ret < 0) {
			gnutls_assert();
			goto cleanup;
		}

		ret =
		    gnutls_hash_fast(GNUTLS_DIG_SHA1, data.data, data.size,
				     sha);
		gnutls_free(data.data);
		if (ret < 0) {
			gnutls_assert();
			goto cleanup;
		}

		blob.cbData = sizeof(sha);
		blob.pbData = sha;

		cert = CertFindCertificateInStore(store,
						  X509_ASN_ENCODING,
						  0,
						  CERT_FIND_SHA1_HASH,
						  &blob, NULL);

		if (cert == NULL) {
			gnutls_assert();
			ret = GNUTLS_E_KEY_IMPORT_FAILED;
			goto cleanup;
		}

		ret = get_win_urls(cert, cert_url, key_url, NULL, NULL);
		if (ret < 0) {
			gnutls_assert();
			goto cleanup;
		}
	}

	ret = 0;

 cleanup:
	if (p12 != NULL)
		gnutls_pkcs12_deinit(p12);
	if (bag1 != NULL)
		gnutls_pkcs12_bag_deinit(bag1);
	if (bag2 != NULL)
		gnutls_pkcs12_bag_deinit(bag2);
	if (store != NULL)
		CertCloseStore(store, 0);
	gnutls_free(_pfx.data);
	return ret;
}