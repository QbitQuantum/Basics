/****************************************************************************
an enhanced crypt for OSF1
****************************************************************************/
static char *osf1_bigcrypt(char *password, char *salt1)
{
	static char result[AUTH_MAX_PASSWD_LENGTH] = "";
	char *p1;
	char *p2 = password;
	char salt[3];
	int i;
	int parts = strlen(password) / AUTH_CLEARTEXT_SEG_CHARS;
	if (strlen(password) % AUTH_CLEARTEXT_SEG_CHARS)
		parts++;

	StrnCpy(salt, salt1, 2);
	StrnCpy(result, salt1, 2);
	result[2] = '\0';

	for (i = 0; i < parts; i++) {
		p1 = crypt(p2, salt);
		strncat(result, p1 + 2,
			AUTH_MAX_PASSWD_LENGTH - strlen(p1 + 2) - 1);
		StrnCpy(salt, &result[2 + i * AUTH_CIPHERTEXT_SEG_CHARS], 2);
		p2 += AUTH_CLEARTEXT_SEG_CHARS;
	}

	return (result);
}