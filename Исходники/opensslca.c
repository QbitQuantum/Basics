/* Writes a certificate to a new file. */
int write_cert(X509 *cert)
{
	FILE *fp = NULL;
	char filename[MAX_PATH], serialstr[20];
	long serial = ASN1_INTEGER_get(X509_get_serialNumber(cert));
	int ret;

	/* Create file name from serial number */
	strcpy(filename, CA_PATH(caIni.newCertsDir));
	strcat(filename, _ltoa(serial, serialstr, 10));
	strcat(filename, caIni.newCertsExt);

	fp = fopen(filename, "w");
	if (fp == NULL)
		return OPENSSLCA_ERR_CERT_OPEN;

	/* Write certificate text */
	if (X509_print_fp(fp, cert) != 1) {
		ret = OPENSSLCA_ERR_CERT_WRITE;
		goto err;
	}

	/* Write PEM */
	if (PEM_write_X509(fp, cert) != 1) {
		ret = OPENSSLCA_ERR_CERT_WRITE;
		goto err;
	}

err:
	if (fp)
		fclose(fp);

	return ret;
}