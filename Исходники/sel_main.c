/* parse given command line and initialize NaClApp object */
static void ParseCommandLine(struct NaClApp *nap, int argc, char **argv)
{
  int opt;
  char *manifest_name = NULL;

  /* set defaults */
  nap->skip_qualification = 0;
  nap->quit_after_load = 0;
  nap->handle_signals = 1;
  nap->storage_limit = ZEROVM_IO_LIMIT;

  /* construct zlog with default verbosity */
  ZLogCtor(LOG_ERROR);

  /* todo(d'b): revise switches and rename them */
  while((opt = getopt(argc, argv, "+FeQsSv:M:l:")) != -1)
  {
    switch(opt)
    {
      case 'M':
        manifest_name = optarg;
        break;
      case 's':
        nap->skip_validator = 1;
        ZLOG(LOG_ERROR, "validation disabled by -s");
        break;
      case 'F':
        nap->quit_after_load = 1;
        break;
      case 'e':
        TagEngineCtor();
        nap->user_tag = TagCtor();
        break;
      case 'S':
        /* d'b: disable signals handling */
        nap->handle_signals = 0;
        break;
      case 'l':
        /* calculate hard limit in Gb and don't allow it less then "big enough" */
        nap->storage_limit = ATOI(optarg) * ZEROVM_IO_LIMIT_UNIT;
        ZLOGFAIL(nap->storage_limit < ZEROVM_IO_LIMIT_UNIT, EFAULT,
            "invalid storage limit: %d", nap->storage_limit);
        break;
      case 'v':
        ZLogDtor();
        ZLogCtor(ATOI(optarg));
        break;
      case 'Q':
        nap->skip_qualification = 1;
        ZLOGS(LOG_ERROR, "PLATFORM QUALIFICATION DISABLED BY -Q - "
            "Native Client's sandbox will be unreliable!");
        break;
      default:
        ZLOGS(LOG_ERROR, "ERROR: unknown option: [%c]", opt);
        puts(HELP_SCREEN);
        exit(EINVAL);
        break;
    }
  }

  /* show zerovm command line */
  ZVMCommandLine(argc, argv);

  /* parse manifest file specified in cmdline */
  if(manifest_name == NULL)
  {
    puts(HELP_SCREEN);
    exit(EINVAL);
  }
  ZLOGFAIL(ManifestCtor(manifest_name), EFAULT, "Invalid manifest '%s'", manifest_name);

  /* set available nap and manifest fields */
  assert(nap->system_manifest != NULL);
  nap->system_manifest->nexe = GetValueByKey("Nexe");
  ZLOGFAIL(GetFileSize(nap->system_manifest->nexe) < 0, ENOENT, "nexe open error");
  syscallback = 0;
}