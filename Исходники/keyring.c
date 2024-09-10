WizardExport WizardBooleanType KeyringCommand(int argc,char **argv,
  ExceptionInfo *exception)
{
#define DestroyKeyring() \
{ \
  for (i=0; i < (ssize_t) argc; i++) \
    argv[i]=DestroyString(argv[i]); \
  argv=(char **) RelinquishWizardMemory(argv); \
}
#define ThrowKeyringException(asperity,tag,context) \
{ \
  (void) ThrowWizardException(exception,GetWizardModule(),asperity,tag, \
    context); \
  DestroyKeyring(); \
  return(WizardFalse); \
}
#define ThrowInvalidArgumentException(option,argument) \
{ \
  (void) ThrowWizardException(exception,GetWizardModule(),OptionError, \
    "invalid argument: `%s': %s",argument,option); \
  DestroyKeyring(); \
  return(WizardFalse); \
}

  BlobInfo
    *keyring_blob;

  const char
    *option;

  register ssize_t
    i;

  WizardBooleanType
    status;

  /*
    Parse command-line options.
  */
  if (argc == 2)
    {
      option=argv[1];
      if ((LocaleCompare("version",option+1) == 0) ||
          (LocaleCompare("-version",option+1) == 0))
        {
          (void) fprintf(stdout,"Version: %s\n",GetWizardVersion(
            (size_t *) NULL));
          (void) fprintf(stdout,"Copyright: %s\n\n",GetWizardCopyright());
          return(WizardTrue);
        }
    }
  if (argc < 2)
    KeyringUsage();
  status=ExpandFilenames(&argc,&argv);
  if (status == WizardFalse)
    ThrowKeyringException(ResourceError,"memory allocation failed: `%s'",
      strerror(errno));
  for (i=1; i < (argc-1); i++)
  {
    option=argv[i];
    if (LocaleCompare(option+1,"export") == 0)
      {
        status=ExportKeyring(argc,argv,exception);
        DestroyKeyring();
        return(status);
      }
  }
  keyring_blob=OpenBlob(argv[argc-1],WriteBinaryBlobMode,WizardTrue,exception);
  if (keyring_blob == (BlobInfo *) NULL)
    return(WizardFalse);
  (void) WriteBlobString(keyring_blob,"<?xml version=\"1.0\"?>\n");
  (void) WriteBlobString(keyring_blob,"<rdf:RDF xmlns:rdf=\""
    "http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n");
  (void) WriteBlobString(keyring_blob,"         xmlns:keyring=\""
    "http://www.wizards-toolkit.org/keyring/1.0/\">\n");
  for (i=1; i < (ssize_t) (argc-1); i++)
  {
    option=argv[i];
    if (IsWizardOption(option) != WizardFalse)
      switch (*(option+1))
      {
        case 'd':
        {
          if (LocaleCompare(option,"-debug") == 0)
            {
              LogEventType
                event_mask;

              i++;
              if (i == (ssize_t) argc)
                ThrowKeyringException(OptionError,"missing log event mask: "
                  "`%s'",option);
              event_mask=SetLogEventMask(argv[i]);
              if (event_mask == UndefinedEvents)
                ThrowKeyringException(OptionFatalError,"unrecognized log event "
                  "type: `%s'",argv[i]);
              break;
            }
          ThrowKeyringException(OptionFatalError,"unrecognized option: `%s'",
            option);
          break;
        }
        case 'h':
        {
          if ((LocaleCompare("help",option+1) == 0) ||
              (LocaleCompare("-help",option+1) == 0))
            KeyringUsage();
          ThrowKeyringException(OptionFatalError,"unrecognized option: `%s'",
            option);
          break;
        }
        case 'l':
        {
          if (LocaleCompare(option,"-list") == 0)
            {
              ssize_t
                list;

              if (*option == '+')
                break;
              i++;
              if (i == (ssize_t) argc)
                ThrowKeyringException(OptionError,"missing list type: `%s'",
                  option);
              if (LocaleCompare(argv[i],"configure") == 0)
                {
                  (void) ListConfigureInfo((FILE *) NULL,exception);
                  Exit(0);
                }
              list=ParseWizardOption(WizardListOptions,WizardFalse,argv[i]);
              if (list < 0)
                ThrowKeyringException(OptionFatalError,"unrecognized list "
                  "type: `%s'",argv[i]);
              (void) ListWizardOptions((FILE *) NULL,(WizardOption) list,
                exception);
              Exit(0);
              break;
            }
          if (LocaleCompare("log",option+1) == 0)
            {
              if (*option == '+')
                break;
              i++;
              if ((i == (ssize_t) argc) ||
                  (strchr(argv[i],'%') == (char *) NULL))
                ThrowKeyringException(OptionFatalError,"missing argument: `%s'",
                  option);
              break;
            }
          ThrowKeyringException(OptionFatalError,"unrecognized option: `%s'",
            option);
          break;
        }
        case 'v':
        {
          if (LocaleCompare(option,"-version") == 0)
            {
              (void) fprintf(stdout,"Version: %s\n",GetWizardVersion(
                (size_t *) NULL));
              (void) fprintf(stdout,"Copyright: %s\n\n",GetWizardCopyright());
              exit(0);
            }
          ThrowKeyringException(OptionFatalError,"unrecognized option: `%s'",
            option);
          break;
        }
        default:
        {
          ThrowKeyringException(OptionFatalError,"unrecognized option: `%s'",
            option);
          break;
        }
      }
    status=PrintKeyringProperties(argv[i],keyring_blob,exception);
  }
  if (argc == 2)
    status=PrintKeyringProperties((const char *) NULL,keyring_blob,exception);
  (void) WriteBlobString(keyring_blob,"</rdf:RDF>\n");
  status=CloseBlob(keyring_blob);
  /*
    Free resources.
  */
  DestroyKeyring();
  return(status);
}