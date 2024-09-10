int DoGet(GetOptionsPtr gopt)
{
	int fd;
	int result;
	string local;
	long fileSize;
	time_t modifTime;
	int doReports;
	struct stat st;
	size_t restartPt;
	const char *mode = "w";
	time_t now;
	XferSpecPtr xp;

	if (gTransferType == 'A') {
		/* Have to set the type here, because GetDateAndSize() may
		 * use the SIZE command, and the result of that depends
		 * on the current transfer type setting.
		 */
		SETASCII;
	} else {
		SetType(gTransferType);
	}
	
	/* See if we can get some info about the file first. */
	fileSize = GetDateAndSize(gopt->rName, &modifTime);
	restartPt = SZ(0);
	doReports = 0;

	if (gopt->outputMode == kDumpToStdout) {
		fd = gStdout;
		STRNCPY(local, kLocalFileIsStdout);
		/* Don't have progress reports going if we're piping or
		 * dumping to the screen.
		 */
	} else {
		GetLocalName(gopt, local);
		if (stat(local, &st) == 0) {
			/* File exists on the local host.  We must decide whether
			 * we really want to fetch this file, since we might have
			 * it here already.  But when in doubt, we will go ahead
			 * and fetch the file.
			 */
			if (gopt->forceReget) {
				/* If the local file is smaller, then we
				 * should attempt to restart the transfer
				 * from where we left off.
				 */
				if ((st.st_size < fileSize) || (fileSize == kSizeUnknown)) {
					restartPt = SZ(st.st_size);
					mode = "a";
					DebugMsg("Manually continuing local file %s.", local);
				} else {
					PrintF("Already have %s with size %lu.\n", gopt->rName, fileSize);
					return (0);
				}
			} else if (!gopt->overwrite) {
				if (modifTime != kModTimeUnknown) {
					/* We know the date of the remote file. */
					DebugMsg("Local file %s has size %lu and is dated %s",
						local,
						(unsigned long) st.st_size,
						ctime(&st.st_mtime)
					);
					if (modifTime < st.st_mtime) {
						/* Remote file is older than existing local file. */
						PrintF("Already have %s.\n", gopt->rName);
						return (0);
					} else if (modifTime == st.st_mtime) {
						/* Remote file is same age. */
						if (fileSize != kSizeUnknown) {
							/* If the local file is smaller, then we
							 * should attempt to restart the transfer
							 * from where we left off, since we the remote
							 * file has the same date.
							 */
							if (st.st_size < fileSize) {
								restartPt = SZ(st.st_size);
								mode = "a";
							} else if (st.st_size == fileSize) {
								PrintF("Already have %s.\n", gopt->rName);
								return (0);
							} else {
								DebugMsg("Overwriting %s; local file has same date,\n",
									gopt->lName);
								DebugMsg("but local file is larger, so fetching remote version anyway.\n");
							}
						} else {
							DebugMsg("Overwriting %s; local file has same date,\n",
									gopt->lName);
							DebugMsg("but can't determine remote size, so fetching remote version anyway.\n");
						}
					} else {
						/* Remote file is more recent.  Fetch the
						 * whole file.
						 */
						DebugMsg("Overwriting %s; remote was newer.\n",
							gopt->lName);
					}
				} else {
					/* We don't know the date of the file.
					 * We won't be able to safely assume anything about
					 * the remote file.  It is legal to have a more
					 * recent remote file (which we don't know), with a
					 * smaller (or greater, or equal even) size.  We
					 * will just have to fetch it no matter what.
					 */
					DebugMsg("Overwriting %s; couldn't determine remote file date.\n",
						gopt->lName);
				}
			} else {
				DebugMsg("Explicitly overwriting %s.\n", gopt->lName);
			}
		} else {
			/* We don't have a local file with the same name as the remote,
			 * but we may also want to avoid doing the transfer of this
			 * file.  For example, this is where we check the remote
			 * file's date if we were told to only get files which are
			 * less than X days old.
			 */
			if (gopt->newer > 0) {
				time(&now);
				if (((unsigned long) now - (unsigned long) (gopt->newer * 86400)) > (unsigned long) modifTime) {
					DebugMsg("Skipping %s, older than %d days.\n",
						gopt->rName, gopt->newer);
					return (0);
				}
			}
		}
		if (*mode == 'w')
			fd = open(local, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			fd = open(local, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd < 0) {
			Error(kDoPerror, "Can't open local file %s.\n", local);
			return (-1);
		}
		doReports = gopt->doReports;
	}

	xp = InitXferSpec();
	xp->netMode = kNetReading;
	xp->outStream = fd;
	
	/* This group is needed for the progress reporting and logging stuff.
	 * Otherwise, it isn't that important.
	 */
	xp->doReports = doReports;
	xp->localFileName = local;
	xp->remoteFileName = gopt->rName;
	xp->expectedSize = fileSize;
	xp->startPoint = restartPt;
	xp->doUTime = gopt->doUTime;
	xp->remoteModTime = modifTime;
	
	if (gTransferType == 'A') {
		result = AsciiGet(xp);
	} else {		
		result = BinaryGet(xp);
	}

	if (fd != gStdout) {
		(void) close(fd);
		if ((result < 0) && (xp->bytesTransferred < 1L) && (*mode != 'a')) {
			/* An error occurred, and we didn't transfer anything,
			 * so remove empty file we just made.
			 */
			(void) UNLINK(local);
		} else {
			/* Restore the modifcation date of the new file to
			 * what it was on the remote host, if possible.
			 */
			SetLocalFileTimes(gopt->doUTime, modifTime, local);
		}
	}

	DoneWithXferSpec(xp);
	return (result);
}	/* DoGet */