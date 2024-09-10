void displayError (SQLSMALLINT handleType, SQLHANDLE handle)		
{
	SQLSMALLINT	recNumber = 1;
	UCHAR	sqlstate[10];
	UCHAR	errmsg[SQL_MAX_MESSAGE_LENGTH];
	SDWORD	nativeerr;
	SWORD	actualmsglen;
	RETCODE	rc;

loop:  	rc = SQLGetDiagRec(handleType, handle, recNumber, sqlstate, &nativeerr, errmsg, strlen(errmsg), &actualmsglen);

	if (rc != SQL_SUCCESS) {
		printf ("SQLGetDiagRec failed!\n");
		getchar();
		return;
	}

	if (rc != SQL_NO_DATA_FOUND) {
		printf ("SQLSTATE = %s\n",sqlstate);
		printf ("NATIVE ERROR = %d\n",nativeerr);
		errmsg[actualmsglen] = '\0';
		printf ("MSG = %s\n\n",errmsg); 
		recNumber++;
		goto loop;
	}
}