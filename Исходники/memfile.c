/*
 * Sync the memory file *mfp to disk.
 * Flags:
 *  MFS_ALL	If not given, blocks with negative numbers are not synced,
 *		even when they are dirty!
 *  MFS_STOP	Stop syncing when a character becomes available, but sync at
 *		least one block.
 *  MFS_FLUSH	Make sure buffers are flushed to disk, so they will survive a
 *		system crash.
 *  MFS_ZERO	Only write block 0.
 *
 * Return FAIL for failure, OK otherwise
 */
    int
mf_sync(memfile_T *mfp, int flags)
{
    int		status;
    bhdr_T	*hp;
#if defined(SYNC_DUP_CLOSE)
    int		fd;
#endif
    int		got_int_save = got_int;

    if (mfp->mf_fd < 0)	    /* there is no file, nothing to do */
    {
	mfp->mf_dirty = FALSE;
	return FAIL;
    }

    /* Only a CTRL-C while writing will break us here, not one typed
     * previously. */
    got_int = FALSE;

    /*
     * sync from last to first (may reduce the probability of an inconsistent
     * file) If a write fails, it is very likely caused by a full filesystem.
     * Then we only try to write blocks within the existing file. If that also
     * fails then we give up.
     */
    status = OK;
    for (hp = mfp->mf_used_last; hp != NULL; hp = hp->bh_prev)
	if (((flags & MFS_ALL) || hp->bh_bnum >= 0)
		&& (hp->bh_flags & BH_DIRTY)
		&& (status == OK || (hp->bh_bnum >= 0
		    && hp->bh_bnum < mfp->mf_infile_count)))
	{
	    if ((flags & MFS_ZERO) && hp->bh_bnum != 0)
		continue;
	    if (mf_write(mfp, hp) == FAIL)
	    {
		if (status == FAIL)	/* double error: quit syncing */
		    break;
		status = FAIL;
	    }
	    if (flags & MFS_STOP)
	    {
		/* Stop when char available now. */
		if (ui_char_avail())
		    break;
	    }
	    else
		ui_breakcheck();
	    if (got_int)
		break;
	}

    /*
     * If the whole list is flushed, the memfile is not dirty anymore.
     * In case of an error this flag is also set, to avoid trying all the time.
     */
    if (hp == NULL || status == FAIL)
	mfp->mf_dirty = FALSE;

    if ((flags & MFS_FLUSH) && *p_sws != NUL)
    {
#if defined(UNIX)
# ifdef HAVE_FSYNC
	/*
	 * most Unixes have the very useful fsync() function, just what we need.
	 * However, with OS/2 and EMX it is also available, but there are
	 * reports of bad problems with it (a bug in HPFS.IFS).
	 * So we disable use of it here in case someone tries to be smart
	 * and changes os_os2_cfg.h... (even though there is no __EMX__ test
	 * in the #if, as __EMX__ does not have sync(); we hope for a timely
	 * sync from the system itself).
	 */
#  if defined(__EMX__)
   error "Don't use fsync with EMX! Read emxdoc.doc or emxfix01.doc for info."
#  endif
	if (STRCMP(p_sws, "fsync") == 0)
	{
	    if (fsync(mfp->mf_fd))
		status = FAIL;
	}
	else
# endif
	    /* OpenNT is strictly POSIX (Benzinger) */
	    /* Tandem/Himalaya NSK-OSS doesn't have sync() */
	    /* No sync() on Stratus VOS */
# if defined(__OPENNT) || defined(__TANDEM) || defined(__VOS__)
	    fflush(NULL);
# else
	    sync();
# endif
#endif
#ifdef VMS
	if (STRCMP(p_sws, "fsync") == 0)
	{
	    if (fsync(mfp->mf_fd))
		status = FAIL;
	}
#endif
#ifdef SYNC_DUP_CLOSE
	/*
	 * Win32 is a bit more work: Duplicate the file handle and close it.
	 * This should flush the file to disk.
	 */
	if ((fd = dup(mfp->mf_fd)) >= 0)
	    close(fd);
#endif
#ifdef AMIGA
# if defined(__AROS__) || defined(__amigaos4__)
	if (fsync(mfp->mf_fd) != 0)
	    status = FAIL;
# else
	/*
	 * Flush() only exists for AmigaDos 2.0.
	 * For 1.3 it should be done with close() + open(), but then the risk
	 * is that the open() may fail and lose the file....
	 */
#  ifdef FEAT_ARP
	if (dos2)
#  endif
#  ifdef SASC
	{
	    struct UFB *fp = chkufb(mfp->mf_fd);

	    if (fp != NULL)
		Flush(fp->ufbfh);
	}
#  else
#   if defined(_DCC) || defined(__GNUC__) || defined(__MORPHOS__)
	{
#    if defined(__GNUC__) && !defined(__MORPHOS__) && defined(__libnix__)
	    /* Have function (in libnix at least),
	     * but ain't got no prototype anywhere. */
	    extern unsigned long fdtofh(int filedescriptor);
#    endif
#    if !defined(__libnix__)
	    fflush(NULL);
#    else
	    BPTR fh = (BPTR)fdtofh(mfp->mf_fd);

	    if (fh != 0)
		Flush(fh);
#    endif
	}
#   else /* assume Manx */
	    Flush(_devtab[mfp->mf_fd].fd);
#   endif
#  endif
# endif
#endif /* AMIGA */
    }