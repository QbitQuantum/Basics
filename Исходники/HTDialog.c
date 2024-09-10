PUBLIC BOOL HTConfirm (HTRequest * request, HTAlertOpcode op,
		       int msgnum, const char * dfault, void * input,
		       HTAlertPar * reply)
{
    char response[4];	/* One more for terminating NULL -- AL */
    HTPrint("%s", HTDialogs[msgnum]);
    if (input) HTPrint(" (%s)", (char *) input);
    HTPrint(" (y/n) ");
    if (fgets(response, 4, stdin)) { 		   /* get reply, max 3 chars */
	char *ptr = response;
	while (*ptr) {
	    if (*ptr == '\n') {
		*ptr = '\0';
		break;
	    }
	    *ptr = TOUPPER(*ptr);
	    ptr++;
	}
	return (!strcmp(response, "YES") || !strcmp(response, "Y")) ? YES : NO;
    }
    return NO;
}