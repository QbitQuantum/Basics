APIRET UserDel (void)
{
  NETRET rc;                                           /* NET_API returncode */

#define ASC2UNI(a,b) OemToChar(Options.a,Globals.b)

  /**************************************************************************
   * convert ASCII to UNICODE strings                                       *
   **************************************************************************/

#ifdef _WIN32
  if (Options.fsUser)          ASC2UNI(pszUser,         lptstrUser);
  if (Options.fsServer)        ASC2UNI(pszServer,       lptstrServer);
#endif

  printf ("\nDeleting account %s from %s.",
	      Options.pszUser,
		  Options.fsServer ? Options.pszServer : "<local>");

  /* @@@confirmation !! */
  if (!Options.fsNoPrompt)
  {
	int iAnswer;                                         /* answer from user */

	iAnswer = ToolsConfirmationQuery();               /* ask the user yes/no */
	if (iAnswer != 1)                                   /* answer is not YES */
	  return (0);                      /* then abort the process immediately */
  }

#ifdef _WIN32
  rc = NetUserDel(Globals.lptstrServer,
                  Globals.lptstrUser);
#endif

#ifdef __OS2__
  rc = Net32UserDel(Options.pszServer,
                    Options.pszUser,
                    NULL);
#endif
  if (rc != NERR_Success)
  {
	UserDelError (rc,
		          0);
  }

  return (rc);
}