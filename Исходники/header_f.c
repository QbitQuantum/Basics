/* replaces the uri in first line of mes with the other uri */
void uri_replace(char *mes, char *uri)
{
	char *foo, *backup;

	foo=strchr(mes, '\n');
	if (!foo) {
		printf("failed to find newline\n");
		exit_code(254);
	}
	foo++;
	backup=malloc(strlen(foo)+1);
	if (!backup) {
		printf("failed to allocate memory\n");
		exit_code(255);
	}
	strncpy(backup, foo, strlen(foo)+1);
	foo=STRSTR(mes, "sip");
	strncpy(foo, uri, strlen(uri));
	strncpy(foo+strlen(uri), SIP20_STR, SIP20_STR_LEN);
	strncpy(foo+strlen(uri)+SIP20_STR_LEN, backup, strlen(backup)+1);
	free(backup);
	if (verbose > 2)
		printf("Message with modified uri:\n%s\n", mes);
}