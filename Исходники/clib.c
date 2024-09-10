BCPLWORD dosys(register BCPLWORD *p, register BCPLWORD *g)
{ register BCPLWORD i;
  /*PRINTFD("dosys(%" FormD ", ", (BCPLWORD)p); */
  /*PRINTFD("%" FormD, g); */
  /*PINTFD(") P3=%" FormD " ", p[3]); */
  /*PRINTFD("P4=%" FormD "\n",  p[4]); */

  switch((int)(p[3]))
  { default: printf("\nBad sys %ld\n", (long)p[3]);  return p[3];
  
    /* case Sys_setcount: set count               -- done in cinterp
    ** case Sys_quit:     return from interpreter -- done in cinterp

    ** case Sys_rti:      sys(Sys_rti, regs)      -- done in cinterp  Cintpos
    ** case Sys_saveregs: sys(Sys_saveregs, regs) -- done in cinterp  Cintpos
    ** case Sys_setst:    sys(Sys_setst, st)      -- done in cinterp  Cintpos
    */
    case Sys_tracing:  /* sys(Sys_tracing, b)  */
      tracing = p[4];
      return 0;
    /* case Sys_watch:    sys(Sys_watch, addr)    -- done in cinterp
    */
    /*
    case  Sys_tally:         // sys(Sys_tally, flag) 
      if(p[4]) {
        tallylim = tallyupb;
        for(i=1; i<=tallylim; i++) tallyv[i] = 0;
      } else {
        tallylim = 0;
      }
      return 0;
     
    case Sys_interpret: // call interpreter (recursively)
    { BCPLWORD regsv = p[4];
      if(W[regsv+7]>=0 || slowflag) return interpret(regsv, W);
      return CINTASM  (regsv, W);
    }
    */

    case Sys_sardch:
    { BCPLWORD ch;
      /*printf("parmp=%d parms[0]=%d\n", parmp, parms[0]); */
      if(parmp<=parms[0]) {  /* Added MR 10/04/06 */
        /* Read the command arguments (without echo) first. */
        /*printf("sardch: parmp=%d parms[0]=%d\n", parmp, parms[0]); */
        /*printf("sardch: returning %d\n", parms[parmp]); */
        return parms[parmp++];
      }
      ch = Readch();
      if (ttyinp) {  /* echo tty input only */
        if (ch>=0) putchar((char)ch);
        if(ch==13) { ch = 10; putchar(10); }
        fflush(stdout);
      }
      return ch;
    }

    case Sys_sawrch:
      if(p[4] == 10) putchar(13);
      putchar((char)p[4]);
      fflush(stdout);
      return 0;

    case Sys_read:  /* bytesread := sys(Sys_read, fp, buf, bytecount) */
    { FILE *fp = findfp(p[4]);
      char *bbuf = (char *)(p[5]<<B2Wsh);
      BCPLWORD len   = p[6];
      len = fread(bbuf, (size_t)1, (size_t)len, fp);
      return len;
    }

    case Sys_write:
      { FILE *fp = findfp(p[4]);
        char *bbuf = (char *)(p[5]<<B2Wsh);
        BCPLWORD len = p[6];
        len = WD fwrite(bbuf, (size_t)1, (size_t)len, fp);
        fflush(fp);
        return len;
      }

    case Sys_openread:
      { char *name = b2c_str(p[4], chbuf1);
        FILEPT fp;
        fp = pathinput(name,                      /* Filename */
                       b2c_str(p[5], chbuf2));    /* Environment variable */
        if(fp==0) return 0L;
        return newfno(fp);
      }

    case Sys_openwrite:
      { char *name = b2c_str(p[4], chbuf1);
        FILEPT fp;
        fp = fopen(osfname(name, chbuf4), "wb");
        if(fp==0) return 0L;
        return newfno(fp);
      }

    case Sys_openappend:
      { char *name = b2c_str(p[4], chbuf1);
        FILEPT fp;
        fp = fopen(osfname(name, chbuf4), "ab");
        if(fp==0) return 0L;
        return newfno(fp);
      }

    case Sys_openreadwrite:
      { char *name = b2c_str(p[4], chbuf1);
	FILEPT fp;
        fp = fopen(osfname(name, chbuf4), "rb+");
        if(fp==0) fp = fopen(name, "wb+");
        if(fp==0) return 0L;
        return newfno(fp);
      }

    case Sys_close:
    { BCPLWORD res = fclose(findfp(p[4]));
      freefno(p[4]);
      return res==0 ? -1 : 0; /* res==0 means success */
    }

    case Sys_deletefile:
    { char *name = b2c_str(p[4], chbuf1);
      FILEPT fp;
      name = osfname(name, chbuf4);
#ifdef VMSNAMES
      { /* Append ';*' to name */
        int len = 0;
        while (name[len]) len++;
        name[len++] = ';';
        name[len++] = '*';
        name[len] = 0;
      }
#endif
      return ! REMOVE(name);
    }

    case Sys_renamefile:
    { char *name1 = b2c_str(p[4], chbuf1);
      char *name2 = b2c_str(p[5], chbuf2);
      int len = 0;
      name1 = osfname(name1, chbuf3);
      name2 = osfname(name2, chbuf4);
#ifdef VMSNAMES
      { /* Append ';*' to name2 */
        len = 0;
        while (name2[len]) len++;
        name2[len]   = ';';
        name2[len+1] = '*';
        name2[len+2] = 0;
      }
#endif
      REMOVE(name2);
#ifdef VMSNAMES
      name2[len] = 0;
#endif
      return ! rename(name1, name2);
    }

    case Sys_getvec:
      return ((BCPLWORD)(malloc((1+p[4])<<B2Wsh)))>>B2Wsh;

    case Sys_freevec:
      free((void *)(p[4]<<B2Wsh)); return -1;
/*
    case Sys_loadseg:
      return loadseg(b2c_str(p[4], chbuf1));

    case Sys_globin:
      return globin(p[4], g);

    case Sys_unloadseg:
      unloadseg(p[4]);                    return 0;
*/

    case Sys_muldiv:
      //printf("dosys: calling muldiv(%d, %d, %d)\n", p[4], p[5], p[6]);
    { BCPLWORD res =  muldiv(p[4], p[5], p[6]);
	//printf("res=%d   result2=%d\n", res, result2);
      globbase[Gn_result2] = result2;
      return res;
    }

    case Sys_intflag:
      return intflag() ? -1L : 0L;

/*
    case Sys_setraster:
      return setraster(p[4], p[5]);
*/

    case Sys_cputime: /* Return CPU time in milliseconds  */
      return muldiv(clock(), 1000, TICKS_PER_SEC);

#ifndef forWinCE
    case Sys_filemodtime:
    /* sys(Sys_filemodtime, filename, datv)
       Set the elements of datv to represent the date and time of
       the last modification of the given file, returning TRUE if
       successful and FALSE otherwise. datv!0 is the number of days
       since 1 January 1970, datv!1 is the number of milli-seconds
       since midnight and datv!2=-1 indicating that the new date and
       time format is being used.
       If the file does not exist or there is an error then
       FALSE is returned and the elements of datv are set to 0, 0 and
       -1, respectively.
    */
    { struct stat buf;
      BCPLWORD days, secs, msecs;
      char *name = b2c_str(p[4], chbuf1);
      BCPLWORD *datestamp = (BCPLWORD *)(p[5]<<B2Wsh);
      if (stat(osfname(name, chbuf4), &buf)) {
        datestamp[0] = 0;
        datestamp[1] = 0;
        datestamp[2] = -1;
        return 0;
      }
      secs = buf.st_mtime;
      // nsecs = buf.st_mtimensec; // nano second time, if poss
      days = secs / (24*60*60);
      msecs = (secs % (24*60*60)) * 1000;
      datestamp[0] = days;
      datestamp[1] = msecs;
      datestamp[2] = -1;  // New dat format
      //printf("filemodtime: name=%s days=%" FormD " msecs=%" FormD "\n",
      //        name, days, msecs);
      return -1;
    }
#endif

    case Sys_setprefix: /* Set the file name prefix string  */
    { BCPLWORD str = p[4];
      char *fp = (char*)(str<<B2Wsh);
      char *tp = prefixbp;
      int i, len=*fp;
      if(len>63) return 0;
      for (i=0; i<=len; i++) *tp++ = *fp++;
      return prefixstr;
    }

    case Sys_getprefix: /* Return the file name prefix string  */
      return prefixstr;

    case Sys_graphics: /* Perform an operation on the graphics window  */
      return sysGraphics(p);

    case 35: /* Return TRUE if no keyboard character is available */
#ifdef forWinCE
              return chBufEmpty() ? -1 : 0;
#else
              return -1;
#endif

    case 36:   return 0; /* Spare */

    case 37:   return 0; /* Spare  */

    case Sys_seek:  /* res := sys(Sys_seek, fd, pos)   */
    { FILEPT fp = findfp(p[4]);
      BCPLWORD pos = p[5];
      BCPLWORD res = fseek(fp, pos, SEEK_SET);
      /*printf("fseek => res=%d errno=%d\n", res, errno); */
      /*g[Gn_result2] = errno; */
      return res==0 ? -1 : 0; /* res=0 succ, res=-1 error  */
    }

    case Sys_tell: /* pos := sys(Sys_tell,fd)  */
    { FILE *fp = findfp(p[4]);
      BCPLWORD pos = ftell(fp);
      /*g[Gn_result2] = errno; */
      return pos; /* >=0 succ, -1=error */
    }

    case Sys_waitirq: /* Wait for irq */
      /*
      pthread_mutex_lock  (         &irq_mutex);
      pthread_cond_wait   (&irq_cv, &irq_mutex);
      pthread_mutex_unlock(         &irq_mutex);
      */
      return 0;

    case Sys_lockirq: /* Stop all devices from modifying */
                      /* packets or generating interrupts */
      /*
      pthread_mutex_lock(&irq_mutex);
      */
      return 0;

    case Sys_unlockirq: /* Allow devices to modify packets */
                        /* and generate interrupts */
      /*
      pthread_mutex_unlock(&irq_mutex);
      */
      return 0;

    case Sys_devcom: /* res := sys(Sys_devcom, dcb, com, arg) */
      return 0; /*devcommand(W[p+4], W[p+5], W[p+6]); */

    case Sys_datstamp: /* res := sys(Sys_datstamp, v)  */
    // Set v!0 = days  since 1 January 1970
    //     v!1 = msecs since midnight
    //     v!2 = ticks =-1 for new dat format
    // Return -1 if successful
      return timestamp((BCPLWORD*)(p[4]));

    case Sys_filesize:  /* res := sys(Sys_filesize, fd)   */
      { FILEPT fp   = findfp(p[4]);
        long pos  = ftell(fp);
        BCPLWORD rc   = fseek(fp, 0, SEEK_END);
        BCPLWORD size = ftell(fp);
        rc  = fseek(fp, pos, SEEK_SET);
        if (rc) size = -1;
        return size; /* >=0 succ, -1=error  */
      }

     case Sys_getsysval: /* res := sys(Sys_getsysval, addr) */
     { BCPLWORD *addr = (BCPLWORD*)p[4];
       return *addr;
     }

     case Sys_putsysval: /* res := sys(Sys_putsysval, addr, val) */
     { BCPLWORD *addr = (BCPLWORD*)p[4];
       *addr = p[5];
       return 0;
     }

     case Sys_shellcom: /* res := sys(Sys_shellcom, comstr) */
     { char *comstr = (char*)(p[4]<<2);
       int i;
       char com[256];
       int len = strlen(comstr);
       for(i=0; i<len; i++) com[i] = comstr[i+1];
       com[len] = 0;
       /*
       printf("\ndosys: calling shell command %s\n", com);
       */
       return system(com);
     }

     case Sys_getpid: /* res := sys(Sys_getpid) */
       return getpid();

     case Sys_dumpmem: /* sys(Sys_dumpmem, context) */
       printf("\nCintpos memory not dumped to DUMP.mem\n");
       return 0;

     case Sys_callnative:
     { /* Call native code. */
       int(*rasmfn)(void) = (int(*)(void))&p[4];
       return rasmfn();
     }              

    case Sys_platform:
              { /* Return platform code, 0 if unknown */
		BCPLWORD res = 0;
#ifdef forMAC
		res = 1;
#endif
#ifdef forMIPS
		res = 2;
#endif
#ifdef forSGI
		res = 3;
#endif
#ifdef forARM
		res = 4;
#endif
#ifdef forLINUX
		res = 5;
#endif
#ifdef forLINUXamd64
		res = 6;
#endif
#ifdef forCYGWIN32
		res = 7;
#endif
#ifdef forLINUXPPC
		res = 8;
#endif
#ifdef forSUN4
		res = 9;
#endif
#ifdef forSPARC
		res = 10;
#endif
#ifdef forALPHA
		res = 11;
#endif
#ifdef forMSDOS
		res = 12;
#endif
#ifdef forOS2
		res = 13;
#endif
#ifdef forSHwinCE
		res = 14;
#endif
#ifdef forMIPSwinCE
		res = 15;
#endif
                return res;
              }              

    case Sys_inc: /* newval := sys(Sys_inc, ptr, amount) */
              { /* !ptr := !ptr + amount; RESULTIS !ptr */
                return 0; /**p[4] += p[5];*/
              }

    case Sys_buttons: /* Return bit pattern of buttons currently
                          pressed on the GP2X */
#ifdef forGP2X
              { unsigned long buttons = 0;
	        int fd = open("/dev/GPIO", O_RDWR | O_NDELAY);
	        if (fd<0) return -1;
                if (read(fd, &buttons, 4) != 4) return -2;
                close(fd);
                return (BCPLWORD)buttons;
              }
#else
              return -3;

#endif

    case Sys_delay: /* sys(Sys_delay, msecs) */
              { unsigned int msecs = (unsigned int)p[4];
                msecdelay(msecs);
                return 0;
              }

    case Sys_sound: /* res := sys(Sys_sound, fno, a1, a2,...) */
#ifdef SOUND
                return soundfn(&p[4], &g[0]);
#else
                return 0;
#endif

    case Sys_sdl: /* res := sys(Sys_sdl, fno, a1, a2,...) */
#ifdef SDLavail
      return sdlfn(&((BCPLWORD*)p)[4], &((BCPLWORD*)g)[0], 0/*W*/);
#else
      return 0;
#endif

    case Sys_callc: /* res := sys(Sys_callc, fno, a1, a2,...) */
#ifdef CALLC
      /*
         printf("dosys: sys(Sys_callc, %" FormD ", %" FormD ", %" FormD", ...)\n",
                 W[p+4], W[p+5], W[p+6]);
      */
      return 0;//callc(&p[4], &g[0]);
#else
                return -1;
#endif

    case Sys_trpush: /* sys(Sys_trpush, val) */
                trpush(p[4]);
                return 0;

    case Sys_settrcount: /* res := sys(Sys_settrcount, count) */
                return settrcount(p[4]);

    case Sys_gettrval: /* res := sys(Sys_gettrval, count) */
                return gettrval(p[4]);

    case Sys_flt: /* res := sys(Sys_flt, op, a, b)) */
              { BCPLWORD res = doflt(p[4], p[5], p[6], p[7]);
                globbase[Gn_result2] = result2;
		//g[Gn_result2] = result2;
		//if(W[p+4]==35)
		//printf("sys_flt: op=%d res=%08" FormX " result2=%08" FormX "\n",
                //       W[p+4], (UBCPLWORD)res, (UBCPLWORD)result2);
                return res;
              }

    case Sys_pollsardch: /* res := sys(Sys_pollsardch) */
              {
                // Return a character if available otherwise pollch (=-3)
                return pollReadch();
              }

    case Sys_incdcount: /* res := sys(Sys_incdcount, n) */
                return incdcount(p[4]);


		//#ifndef forWinCE
    case 135:
    { /* Return system date and time in VEC 5 */
      time_t clk = time(0);
      struct tm *now = gmtime(&clk);
      BCPLWORD *arg = PT(p[4] << B2Wsh);
      arg[0] = now->tm_year+1900;
      arg[1] = now->tm_mon+1;
      arg[2] = now->tm_mday;
      arg[3] = now->tm_hour;
      arg[4] = now->tm_min;
      arg[5] = now->tm_sec;
      return 0;
    }

    case 136: /* Return current directory in VEC 1 + 256/bytesperword */
    { char *res = getcwd(chbuf1, 256);
      c2b_str(chbuf1, p[4]);
      return 0;
    }

    case 137:
      return (BCPLWORD)parms >> B2Wsh;
  }
  // This is unreadchable
  // return 0;
}