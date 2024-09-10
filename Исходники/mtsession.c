/*** mssAuthenticate - start a new session, overwriting previous
 *** (inherited) session information.
 ***/
int 
mssAuthenticate(char* username, char* password)
    {
    pMtSession s;
    char* encrypted_pwd;
    char* pwd;
    struct passwd* pw = NULL;
#ifdef HAVE_SHADOW_H
    struct spwd* spw;
#endif
    char salt[3];
    pFile altpass_fd;
    pLxSession altpass_lxs;
    char pwline[80];
    int t;
    int found_user;
    gid_t grps[16];
    int n_grps;

	/** Allocate a new session structure. **/
	s = (pMtSession)nmMalloc(sizeof(MtSession));
	if (!s) return -1;
	s->LinkCnt = 1;
	strncpy(s->UserName, username, 31);
	s->UserName[31]=0;
	strncpy(s->Password, password, 31);
	s->Password[31]=0;

	/** Attempt to authenticate. **/
	if (!strcmp(MSS.AuthMethod,"system"))
	    {
	    /** Use system auth (passwd/shadow files) **/
	    pw = getpwnam(s->UserName);
	    if (!pw)
		{
		memset(s, 0, sizeof(MtSession));
		nmFree(s,sizeof(MtSession));
		return -1;
		}
#ifdef HAVE_SHADOW_H
	    spw = getspnam(s->UserName);
	    if (!spw)
		{
#endif
		pwd = pw->pw_passwd;
#ifdef HAVE_SHADOW_H
		}
	    else
		{
		pwd = spw->sp_pwdp;
		}
#endif
	    strncpy(salt,pwd,2);
	    salt[2]=0;
	    encrypted_pwd = (char*)crypt(s->Password,pwd);
	    if (strcmp(encrypted_pwd,pwd))
		{
		memset(s, 0, sizeof(MtSession));
		nmFree(s,sizeof(MtSession));
		return -1;
		}
	    }
	else if (!strcmp(MSS.AuthMethod, "altpasswd"))
	    {
	    /** Sanity checking. **/
	    if (strchr(username,':'))
		{
		mssError(1, "MSS", "Attempt to use invalid username '%s'", username);
		memset(s, 0, sizeof(MtSession));
		nmFree(s,sizeof(MtSession));
		return -1;
		}

	    /** Open the alternate password file **/
	    altpass_fd = fdOpen(MSS.AuthFile, O_RDONLY, 0600);
	    if (!altpass_fd)
		{
		mssErrorErrno(1, "MSS", "Could not open auth file '%s'", MSS.AuthFile);
		memset(s, 0, sizeof(MtSession));
		nmFree(s,sizeof(MtSession));
		return -1;
		}
	    altpass_lxs = mlxOpenSession(altpass_fd, MLX_F_LINEONLY | MLX_F_EOF);

	    /** Scan it for the user name **/
	    found_user = 0;
	    while ((t = mlxNextToken(altpass_lxs)) != MLX_TOK_EOF)
		{
		if (t == MLX_TOK_ERROR)
		    {
		    mssError(0, "MSS", "Could not read auth file '%s'", MSS.AuthFile);
		    memset(s, 0, sizeof(MtSession));
		    nmFree(s,sizeof(MtSession));
		    mlxCloseSession(altpass_lxs);
		    fdClose(altpass_fd, 0);
		    return -1;
		    }
		mlxCopyToken(altpass_lxs, pwline, 80);
		if (strlen(username) < strlen(pwline) && !strncmp(pwline, username, strlen(username)) && pwline[strlen(username)] == ':')
		    {
		    found_user = 1;
		    break;
		    }
		}

	    /** Close the alternate password file **/
	    mlxCloseSession(altpass_lxs);
	    fdClose(altpass_fd, 0);

	    /** Did we find the user in the file? **/
	    if (found_user)
		{
		if (pwline[strlen(pwline)-1] == '\n')
		    pwline[strlen(pwline)-1] = '\0';
		pwd = pwline + strlen(username) + 1;
		encrypted_pwd = (char*)crypt(s->Password,pwd);
		if (strcmp(encrypted_pwd,pwd))
		    {
		    memset(s, 0, sizeof(MtSession));
		    nmFree(s,sizeof(MtSession));
		    return -1;
		    }
		}
	    else
		{
		memset(s, 0, sizeof(MtSession));
		nmFree(s,sizeof(MtSession));
		return -1;
		}
	    }
	else
	    {
	    mssError(1, "MSS", "Invalid auth method '%s'", MSS.AuthMethod);
	    return -1;
	    }

	/** Set the session information **/
	if (!strcmp(MSS.AuthMethod,"system"))
	    {
	    s->UserID = pw->pw_uid;
	    s->GroupID = pw->pw_gid;
	    initgroups(username, s->GroupID);
	    }
	else
	    {
	    s->UserID = geteuid();
	    s->GroupID = getegid();
	    }
	n_grps = getgroups(sizeof(grps) / sizeof(gid_t), grps);
	if (n_grps < 0 || n_grps > sizeof(grps) / sizeof(gid_t))
	    n_grps = 0;
	thSetParam(NULL,"mss",(void*)s);
	thSetParamFunctions(NULL, mssLinkSession, mssUnlinkSession);
	thSetSupplementalGroups(NULL, n_grps, grps);
	thSetGroupID(NULL,s->GroupID);
	thSetUserID(NULL,s->UserID);

	/** Initialize the error info **/
	xaInit(&(s->ErrList), 16);
	xhInit(&s->Params, 17, 0);

	/** Add to session list **/
	xaAddItem(&(MSS.Sessions), (void*)s);

    return 0;
    }