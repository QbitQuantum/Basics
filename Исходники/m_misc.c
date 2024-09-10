void M_LoadDefaults (void)
{
  int   i;
  int   len;
  FILE* f;
  char  def[80];
  char  strparm[100];
  char* newstring = NULL;   // killough
  int   parm;
  boolean isstring;

  // set everything to base values

  numdefaults = sizeof(defaults) / sizeof(defaults[0]);
  for (i = 0 ; i < numdefaults ; i++) {
    if (defaults[i].location.ppsz)
      *defaults[i].location.ppsz = strdup(defaults[i].defaultvalue.psz);
    if (defaults[i].location.pi)
      *defaults[i].location.pi = defaults[i].defaultvalue.i;
  }

  // check for a custom default file

#if ((defined GL_DOOM) && (defined _MSC_VER))
#define BOOM_CFG "glboom.cfg"
#else
#define BOOM_CFG "prboom.cfg"
#endif

  i = M_CheckParm ("-config");
  if (i && i < myargc-1)
    defaultfile = strdup(myargv[i+1]);
  else {
    const char* exedir = I_DoomExeDir();
    /* get config file from same directory as executable */
#if 1
	int len = doom_snprintf(NULL, 0, BOOM_CFG);
	defaultfile = malloc(len+1);
	doom_snprintf(defaultfile, len+1, BOOM_CFG);
#else
    int len = doom_snprintf(NULL, 0, "%s/" BOOM_CFG, exedir);
    defaultfile = malloc(len+1);
    doom_snprintf(defaultfile, len+1, "%s/" BOOM_CFG, exedir);
#endif
  }

  lprintf (LO_CONFIRM, " default file: %s\n",defaultfile);

  // read the file in, overriding any set defaults

  f = fopen (defaultfile, "r");
  if (f)
    {
    while (!feof(f))
      {
      isstring = false;
      if (fscanf (f, "%79s %[^\n]\n", def, strparm) == 2)
        {

        //jff 3/3/98 skip lines not starting with an alphanum

        if (!isalnum(def[0]))
          continue;

        if (strparm[0] == '"') {
          // get a string default

          isstring = true;
          len = strlen(strparm);
          newstring = (char *) malloc(len);
          strparm[len-1] = 0; // clears trailing double-quote mark
          strcpy(newstring, strparm+1); // clears leading double-quote mark
  } else if ((strparm[0] == '0') && (strparm[1] == 'x')) {
    // CPhipps - allow ints to be specified in hex
    sscanf(strparm+2, "%x", &parm);
  } else {
          sscanf(strparm, "%i", &parm);
    // Keycode hack removed
  }

        for (i = 0 ; i < numdefaults ; i++)
          if ((defaults[i].type != def_none) && !strcmp(def, defaults[i].name))
            {
      // CPhipps - safety check
            if (isstring != IS_STRING(defaults[i])) {
        lprintf(LO_WARN, "M_LoadDefaults: Type mismatch reading %s\n", defaults[i].name);
        continue;
      }
            if (!isstring)
              {

              //jff 3/4/98 range check numeric parameters

              if ((defaults[i].minvalue==UL || defaults[i].minvalue<=parm) &&
                  (defaults[i].maxvalue==UL || defaults[i].maxvalue>=parm))
                *(defaults[i].location.pi) = parm;
              }
            else
              {
                union { const char **c; char **s; } u; // type punning via unions

                u.c = defaults[i].location.ppsz;
                free(*(u.s));
                *(u.s) = newstring;
              }
            break;
            }
        }
      }

    fclose (f);
    }
  //jff 3/4/98 redundant range checks for hud deleted here
}