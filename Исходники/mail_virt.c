int
main (int argc, char ** argv)
{
  int c, readed = 0;
  FILE *fd = NULL;
  char buf [4096];
  SQLLEN cbParam;
  SQLRETURN  retcode;
  SQLPOINTER pToken;
  FILE *cfg;
  char *ini = NULL, suid[128], spwd[128];

  if (argc < 1)
    {
      fprintf (stderr, "Type -? for help\n");
      return ERR_USAGE;
    }

  while ((c = getopt (argc, argv, "b:s:w:r:f:i:")) != EOF)
    {
      switch (c)
	{

	  case 'b':
	      dsn = optarg;
	      break;

	  case 's':
	      uid = optarg;
	      break;

	  case 'w':
	      pwd = optarg;
	      break;

	  case 'r':
	      uname = optarg;
	      break;

	  case 'i':
	      ini = optarg;
	      break;

	  case '?':
	      fprintf (stderr, "Usage: %s -b [DSN] -s [UID] -w [PWD] -r [RCPT] -i [INI_FILE]\n", argv [0]);
	      return 0;
	      break;
	}
    }

  if ((argc < 4 && !ini) || (argc < 3 && ini))
    {
      fprintf (stderr, "%s: missing arguments\nTry -? for help\n", argv [0]);
      return ERR_USAGE;
    }

  if (ini)
    {
      cfg = fopen (ini, "rt");
      if (!cfg)
	{
	  fprintf (stderr, "%s: cannot open config file\n", argv [0]);
	  return ERR_USAGE;
	}
      suid[0] = 0; spwd[0] = 0;
      fscanf (cfg, "%s %s", suid, spwd);
      uid = suid; pwd = spwd;
      fclose (cfg);
    }


  SQLAllocEnv (&henv);
  SQLAllocConnect (henv, &hdbc);

  if (SQL_ERROR == SQLConnect (hdbc, (UCHAR *) dsn, SQL_NTS,
	(UCHAR *) uid, SQL_NTS, (UCHAR *) pwd, SQL_NTS))
    {
      fprintf (stderr, "Database connect failed DSN:%s UID:%s PWD:%s\n", dsn, uid, pwd);
      return ERR_TEMP;
    }

  SQLAllocStmt (hdbc, &new_mail);
  if (SQL_ERROR == SQLPrepare (new_mail, (UCHAR *) new_mail_st, SQL_NTS))
    {
      fprintf (stderr, "Statement prepare fails\n");
      return ERR_SOFT;
    }

  SQLSetParam (new_mail, 1, SQL_C_CHAR, SQL_CHAR, 0,0, uname, NULL);

  SQLBindParameter(new_mail, 2, SQL_PARAM_INPUT,
      SQL_C_BINARY, SQL_LONGVARBINARY,
      0, 0, (SQLPOINTER) 2, 0, &cbParam);

  cbParam = SQL_DATA_AT_EXEC;
deadlock_no:
  retcode = SQLExecute (new_mail);
  if (retcode != SQL_NEED_DATA)
    {
      char state [10], msg [256];
      if (SQL_SUCCESS == SQLError (SQL_NULL_HENV, SQL_NULL_HDBC, new_mail, state, NULL, msg, 256, NULL))
       fprintf (stderr, "SQL Error status code: %s description: %s\n", state, msg);
      if (0 == strcmp (state, "40001"))
	goto deadlock_no;
	/*return ERR_TEMP;*/
      return ERR_SOFT;
    }
  fd = stdin;
  while (retcode == SQL_NEED_DATA)
    {
      retcode = SQLParamData(new_mail, &pToken);
      if (retcode == SQL_NEED_DATA)
	{
	  while (!feof (fd))
	    {
	      memset (buf, '\x0', sizeof (buf));
	      readed = fread (buf, sizeof (buf) - 1, 1L, fd);
	      SQLPutData(new_mail, buf, strlen (buf));
	    }
	}
    }
  return 0;
};