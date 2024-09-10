struct searchNode *qchanflags_parse(searchCtx *ctx, int argc, char **argv) {
  struct searchNode *thenode;
  struct qchanflags_localdata *localdata;

  if (!(thenode=(struct searchNode *)malloc(sizeof (struct searchNode)))) {
    parseError = "malloc: could not allocate memory for this search.";
    return NULL;
  }

  thenode->localdata=localdata=malloc(sizeof(struct qchanflags_localdata));
  thenode->returntype = RETURNTYPE_INT;
  thenode->exe = qchanflags_exe;
  thenode->free = qchanflags_free;

  if (argc==0) {
    localdata->setmodes=0;
    localdata->clearmodes=0;
  } else {
    struct searchNode *arg;
    char *p;

    localdata->setmodes=0;
    localdata->clearmodes=~0;

    if (!(arg=argtoconststr("qchanflags", ctx, argv[0], &p))) {
      free(thenode);
      return NULL;
    }

    setflags(&(localdata->setmodes), QCFLAG_ALL, p, rcflags, REJECT_NONE);
    setflags(&(localdata->clearmodes), QCFLAG_ALL, p, rcflags, REJECT_NONE);
    arg->free(ctx, arg);

    localdata->clearmodes = ~localdata->clearmodes;
  }

  return thenode;
}