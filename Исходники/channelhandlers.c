int handleburstmsg(void *source, int cargc, char **cargv) {
  channel *cp;
  time_t timestamp;
  int wipeout=0;
  int i;
  int arg=0;
  char *charp;
  int newlimit;
  int waslimit,waskeyed;
  char *nextnum;
  unsigned long currentmode;
  int isnewchan;
  
  /* (we don't see the first 2 params in cargc) */
  /* AK B #+lod+ 1017561154 +tnk eits ATJWu:o,AiW1a,Ag3lV,AiWnl,AE6oI :%*[email protected] */
  
  if (cargc<2) {
    Error("channel",ERR_WARNING,"Burst message with only %d parameters",cargc);
    return CMD_OK;
  }
  
  timestamp=strtol(cargv[1],NULL,10);
  
  if ((cp=findchannel(cargv[0]))==NULL) {
    /* We don't have this channel already */
    cp=createchannel(cargv[0]);
    cp->timestamp=timestamp;
    isnewchan=1;
  } else {
    isnewchan=0;
    if (timestamp<cp->timestamp) {
      /* The incoming timestamp is older.  Erase all our current channel modes, and the topic. */
      cp->timestamp=timestamp;
      freesstring(cp->topic);
      cp->topic=NULL;
      cp->topictime=0;
      freesstring(cp->key);
      cp->key=NULL;
      cp->limit=0;
      cp->flags=0;
      clearallbans(cp);
      /* Remove all +v, +o we currently have */
      for(i=0;i<cp->users->hashsize;i++) {
        if (cp->users->content[i]!=nouser) {
          cp->users->content[i]&=CU_NUMERICMASK;
        }
      }
    } else if (timestamp>cp->timestamp) {
      /* The incoming timestamp is greater.  Ignore any incoming modes they may happen to set */
      wipeout=1;
    }
  }

  /* OK, dealt with the name and timestamp. 
   * Loop over the remaining args */
  for (arg=2;arg<cargc;arg++) {
    if (cargv[arg][0]=='+') {
      /* Channel modes */
      if (wipeout) {
        /* We ignore the modes, but we need to see if they include +l or +k 
         * so that we can ignore their corresponding values */
        for (charp=cargv[arg];*charp;charp++) {
          if (*charp=='k' || *charp=='l') {
            arg++;
          }
        }
      } else {
        /* Clear off the limit and key flags before calling setflags so we can see if the burst tried to set them */
        /* If the burst doesn't set them, we restore them afterwards */
        waslimit=IsLimit(cp); ClearLimit(cp);
        waskeyed=IsKey(cp);   ClearKey(cp);
        /* We can then use the flag function for these modes */
        setflags(&(cp->flags),CHANMODE_ALL,cargv[arg],cmodeflags,REJECT_NONE);
        /* Pick up the limit and key, if they were set.  Note that the limit comes first */
        if (IsLimit(cp)) { /* A limit was SET by the burst */
          if (++arg>=cargc) {
            /* Ran out of args -- damn ircd is spewing out crap again */
            Error("channel",ERR_WARNING,"Burst +l with no argument");
            break; /* "break" being the operative word */
          } else {
            newlimit=strtol(cargv[arg],NULL,10);
          }
          if (cp->limit>0 && waslimit) {
            /* We had a limit before -- we now have the lowest one of the two */
            if (newlimit<cp->limit) {
              cp->limit=newlimit;
            }
          } else {
            /* No limit before -- we just have the new one */
            cp->limit=newlimit;
          }
        } else if (waslimit) {
          SetLimit(cp); /* We had a limit before, but the burst didn't set one.  Restore flag. */
        }
        
        if (IsKey(cp)) { /* A key was SET by the burst */
          if (++arg>=cargc) {
            /* Ran out of args -- oopsie! */
            Error("channel",ERR_WARNING,"Burst +k with no argument");
            break;
          }
          if (waskeyed) {
            /* We had a key before -- alphabetically first wins */
            if (ircd_strcmp(cargv[arg],cp->key->content)<0) {
              /* Replace our key */
              freesstring(cp->key);
              cp->key=getsstring(cargv[arg],KEYLEN);
            }
          } else {
            /* No key before -- just the new one */
            cp->key=getsstring(cargv[arg],KEYLEN);
          }
        } else if (waskeyed) {
          SetKey(cp); /* We had a key before, but the burst didn't set one.  Restore flag. */
        }
      }       
    } else if (cargv[arg][0]=='%') {
      /* We have one or more bans here */
      nextnum=cargv[arg]+1;
      while (*nextnum) {
        /* Split off the next ban */
        for (charp=nextnum;*charp;charp++) {
          if (*charp==' ') {
            *charp='\0';
            charp++;
            break;
          }
        }        
        setban(cp,nextnum);
        nextnum=charp;
      }
    } else {
      /* List of numerics */
      nextnum=charp=cargv[arg];
      currentmode=0;
      while (*nextnum!='\0') {
        /* Step over the next numeric */
        for (i=0;i<5;i++) {
          if (*charp++=='\0')
            break;
        }
        if (i<5) {
          break;
        }
        if (*charp==',') {
          *charp='\0';
          charp++;
        } else if (*charp==':') {
          *charp='\0';
          charp++;
          currentmode=0;
          /* Look for modes */
          for (;*charp;charp++) {
            if (*charp=='v') {
              currentmode|=CUMODE_VOICE;
            } else if (*charp=='o') {
              currentmode|=CUMODE_OP;
            } else if (*charp==',') {
              charp++;
              break;
            }
          }
          /* If we're ignore incoming modes, zap it to zero again */
          if (wipeout) {
            currentmode=0;
          }
        }
        /* OK.  At this point charp points to either '\0' if we're at the end,
         * or the start of the next numeric otherwise.  nextnum points at a valid numeric
         * we need to add, and currentmode reflects the correct mode */
        addnicktochannel(cp,(numerictolong(nextnum,5)|currentmode));
        nextnum=charp;
      }
    }
  }
  if (cp->users->totalusers==0) {
    /* Oh dear, the channel is now empty.  Perhaps one of those 
     * charming empty burst messages you get sometimes.. */
    if (!isnewchan) {
      /* I really don't think this can happen, can it..? */
      /* Only send the LOSTCHANNEL if the channel existed before */
      triggerhook(HOOK_CHANNEL_LOSTCHANNEL,cp);
    }
    delchannel(cp);
  } else {
    /* If this is a new channel, we do the NEWCHANNEL hook also */
    if (isnewchan) {
      triggerhook(HOOK_CHANNEL_NEWCHANNEL,cp);
    }
    /* Just one hook to say "something happened to this channel" */
    triggerhook(HOOK_CHANNEL_BURST,cp);       
  }
   
  return CMD_OK;     
}