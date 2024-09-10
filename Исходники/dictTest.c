int main(int argc, char **argv)
{
  LCHAR phrase[MAX_LINE_LENGTH];
  SR_Vocabulary *vocab = 0;
  LCHAR vocabfile[MAX_LINE_LENGTH];
  LCHAR outfilename[MAX_LINE_LENGTH];
  LCHAR testfilename[MAX_LINE_LENGTH];
  LCHAR parfilename[MAX_LINE_LENGTH];
  LCHAR wordfile[MAX_LINE_LENGTH];
  LCHAR locale[MAX_LINE_LENGTH];
  LCHAR ptemp[MAX_LINE_LENGTH];
  LCHAR* p;
  ESR_ReturnCode rc;
  int i;
  PFile* fin = 0;
  FILE* fout = stdout;
  size_t len;
  ESR_BOOL bSession = ESR_FALSE;

  LCHAR *env_sdk_path;
  LCHAR *env_lang;

  CHKLOG(rc, PMemInit());
/*  CHKLOG(rc, PFileSystemCreate());
    CHKLOG(rc, PANSIFileSystemCreate());
    CHKLOG(rc, PANSIFileSystemAddPath(L("/dev/ansi"), L("/")));*/

    /* Set ANSI file-system as default file-system */
/*  CHKLOG(rc, PANSIFileSystemSetDefault(ESR_TRUE));*/
    /* Set virtual current working directory to native current working directory */
/*  len = P_PATH_MAX;
    CHKLOG(rc, PANSIFileSystemGetcwd(cwd, &len));
    CHKLOG(rc, PFileSystemChdir(cwd));*/

    fout = stdout;
  *vocabfile = 0;
  *wordfile = 0;
  *locale = 0;
  *outfilename = 0;
  *testfilename = 0;
  *parfilename = 0;

  /* get some phrases from the user */
  LPRINTF("\nDictation Test Program for esr (Nuance Communications, 2007)\n");

  if(argc != 1 && argc != 3 && argc != 5 && argc != 7 && argc != 9)
  {
    usage();
        rc = 1;
    goto CLEANUP;
  }

  for(i=1; i<argc; i++)
  {
    if(!LSTRCMP(argv[i], L("-words")))
      LSTRCPY(wordfile, argv[++i]);
    else if(!LSTRCMP(argv[i], L("-vocab")))
      LSTRCPY(vocabfile, argv[++i]);
    else if(!LSTRCMP(argv[i], L("-locale")))
      LSTRCPY(locale, argv[++i]);
    else if(!LSTRCMP(argv[i], L("-out")))
      LSTRCPY(outfilename, argv[++i]);
    else if(!LSTRCMP(argv[i], L("-itest")))
      LSTRCPY(testfilename, argv[++i]);
    else if(!LSTRCMP(argv[i], L("-parfile")) || !LSTRCMP(argv[i], L("-par")) )
      LSTRCPY(parfilename, argv[++i]);
    else {
      usage();
      rc = 1;
      goto CLEANUP;
    }
  }

  if ( *parfilename == L('\0') )
  {
    LPRINTF ( "Warning: No parfile defined in the command line.\n" );
    LPRINTF ( "Looking for the default parfile, $ESRSDK/config/$ESRLANG/baseline.par...\n" );

    env_sdk_path =  LGETENV(L("ESRSDK"));
    if ( env_sdk_path != NULL )
    {
      LSPRINTF ( parfilename, L("%s/config/"), env_sdk_path );
      env_lang = LGETENV(L("ESRLANG"));
      if ( env_lang != NULL )
      {
         LSTRCAT ( parfilename, env_lang );
         LSTRCAT ( parfilename, L("/baseline.par") );
      }
      else
      {
        LPRINTF("Error: An environment variable ESRLANG should be defined.\n");
        goto CLEANUP;
      }
    }
    else
    {
      LPRINTF("Error: An environment variable ESRSDK should be defined.\n");
      goto CLEANUP;
    }
  }

  rc = InitSession( parfilename );
  if ( rc != ESR_SUCCESS )
  {
    LPRINTF("Error: %s\n", ESR_rc2str(rc));
    goto CLEANUP;
  }
  bSession = ESR_TRUE;

  if (*vocabfile == 0)
  {
    len = sizeof(vocabfile);
    rc = ESR_SessionGetLCHAR ( L("cmdline.vocabulary"), vocabfile, &len );
    env_sdk_path =  LGETENV(L("ESRSDK"));
    if ( env_sdk_path != NULL )
      {
	LSPRINTF ( parfilename, L("%s/config/"), env_sdk_path );
	env_lang = LGETENV(L("ESRLANG"));
	if ( env_lang != NULL )
	  {
	    LSTRCAT ( parfilename, env_lang );
	    LSTRCAT ( parfilename, L("/baseline.par") );
	  }
	else
	  {
	    LPRINTF("Error: An environment variable ESRLANG should be defined.\n");
	    goto CLEANUP;
	  }
      }
    else
      {
	LPRINTF("Error: An environment variable ESRSDK should be defined.\n");
	goto CLEANUP;
      }

    strcpy(ptemp, env_sdk_path);
    strcat(ptemp,"/config/");
    strcat(ptemp,env_lang);
    strcat(ptemp,"/");
    strcat(ptemp,vocabfile);
    strcpy(vocabfile,ptemp);
    if ( rc == ESR_SUCCESS )
    {
      len = sizeof(vocabfile);
       rc = ESR_SessionPrefixWithBaseDirectory(vocabfile, &len);
    }
    else
    {
       *vocabfile = 0;
    }
  }

  if (*vocabfile)
    rc = SR_VocabularyLoad(vocabfile, &vocab);
  else if (*locale)
  {
    ESR_Locale localeTag;

    rc = ESR_str2locale(locale, &localeTag);
    if (rc != ESR_SUCCESS)
    {
      LPRINTF("Error: %s\n",ESR_rc2str(rc));
      goto CLEANUP;
    }
    rc = SR_VocabularyCreate(localeTag, &vocab);
  }
  else
    rc = SR_VocabularyCreate(ESR_LOCALE_EN_US, &vocab);

  if (rc != ESR_SUCCESS)
  {
    LPRINTF("Error: %s\n",ESR_rc2str(rc));
    goto CLEANUP;
  }

  if (*outfilename) /* output file */
  {
    if  ((fout = fopen(outfilename,"w")) == NULL)
    {
      LPRINTF("Could not open file: %s\n",outfilename);
      rc = 1;
      goto CLEANUP;
    }
  }

  if (*wordfile) /* file mode */
  {
    if ((fin = pfopen(wordfile,"r")) == NULL)
    {
      LPRINTF("Could not open file: %s\n", wordfile);
      goto CLEANUP;
    }
    while (pfgets(phrase, MAX_LINE_LENGTH, fin)!=NULL)
    {
      lstrtrim(phrase);
      doGetProns(vocab, phrase, MAX_PRONS_LENGTH, fout);
    }

  }
  else if (*testfilename) /* test file mode */
  {
    if ((fin = pfopen(testfilename,"r")) == NULL)
    {
      LPRINTF("Could not open file: %s\n", testfilename);
      rc = 1;
      goto CLEANUP;
    }
    doInputTestPhonemes(vocab, fin, fout);
  }
  else /* interactive mode */
  {
    LPRINTF("'qqq' to quit\n");
    while (ESR_TRUE)
    {
      LPRINTF("> ");
      if(! pfgets(phrase, MAX_LINE_LENGTH, PSTDIN ))
        break;
      // remove trailing whitespace
      for(p=&phrase[0]; *p!=0 && *p!='\n' && *p!='\r'; p++) {}
      *p=0;
      lstrtrim(phrase);
      if(!LSTRCMP("qqq",phrase))
        break;
      else
        doGetProns(vocab, phrase, MAX_PRONS_LENGTH, fout);
     }
  }

CLEANUP:
  if(vocab)
    vocab->destroy(vocab);

  if(bSession)
    ShutdownSession();

  if(fin)
    pfclose(fin);

  if(fout && fout != stdout)
    fclose(fout);

/*  PANSIFileSystemDestroy();
  PFileSystemDestroy();*/
  PMemShutdown();
  return rc;
}