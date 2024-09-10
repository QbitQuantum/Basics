int csu_dodomainmode(void *source, int cargc, char **cargv) {
  maildomain *mdp; 
  nick *sender=source;
  flag_t forceflags, currentflags;
  char buf1[60];
  int carg=2,limdone=0,actlimdone=0;
  unsigned int newlim=0;
  unsigned int newactlim=0;

  if (cargc<1) {
    chanservstdmessage(sender,QM_NOTENOUGHPARAMS,"domainmode");
    return CMD_ERROR;
  }

  if (checkdomain(cargv[0])) {
    chanservstdmessage(sender,QM_INVALIDDOMAIN,cargv[0]);
    return CMD_ERROR;
  }

  if(!(mdp=findorcreatemaildomain(cargv[0]))) {
    return CMD_ERROR;
  }

  if (cargc>1) {
    /* Save the current modes.. */
    strcpy(buf1,getdomainmode(mdp));

    /* Pick out the + flags: start from 0 */
    forceflags=0;
    setflags(&forceflags, MDFLAG_ALL, cargv[1], mdflags, REJECT_NONE);
    currentflags=mdp->flags;
    setflags(&currentflags, MDFLAG_ALL, cargv[1], mdflags, REJECT_NONE);

    if ((forceflags & MDFLAG_LIMIT) &&
        (!(forceflags & MDFLAG_ACTLIMIT) || strrchr(cargv[1],'l') < strrchr(cargv[1],'u'))) {
      if (cargc<=carg) {
        chanservstdmessage(sender,QM_NOTENOUGHPARAMS,"domainmode");
        return CMD_ERROR;
      }
      newlim=strtol(cargv[carg++],NULL,10);
      limdone=1;
    }

    if ((forceflags & MDFLAG_LIMIT) && !limdone) {
      if (cargc<=carg) {
        chanservstdmessage(sender,QM_NOTENOUGHPARAMS,"domainmode");
        return CMD_ERROR;
      }
      newlim=strtol(cargv[carg++],NULL,10);
      limdone=1;
    }

    if ((forceflags & MDFLAG_ACTLIMIT) && !actlimdone) {
      if (cargc<=carg) {
        chanservstdmessage(sender,QM_NOTENOUGHPARAMS,"chanmode");
        return CMD_ERROR;
      }
      newactlim=strtol(cargv[carg++],NULL,10);
      actlimdone=1;
    }

    /* It parsed OK, so update the structure.. */
    mdp->flags=currentflags;
    if(actlimdone)
      mdp->actlimit=newactlim; 
    if(!(currentflags & MDFLAG_ACTLIMIT))
      mdp->actlimit=0;
    if(limdone)
      mdp->limit=newlim;
    if(!(currentflags & MDFLAG_LIMIT))
      mdp->limit=0;
    if(mdp->ID) {
      if(mdp->flags) {
        csdb_updatemaildomain(mdp);
      } else {
        csdb_deletemaildomain(mdp);
      }
    } else {
      mdp->ID=++lastdomainID;
      csdb_createmaildomain(mdp);
    }

    chanservstdmessage(sender, QM_DONE);
    cs_log(sender,"DOMAINMODE %s %s (%s -> %s)",mdp->name->content,cargv[1],buf1,getdomainmode(mdp));
  }
  chanservstdmessage(sender,QM_CURDOMAINMODES,mdp->name->content,getdomainmode(mdp));
 
  return CMD_OK;
}