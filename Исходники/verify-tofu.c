static int parse_line(char *line,
		      const char *host, size_t host_len,
		      const char *service, size_t service_len,
		      time_t now,
		      const gnutls_datum_t * rawkey,
		      const gnutls_datum_t * b64key)
{
	char *p, *kp;
	char *savep = NULL;
	size_t kp_len;
	time_t expiration;

	/* read version */
	p = strtok_r(line, "|", &savep);
	if (p == NULL)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	if (strncmp(p, "c0", 2) == 0)
		return parse_commitment_line(p + 3, host, host_len,
					     service, service_len, now,
					     rawkey);

	if (strncmp(p, "g0", 2) != 0)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	/* read host */
	p = strtok_r(NULL, "|", &savep);
	if (p == NULL)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	if (p[0] != '*' && host != NULL && strcmp(p, host) != 0)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	/* read service */
	p = strtok_r(NULL, "|", &savep);
	if (p == NULL)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	if (p[0] != '*' && service != NULL && strcmp(p, service) != 0)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	/* read expiration */
	p = strtok_r(NULL, "|", &savep);
	if (p == NULL)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	expiration = (time_t) atol(p);
	if (expiration > 0 && now > expiration)
		return gnutls_assert_val(GNUTLS_E_EXPIRED);

	/* read key */
	kp = strtok_r(NULL, "|", &savep);
	if (kp == NULL)
		return gnutls_assert_val(GNUTLS_E_PARSING_ERROR);

	p = strpbrk(kp, "\n \r\t|");
	if (p != NULL)
		*p = 0;

	kp_len = strlen(kp);
	if (kp_len != b64key->size)
		return
		    gnutls_assert_val(GNUTLS_E_CERTIFICATE_KEY_MISMATCH);

	if (memcmp(kp, b64key->data, b64key->size) != 0)
		return
		    gnutls_assert_val(GNUTLS_E_CERTIFICATE_KEY_MISMATCH);

	/* key found and matches */
	return 0;
}