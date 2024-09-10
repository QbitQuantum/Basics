void lprPrintfile(
	JOBDEF* pjd,
	char* oriFileName,
	char* spoolFileFullName,
	int16 cnId,
	void (*meter)(long totLen, long accumLen, long actLen) )
{
	char fileBuff[FILEBUFFSIZE];
	long fileLength;
	long lenData = 0;
	long lenSent = 0;    
	char o_str[100];
	int	fin;
	char rc;
	char *eM;

	if ( (fin=Fopen(spoolFileFullName, FO_READ)) < 0) {
		eM = "cannot open spool file for read"; goto errExit;
	}

	fileLength = Fseek(0, fin, 2);	/* position to end */
	Fseek(0, fin, 0);

	/* start the lprd protocol for this file */

/* command 0x02 "receive  printer job" */

	o_str[0] = 0x02;
	o_str[1] = '\0';
	strcat(o_str, pjd->rmPrinter);
	strcat(o_str, "\n");
	output(cnId, o_str, (int)strlen(o_str));

	if ( getResponse(cnId) != 0x00 ) {
		uiPrintf(uiH, uiPrERR, "unknown queue|>%s<|on remote host", pjd->rmPrinter);
		return;
	}



/* subcommand 0x02 "receive control file" */

	/* build the control file */
	strcpy(fileBuff,   "H");
	strcat(fileBuff, pjd->hostName);	/* mandatory */
	strcat(fileBuff, "\nP");
	strcat(fileBuff, pjd->userName);	/* mandatory */
	strcat(fileBuff, "\nN");
	strcat(fileBuff, oriFileName);		/* mandatory */
	strcat(fileBuff, "\n");

	if (pjd->optSendMail) {
		strcat(fileBuff,   "M");
		strcat(fileBuff, pjd->userName);
		strcat(fileBuff, "\n");
	}

	if (!pjd->optNoBanner) {
		strcat(fileBuff,   "C");
		strcat(fileBuff, pjd->hostName);	/* class for banner */
		strcat(fileBuff, "\nJ");
		strcat(fileBuff, oriFileName);		/* job name for banner */
		strcat(fileBuff, "\nL");
		strcat(fileBuff, pjd->userName);	/* banner */
		strcat(fileBuff, "\n");
	}

#if 0	/* not supported */
	strcat(fileBuff,   "U");
	strcat(fileBuff, spoolFileName);	/* unlink data file */
	strcat(fileBuff, "\n");
#endif

	if (pjd->optNCopies) {
		strcat(fileBuff,   "#");
		strcat(fileBuff, pjd->optNCopies);
		strcat(fileBuff, "\n");
	}

	if (pjd->optNIndent) {
		strcat(fileBuff,   "I");
		strcat(fileBuff, pjd->optNIndent);
		strcat(fileBuff, "\n");
	}

	if (pjd->optNWidth) {
		strcat(fileBuff,   "W");
		strcat(fileBuff, pjd->optNWidth);
		strcat(fileBuff, "\n");
	}

	if (pjd->optTitle) {
		strcat(fileBuff,   "T");
		strcat(fileBuff, pjd->optTitle);
		strcat(fileBuff, "\n");
	}

	strcat(fileBuff, pjd->optFormat);
	strcat(fileBuff, pjd->spoolFile);
	strcat(fileBuff, "\n");

#ifdef DEBUG
	uiPrintf(uiH, uiPrOK, "%s", fileBuff);
#endif

	o_str[0] = 0x02;
	ltoa(strlen(fileBuff), o_str+1, 10);
	strcat(o_str, " c");
	strcat(o_str, pjd->spoolFile);
	strcat(o_str, "\n");

	output(cnId, o_str, (int)strlen(o_str));
	rc = getResponse(cnId);
	if        (rc == 0x01) {
		eM = "connection messed up, try again"; goto errExit;
	} else if (rc == 0x02) {
		eM = "server out of storage space"; goto errExit;
	} else if (rc != 0x00) {
		eM = "no ack on sub command 3"; goto errExit;
	}

	output(cnId, fileBuff, (int)strlen(fileBuff));

	fileBuff[0] = 0;
	output(cnId, fileBuff, 1);	/* terminator */

	if ( getResponse(cnId) != 0x00 ) {
		eM = "control file not properly transferred"; goto errExit;
	}


/* subcommand 0x03 "receive data file" */

	o_str[0] = 0x03;
	ltoa(fileLength, o_str+1, 10);
	strcat(o_str, " d");
	strcat(o_str, pjd->spoolFile);
	strcat(o_str, "\n");
#ifdef DEBUG
	uiPrintf(uiH, uiPrOK, "%s", o_str+1);
#endif
	output(cnId, o_str, (int)strlen(o_str));

	rc = getResponse(cnId);
	if        (rc == 0x01) {
		eM = "connection messed up, try again"; goto errExit;
	} else if (rc == 0x02) {
		eM = "server out of storage space"; goto errExit;
	} else if (rc != 0x00) {
		eM = "unknown"; goto errExit;
	}


	while ( (lenData = Fread(fin, min(FILEBUFFSIZE, fileLength), fileBuff)) > 0) {
		lenSent += lenData;

		if (meter != NULL)
			(*meter)(fileLength, lenSent, lenData);

		output(cnId, fileBuff, (int)lenData);
	}


	fileBuff[0] = 0;
	output(cnId, fileBuff, 1);	/* terminator */

	Fclose(fin);

	if ( getResponse(cnId) != 0x00 ) {
		eM = "data file not properly transferred"; goto errExit;
	}
#ifdef DEBUG
	uiPrintf(uiH, uiPrOK, "file closed");
#endif
	return;

errExit:
	uiPrintf(uiH, uiPrERR, "%s", eM);
}	/* print_file */