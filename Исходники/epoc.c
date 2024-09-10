int
do_aspawn ( void *vreally, void **vmark, void **vsp) {

    dTHX;

    SV *really = (SV*)vreally;
    SV **mark = (SV**)vmark;
    SV **sp = (SV**)vsp;

    char **argv;
    char *str;
    char *p2, **ptr;
    char *cmd;


    int  rc;
    int index = 0;

    if (sp<=mark)
      return -1;
    
    ptr = argv =(char**) malloc ((sp-mark+3)*sizeof (char*));
    
    while (++mark <= sp) {
      if (*mark && (str = SvPV_nolen(*mark)))
	argv[index] = str;
      else
	argv[index] = "";
    }
    argv[index++] = 0;

    cmd = strdup((const char*)(really ? SvPV_nolen(really) : argv[0]));

    rc = spawnvp( P_WAIT, cmd, argv);
    free( argv);
    free( cmd);

    return rc;
}