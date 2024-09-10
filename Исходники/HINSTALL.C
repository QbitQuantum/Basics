/*
 * Install hard disk driver.
 *
 */
install()
{
    int i, pdev, ldev;
    int maxsiz;
    char *s, *d, sdev, dvr[15];
    char *lbuf;
    extern char rootstart, rootend;
    extern char bootstart, bootend;

    if ((ldev = glogdev()) < 0) 
	return BAILOUT;
  
    /* final warning */
    sdev = ldev + 'C';
    (instfnl[INSTDRV].ob_spec)->te_ptext = &sdev;
    instfnl[INSTOK].ob_state = NORMAL;
    instfnl[INSTCN].ob_state = NORMAL;
    if (execform(instfnl) != INSTOK) return BAILOUT;

    /* find maximum sector size on system */
    if (!vernum)	    /* new version of AHDI? */
	maxsiz = 512;	    /* if not, sector size is always 512 bytes */
    else
	maxsiz = *(vernum + 1);	/* max sector size kept after version # */

    if (!(lbuf = Malloc((long)maxsiz))) {
	err(nomemory);
	return ERROR;
    }

    /* find which physical unit the chosen logical drive belongs to */
    pdev = physdev[ldev];
    pdev &= 0x1f;		/* mask off extra bits */
      
    /* Remove old driver if there is one */
    dvr[0] = sdev;
    strcpy(&dvr[1], OLDDVR);
    if (!(Fsfirst(dvr, 0x04)))	/* 0x04 = system files */
	Fdelete(dvr);
          
  
    /* copy driver to specified unit */
    if (copydvr(sdev) != OK)
	return ERROR;

    /* read in the root sector */
    if (getroot(pdev, lbuf) != 0) {
	err(rootread);
	goto argh;
    }
  
    /* copy boot code into root sector */
    for (d = lbuf, s = &rootstart, i = &rootend - &rootstart; i--;)
	*d++ = *s++;

    /* if gemroot() is not successful, return with error */
    if (gemroot(lbuf, 1) != 0) {
	err(cantinst);
	goto argh;
    }

    /* write installed root sector back to disk */  
    if (putroot(pdev, lbuf) != 0) {
	err(rootwrit);
	goto argh;
    }

    /* read boot sector from partition */
    if (getboot(ldev, lbuf) != 0) {
	err(bootread);
	goto argh;
    }

    /* 
     * copy boot code to boot sector, avoiding the BPB information 
     * copy bytes 0..1 for BRA.S to code;
     * leave bytes 2..$1d unaltered (information for BPB);
     * copy bytes $1e..$1fe for code.
     */
    s = &bootstart;
    d = lbuf;
    *d++ = *s++;
    *d++ = *s++;
    d += 0x1c;
    s += 0x1c;
    for (i = &bootend-&bootstart-0x1e; i--;)
	*d++ = *s++;

    /* make the image executable */
    Protobt(lbuf, -1L, -1, 1);

    /* write the installed boot sector back to disk */
    if (putboot(ldev, lbuf) != 0) {
	err(bootwrit);
	goto argh;
    }

    return;

argh:
    dvr[0] = sdev;
    strcpy(&dvr[1], DVRNAME);
    Fdelete(dvr);
}