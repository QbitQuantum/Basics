int
main (int ac, char **av)
{
  char rbuff[TBUF];
  char buff[TBUF];
  char savebuff[TBUF];
  char cmd[TBUF];
  char mffile[TBUF];
  char *arg[4];
  static char execfile[TBUF];

  char kpsedot[TBUF];
  char currdir[TBUF];
  char *tmp;
  int cdrive, tdrive;

  FILE *fr, *fw, *fnul;

  int i, savo, savi;
  char *p, *fp, *fpp;
  int issetdest;
  char fontname[TBUF];

  char texbindir[TBUF];
  char fullbin[TBUF];

  kpse_set_program_name (av[0], NULL);
  progname = kpse_program_name;

/*
 * get tex binary dir
 *
 */
  p = kpse_var_value("SELFAUTOLOC");
  if(p == 0) {
     fprintf(stderr, "I cannot get SELFAUTOLOC\n");
     exit(100);
  }
  strcpy(texbindir, p);
  free(p);
  for(p=texbindir; *p; p++) {
     if(*p == '/') *p = '\\';
  }
  *p = '\\';
  *(p+1) = '\0';

  tmp = getenv ("TEMP");
  if (!tmp)
    tmp = getenv ("TMP");
  if (!tmp)
    tmp = getenv ("TMPDIR");
  if (!tmp) {
    fprintf (stderr, "Please define TEMP | TMP | TMPDIR.\n");
    return (100);
  }

  tmp = xstrdup(tmp);

  for (fpp = tmp; *fpp; fpp++) {
    if (IS_KANJI(fpp))
      fpp++;
    else if (*fpp == '\\')
      *fpp = '/';
  }
/*
issetdest = 0 : TDS
issetdest = 1 : user setting
issetdest = 2 : current directory
*/

  issetdest = 0;

  if (ac < 2) {
    usage ();
    free(tmp);
    return (100);
  }

  if ((!strcmp (av[1], "--version")) || (!strcmp (av[1], "-version"))) {
    version ();
    free(tmp);
    return (100);
  }

  if ((!strcmp (av[1], "--help")) || (!strcmp (av[1], "-help"))) {
    help ();
    free(tmp);
    return (100);
  }

  for (i = 0; i < 4; i++)
    arg[i] = (char *) malloc (TBUF);

  if ((!strcmp (av[1], "--destdir")) || (!strcmp (av[1], "-destdir"))) {
    if (ac != 4) {
      usage ();
      relmem (arg);
      free(tmp);
      return (100);
    }
    issetdest = 1;
    if (strlen(av[2]) > TBUF - 1 || strlen(av[3]) > TBUF - 1) {
      fprintf (stderr, "Too long a string.\n");
      return (100);
    }
    strcpy (buff, av[2]);
    strcpy (fontname, av[3]);
    for (p = buff; *p; p++) {
      if (IS_KANJI(p))
        p++;
      else if (*p == '\\')
        *p = '/';
    }
  } else {
    if (strlen(av[1]) > TBUF - 1) {
      fprintf (stderr, "Too long a string.\n");
      return (100);
    }
    strcpy (fontname, av[1]);
  }


  /* fontname = font name
   */
  if ((p = strrchr (fontname, '.')))
    *p = '\0';

  /* mffile is METAFONT file name
   */
  strcpy (mffile, fontname);
  strcat (mffile, ".mf");

  if (!(fp = kpse_var_value ("MFINPUTS"))) {
    fprintf (stderr, "Cannot get value of MFINPUTS\n");
    relmem (arg);
    free(tmp);
    return (100);
  }

  free (fp);

  xputenv("MKTEXMF", "1");
  if (!(p = kpse_find_file (mffile, kpse_mf_format, 1))) {
    fprintf (stderr, "Cannot find %s.\n", mffile);
    relmem (arg);
    free(tmp);
    return (100);
  }

  fpp = _getcwd (currdir, TBUF);
  if (!fpp) {
    fprintf (stderr, "Failed to get current working directory.\n");
    relmem (arg);
    free(tmp);
    return (100);
  }
  for (fpp = currdir; *fpp; fpp++) {
    if (IS_KANJI(fpp))
      fpp++;
    else if (*fpp == '\\')
      *fpp = '/';
  }

  i = (int)strlen (currdir);
  if (currdir[i - 1] == '/')
    currdir[i - 1] = '\0';
  strcpy (kpsedot, "KPSE_DOT=.;");
  strcat (kpsedot, currdir);
  _putenv (kpsedot);

  if ((p[0] == '.') && (p[1] == '/') && (issetdest != 1)) {
    issetdest = 2;
    strcpy (buff, currdir);
  }

  if (issetdest == 0) {
    /* now path of ${name}.mf is in p */
    strcpy (arg[0], "Dummy");
    strcpy (arg[1], "tfm");
    strcpy (arg[2], p);

    if (!(p = getdestdir (3, arg))) {
      fprintf (stderr, "Cannot get destination directory name.\n");
      relmem (arg);
      free(tmp);
      return (100);
    }
    strcpy (buff, p);
  }

/* Now buff is the destdir */
  p = buff;

  i = (int)strlen (p);

  if (p[i - 1] != '/')
    strcat (p, "/");
  strcat (p, fontname);
  strcat (p, ".tfm");

/* now p (or buff) is the full path name of the tfm font */
/* check if it exists */
  if (_access (p, 0) == 0) {
    fprintf (stderr, "%s exists\n", p);
    printf ("%s\n", p);
    relmem (arg);
    free(tmp);
    return (0);
  }

  cdrive = _getdrive ();
  if (tmp[1] == ':') {
    tdrive = tolower (*tmp) - 'a' + 1;
    _chdrive (tdrive);
  }
  _chdir (tmp);

/* save stdout and stdin */
  savo = _dup (fileno (stdout));
  savi = _dup (fileno (stdin));

/* connect stdout to stderr */
  _dup2 (fileno (stderr), fileno (stdout));

/* connect stdin to nul device */
  if (!(fnul = fopen ("nul", "r"))) {
    fprintf (stderr, "Cannot open nul device to read\n");
    relmem (arg);
    _chdrive (cdrive);
    _chdir (currdir);
    free(tmp);
    return (100);
  }
  _dup2 (fileno (fnul), fileno (stdin));

/* METAFONT command line */
  strcpy (cmd, "--progname=mf --base=mf ");
  strcat (cmd, "\\mode:=ljfour; \\mag:=1; nonstopmode; input ");
  strcat (cmd, fontname);
  strcat (cmd, ";");

  strcpy (execfile, "mf-nowin.exe");
  fprintf (stderr, "%s %s\n", execfile, cmd);
  strcpy(fullbin, texbindir);
  strcat(fullbin, execfile);
  (void) _spawnlp (_P_WAIT, fullbin, execfile, cmd, NULL);

/* return to original stdout and stdin */
  _dup2 (savo, fileno (stdout));
  close (savo);
  _dup2 (savi, fileno (stdin));
  close (savi);

/* close nul device */
  fclose (fnul);

/* check consistency */
  strcpy (cmd, fontname);
  strcat (cmd, ".600gf");

  if (_access (cmd, 0) == -1) {
    fprintf (stderr, "METAFONT failed to make gf font.\n");
    relmem (arg);
    _chdrive (cdrive);
    _chdir (currdir);
    free(tmp);
    return (100);
  }

  remove (cmd);

  strcpy (cmd, fontname);
  strcat (cmd, ".tfm");

/* copy the tfm file */
  if (!(fr = fopen (cmd, "rb"))) {
    fprintf (stderr, "Cannot open %s to read\n", cmd);
    _chdrive (cdrive);
    _chdir (currdir);
    relmem (arg);
    free(tmp);
    return (100);
  }
  if (!(fw = fopen (buff, "wb"))) {
    fprintf (stderr, "Cannot open %s to write\n", buff);
    _chdrive (cdrive);
    _chdir (currdir);
    relmem (arg);
    free(tmp);
    return (100);
  }

  while ((i = (int)fread (rbuff, 1, TBUF, fr)))
    fwrite (rbuff, 1, i, fw);
  fclose (fr);
  fclose (fw);

  strcpy(savebuff, buff);

/* 
  copy log file into the current directory
  in the case that issetdest == 2,
  because feynmf package requires the
  log file.
*/

  if(issetdest == 2) {
    i = (int)strlen(buff);
    if(i > 3) {
      i -= 4;
      buff[i] = '\0';
      strcat(buff, ".log");
      strcpy(cmd, fontname);
      strcat(cmd, ".log");
      if (!(fr = fopen (cmd, "rb"))) {
        fprintf (stderr, "Cannot open %s to read\n", cmd);
        _chdrive (cdrive);
        _chdir (currdir);
        relmem (arg);
        free(tmp);
        return (100);
      }
      if (!(fw = fopen (buff, "wb"))) {
        fprintf (stderr, "Cannot open %s to write\n", buff);
        _chdrive (cdrive);
        _chdir (currdir);
        relmem (arg);
        free(tmp);
        return (100);
      }
      while ((i = (int)fread (rbuff, 1, TBUF, fr)))
        fwrite (rbuff, 1, i, fw);
      fclose (fr);
      fclose (fw);
    }
  }

  relmem (arg);
  if(issetdest != 2)
    mktexupd (savebuff);

/* erase files */
  strcpy (cmd, fontname);
  strcat (cmd, ".log");
  remove (cmd);

  strcpy (cmd, fontname);
  strcat (cmd, ".tfm");
  remove (cmd);

  _chdrive (cdrive);
  _chdir (currdir);

/* send message to Kpathsea */
  printf ("%s\n", savebuff);
  free(tmp);

  return (0);
}