void execute_disposition(file_list *fl)
{
    FILE    *fp=NULL;
    char    *nm, tpl='~';

    Syslog('o', "execute_disposition(%s)", fl->local);
    nm = fl->local;
    if (fl->flofp) {
	/*
	 * Check for special case: flo-file 
	 */
	if (fl->floff == -1) {
	    /*
	     * We check if there are any files left for transmission
	     * in the flo-file to decide whether to remove or leave
	     * it on disk.
	     */
	    char    buf[PATH_MAX];
	    int	    files_remain = 0;

	    if (fseek(fl->flofp, 0L, 0) == 0) {
		while (!feof(fl->flofp) && !ferror(fl->flofp)) {
		    if (fgets(buf, sizeof(buf)-1, fl->flofp) == NULL)
			continue;

		    /*
		     * Count nr of files which haven't been sent yet
		     */
		    if (buf[0] != '~')
			files_remain++;
		}

	    } else {
		WriteError("$Error seeking in .flo to 0");
		files_remain = -1; /* Keep flo-file */
	    }

	    if (files_remain) {
		Syslog('o', "Leaving flo-file \"%s\", %d files remaining", FTND_SS(nm), files_remain);
		fl->disposition = LEAVE;
	    } else {
		fl->disposition = KFS;
	    }
	} else {
	    /*
	     * Mark files as sent in flo-file
	     */
	    if (fseek(fl->flofp, fl->floff, 0) == 0) {
		if (fwrite(&tpl,1,1,fl->flofp) != 1) {
		    WriteError("$Error writing '~' to .flo at %u", (unsigned int)fl->floff);
		} else {
		    Syslog('o', "Marked file \"%s\" as sent", FTND_SS(nm));
		}
		fflush(fl->flofp);
#ifdef HAVE_FDATASYNC
		fdatasync(fileno(fl->flofp));
#else
#ifdef HAVE_FSYNC		
		fsync(fileno(fl->flofp));
#endif
#endif
	    } else 
		WriteError("$error seeking in .flo to %u", (unsigned int)fl->floff);
	}
    }

    switch (fl->disposition) {
	case DSF:
	case LEAVE: break;

	case TFS:   Syslog('o', "Truncating sent file \"%s\"",FTND_SS(nm));
		    if ((fp=fopen(nm,"w"))) 
			fclose(fp);
		    else 
			WriteError("$Cannot truncate file \"%s\"",FTND_SS(nm));
		    break;

	case KFS:   Syslog('o', "Removing sent file \"%s\"",FTND_SS(nm));
		    if (unlink(nm) != 0) {
			if (errno == ENOENT)
			    Syslog('o', "Cannot unlink nonexistent file \"%s\"", FTND_SS(nm));
			else
			    WriteError("$Cannot unlink file \"%s\"", FTND_SS(nm));
		    }
		    break;

	default:    WriteError("execute_disposition: unknown disp %d for \"%s\"", fl->disposition,FTND_SS(nm));
		    break;
    }

    return;
}