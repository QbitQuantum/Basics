void openssl_x509_info()
{
	FILE *fp;
	wchar_t *pUtf8;
	X509 *x509Cert;
	long Nid, Version;
	ASN1_INTEGER *Serial;
	X509_NAME *issuer, *subject;
	X509_NAME_ENTRY *name_entry;
	ASN1_TIME *timea, *timeb;
	char msginfo[MAX1_LEN];
	const unsigned char *uCert;
	unsigned char tmp[MAX4_LEN];
	int certLen, i, eNum, msgLen, nUtf8;

	OpenSSL_add_all_algorithms();
	printf("\nX509_Issuer info:\n");

	fp = fopen(U2CERTF, "rb");
	certLen = fread(tmp, 1, 4096, fp);
	fclose(fp);
	uCert = tmp;
	x509Cert = d2i_X509(NULL, &uCert, certLen);
	Version = X509_get_version(x509Cert);
	printf("\tX509 Version: %ld\n", Version);

	Serial = X509_get_serialNumber(x509Cert);
	printf("\tserialNumber is: ");
	for (i = 0; i < Serial->length; i++)
		printf("%02x", Serial->data[i]);
	printf("\n");

	issuer = X509_get_issuer_name(x509Cert);
	eNum = sk_X509_NAME_ENTRY_num(issuer->entries);
	for (i = 0; i < eNum; i++) {
		name_entry = sk_X509_NAME_ENTRY_value(issuer->entries, i);
		if (name_entry->value->type == V_ASN1_UTF8STRING) {
			nUtf8 = 2 * name_entry->value->length;
			pUtf8 = (wchar_t *) malloc(nUtf8);
			if (pUtf8 == NULL)
				return;
			memset(pUtf8, 0, nUtf8);
			mbstowcs(pUtf8, (char *)name_entry->value->data,
					 name_entry->value->length);
			wcstombs(msginfo, pUtf8, nUtf8);
			msgLen = nUtf8;
			msginfo[msgLen] = '\0';
			free(pUtf8);
			pUtf8 = NULL;
		} else {
			msgLen = name_entry->value->length;
			memcpy(msginfo, name_entry->value->data, msgLen);
			msginfo[msgLen] = '\0';
		}

		Nid = OBJ_obj2nid(name_entry->object);
		switch (Nid) {
		case NID_countryName:
			printf("\tissuer's countryName: %s\n", msginfo);
			break;

		case NID_stateOrProvinceName:
			printf("\tissuer's provinceName: %s\n", msginfo);
			break;

		case NID_localityName:
			printf("\tissuer's localityName: %s\n", msginfo);
			break;

		case NID_organizationName:
			printf("\tissuer's organizationName: %s\n", msginfo);
			break;

		case NID_organizationalUnitName:
			printf("\tissuer's organizationalUnitName: %s\n", msginfo);
			break;

		case NID_commonName:
			printf("\tissuer's commonName: %s\n", msginfo);
			break;

		case NID_pkcs9_emailAddress:
			printf("\tissuer's emailAddress: %s\n", msginfo);
			break;

		default:
			break;
		}
	}

	subject = X509_get_subject_name(x509Cert);
	eNum = sk_X509_NAME_ENTRY_num(subject->entries);
	for (i = 0; i < eNum; i++) {
		name_entry = sk_X509_NAME_ENTRY_value(subject->entries, i);
		if (name_entry->value->type == V_ASN1_UTF8STRING) {
			nUtf8 = 2 * name_entry->value->length;
			pUtf8 = (wchar_t *) malloc(nUtf8);
			if (pUtf8 == NULL)
				return;
			memset(pUtf8, 0, nUtf8);
			mbstowcs(pUtf8, (char *)name_entry->value->data,
					 name_entry->value->length);
			wcstombs(msginfo, pUtf8, nUtf8);
			msgLen = nUtf8;
			msginfo[msgLen] = '\0';
			free(pUtf8);
			pUtf8 = NULL;
		} else {
			msgLen = name_entry->value->length;
			memcpy(msginfo, name_entry->value->data, msgLen);
			msginfo[msgLen] = '\0';
		}

		Nid = OBJ_obj2nid(name_entry->object);
		switch (Nid) {
		case NID_countryName:
			printf("\tsubject's countryName: %s\n", msginfo);
			break;

		case NID_stateOrProvinceName:
			printf("\tsubject's ProvinceName: %s\n", msginfo);
			break;

		case NID_localityName:
			printf("\tsubject's localityName: %s\n", msginfo);
			break;

		case NID_organizationName:
			printf("\tsubject's organizationName: %s\n", msginfo);
			break;

		case NID_organizationalUnitName:
			printf("\tsubject's organizationalUnitName: %s\n", msginfo);
			break;

		case NID_commonName:
			printf("\tsubject's commonName: %s\n", msginfo);
			break;

		case NID_pkcs9_emailAddress:
			printf("\tsubject's emailAddress: %s\n", msginfo);
			break;

		default:
			break;
		}
	}

	timea = X509_get_notAfter(x509Cert);
	timeb = X509_get_notBefore(x509Cert);
	printf("\tCert notAfter: %s, notBefore: %s\n", timea->data, timeb->data);
	X509_free(x509Cert);

	return;
}