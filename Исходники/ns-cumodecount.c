struct searchNode *cumodecount_parse(searchCtx *ctx, int argc, char **argv) {
  struct cumodecount_localdata *localdata;
  struct searchNode *thenode, *flagstr;
  flag_t fset, fclear;
  char *p;

  if (argc!=1) {
    parseError="cumodes: usage: cumodecount (mode string)";
    return NULL;
  }

  if (!(localdata=(struct cumodecount_localdata *)malloc(sizeof(struct cumodecount_localdata)))) {
    parseError = "malloc: could not allocate memory for this search.";
    return NULL;
  }

  fset=0;
  fclear=~0;

  if (!(flagstr=argtoconststr("cumodecount", ctx, argv[0], &p))) {
    localdata->xnode->free(ctx, localdata->xnode);
    free(localdata);
    return NULL;
  }

  setflags(&(fset), CU_ALL, p, cumodecountlist, REJECT_NONE);
  setflags(&(fclear), CU_ALL, p, cumodecountlist, REJECT_NONE);
  flagstr->free(ctx, flagstr);

  localdata->setmodes=0;
  localdata->clearmodes=~0;

  if(fset & CU_OP)
    localdata->setmodes|=CUMODE_OP;
  if(fset & CU_VOICE)
    localdata->setmodes|=CUMODE_VOICE;
  if(!(fclear & CU_OP))
    localdata->clearmodes&=~CUMODE_OP;
  if(!(fclear & CU_VOICE))
    localdata->clearmodes&=~CUMODE_VOICE;

  localdata->clearmodes = ~(localdata->clearmodes);
  
  if (!(thenode=(struct searchNode *)malloc(sizeof(struct searchNode)))) {
    /* couldn't malloc() memory for thenode, so free localdata to avoid leakage */
    parseError = "malloc: could not allocate memory for this search.";
    free(localdata);
    return NULL;
  }

  thenode->returntype  = RETURNTYPE_INT;
  thenode->localdata   = (void *)localdata;
  thenode->exe         = cumodecount_exe;
  thenode->free        = cumodecount_free;

  return thenode;
}