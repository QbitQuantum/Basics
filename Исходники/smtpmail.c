void PageAlert(char *subject,char *message)
{
	char messagebuf[4000];
	char FAR hostname[256];
	unsigned int i;
	int res;
	char *mailServer;
	char *emailAddress;

	/* hostname of computer */
	gethostname((char *)&hostname ,255-1);

	mailServer = ConfigStr( EMAIL_HOST );
	emailAddress = ConfigStr( EMAIL_NAME );

	/* don`t want spaces in either subject or message */
	for(i=0;i<strlen( subject ); i++) {
		if(subject[ i ] == ' ' ) subject[ i ] = '_'; 
	}
	for(i=0;i<strlen( message ); i++) {
		if(message[ i ] == ' ' ) message[ i ] = '_'; 
	}

	/* build the command string , bypass the mail filter .. (its ok we`re inside 3do) */
	/* until i finish the internal mail sender, i`ve ignored the subject parameter */
	sprintf(messagebuf,"mailto -H %s -U %s -S Warning -M %s -D %s",mailServer,hostname,message,emailAddress);
	dprintf(messagebuf);
	
	/* calling system() requires a flush of all buffered streams */
	_flushall();

	/* handle any returns from system */
	res = system(messagebuf);

	/* handle any returns from system */
	if(res==-1) {
		DisplayErrnoText();
	} else	
		dprintf("system command returned %d\n",res);
}