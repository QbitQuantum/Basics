void
start(void* v)
    {
    char enc_pass[64];
    char salt[MSS_SALT_SIZE + 1];
    char passwd_line[128];
    XString passwd_contents;
    pFile passwd_file;
    char buf[256];
    int len;
    int offset;
    int pos;
    int uname_len;
    int found_user;
    size_t found_len;
    char* nlptr;
    char* ptr;

	cxssInitialize();

	/** No file specified? **/
	if (!CXPASSWD.PasswdFile[0]) 
	    {
	    puts("no passwd file specified (use option -f).");
	    exit(1);
	    }
	
	/** User asked us to read password from stdin? **/
	if (CXPASSWD.ReadStdin)
	    {
	    fgets(CXPASSWD.Password, sizeof(CXPASSWD.Password), stdin);
	    if (strchr(CXPASSWD.Password, '\n'))
		{
		*strchr(CXPASSWD.Password, '\n') = '\0';
		}
	    }

	/** Now get username and/or password if not supplied on command line **/
	if (!CXPASSWD.UserName[0]) 
	    {
	    ptr = readline("Username: "******"Password: "******"could not generate random bytes for password salt.");
	    exit(1);
	    }

	/** Generate encrypted credential **/
	if (mssGenCred(salt, MSS_SALT_SIZE, CXPASSWD.Password, enc_pass, sizeof(enc_pass)) < 0)
	    {
	    puts("could not generate encrypted password.");
	    exit(1);
	    }

	/** Generate our password file line **/
	snprintf(passwd_line, sizeof(passwd_line), "%s:%s\n", CXPASSWD.UserName, enc_pass);

	/** Open the password file **/
	passwd_file = fdOpen(CXPASSWD.PasswdFile, O_RDWR | O_CREAT, 0600);
	if (!passwd_file)
	    {
	    puts("could not open passwd file.");
	    exit(1);
	    }

	/** Read it into the xstring **/
	xsInit(&passwd_contents);
	while((len = fdRead(passwd_file, buf, sizeof(buf), 0, 0)) > 0)
	    {
	    xsConcatenate(&passwd_contents, buf, len);
	    }
	fdClose(passwd_file, 0);
	
	/** Do we already have this user? **/
	uname_len = strlen(CXPASSWD.UserName);
	offset = 0;
	found_user = -1;
	while((pos = xsFind(&passwd_contents, CXPASSWD.UserName, uname_len, offset)) >= 0)
	    {
	    if ((pos == 0 || xsString(&passwd_contents)[pos-1] == '\n') && xsString(&passwd_contents)[pos+uname_len] == ':')
		{
		/** Found it **/
		found_user = pos;
		found_len = strlen(xsString(&passwd_contents)+pos);
		if ((nlptr = strchr(xsString(&passwd_contents)+pos, '\n')) != NULL)
		    found_len = (nlptr - (xsString(&passwd_contents)+pos)) + 1;
		break;
		}
	    offset = pos+1;
	    }

	/** Replace if found, otherwise add the new user **/
	if (found_user >= 0)
	    xsSubst(&passwd_contents, found_user, found_len, passwd_line, strlen(passwd_line));
	else
	    xsConcatenate(&passwd_contents, passwd_line, strlen(passwd_line));

	/** Rewrite the entire file **/
	passwd_file = fdOpen(CXPASSWD.PasswdFile, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (!passwd_file)
	    {
	    puts("could not open password file to write to it.");
	    exit(1);
	    }

	if (fdWrite(passwd_file, xsString(&passwd_contents), strlen(xsString(&passwd_contents)), 0, FD_U_SEEK | FD_U_PACKET) != strlen(xsString(&passwd_contents)))
	    {
	    puts("could not re-write new password file.");
	    exit(1);
	    }

	/** Close the file **/
	fdClose(passwd_file, 0);

    exit(0);
    }