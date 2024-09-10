_nc_resolve_uses2(bool fullresolve, bool literal)
/* try to resolve all use capabilities */
{
    ENTRY *qp, *rp, *lastread = 0;
    bool keepgoing;
    unsigned i;
    int unresolved, total_unresolved, multiples;

    DEBUG(2, ("RESOLUTION BEGINNING"));

    /*
     * Check for multiple occurrences of the same name.
     */
    multiples = 0;
    for_entry_list(qp) {
	int matchcount = 0;

	for_entry_list(rp) {
	    if (qp > rp
		&& _nc_entry_match(qp->tterm.term_names, rp->tterm.term_names)) {
		matchcount++;
		if (matchcount == 1) {
		    (void) fprintf(stderr, "Name collision between %s",
				   _nc_first_name(qp->tterm.term_names));
		    multiples++;
		}
		if (matchcount >= 1)
		    (void) fprintf(stderr, " %s", _nc_first_name(rp->tterm.term_names));
	    }
	}
	if (matchcount >= 1)
	    (void) putc('\n', stderr);
    }
    if (multiples > 0)
	return (FALSE);

    DEBUG(2, ("NO MULTIPLE NAME OCCURRENCES"));

    /*
     * First resolution stage: compute link pointers corresponding to names.
     */
    total_unresolved = 0;
    _nc_curr_col = -1;
    for_entry_list(qp) {
	unresolved = 0;
	for (i = 0; i < qp->nuses; i++) {
	    bool foundit;
	    char *child = _nc_first_name(qp->tterm.term_names);
	    char *lookfor = qp->uses[i].name;
	    long lookline = qp->uses[i].line;

	    foundit = FALSE;

	    _nc_set_type(child);

	    /* first, try to resolve from in-core records */
	    for_entry_list(rp) {
		if (rp != qp
		    && _nc_name_match(rp->tterm.term_names, lookfor, "|")) {
		    DEBUG(2, ("%s: resolving use=%s (in core)",
			      child, lookfor));

		    qp->uses[i].link = rp;
		    foundit = TRUE;
		}
	    }

	    /* if that didn't work, try to merge in a compiled entry */
	    if (!foundit) {
		TERMTYPE thisterm;
		char filename[PATH_MAX];

		memset(&thisterm, 0, sizeof(thisterm));
		if (_nc_read_entry(lookfor, filename, &thisterm) == 1) {
		    DEBUG(2, ("%s: resolving use=%s (compiled)",
			      child, lookfor));

		    rp = typeMalloc(ENTRY, 1);
		    if (rp == 0)
			_nc_err_abort(MSG_NO_MEMORY);
		    rp->tterm = thisterm;
		    rp->nuses = 0;
		    rp->next = lastread;
		    lastread = rp;

		    qp->uses[i].link = rp;
		    foundit = TRUE;
		}
	    }

	    /* no good, mark this one unresolvable and complain */
	    if (!foundit) {
		unresolved++;
		total_unresolved++;

		_nc_curr_line = lookline;
		_nc_warning("resolution of use=%s failed", lookfor);
		qp->uses[i].link = 0;
	    }
	}
    }
    if (total_unresolved) {
	/* free entries read in off disk */
	_nc_free_entries(lastread);
	return (FALSE);
    }

    DEBUG(2, ("NAME RESOLUTION COMPLETED OK"));

    /*
     * OK, at this point all (char *) references in `name' members
     * have been successfully converted to (ENTRY *) pointers in
     * `link' members.  Time to do the actual merges.
     */
    if (fullresolve) {
	do {
	    TERMTYPE merged;

	    keepgoing = FALSE;

	    for_entry_list(qp) {
		if (qp->nuses > 0) {
		    DEBUG(2, ("%s: attempting merge",
			      _nc_first_name(qp->tterm.term_names)));
		    /*
		     * If any of the use entries we're looking for is
		     * incomplete, punt.  We'll catch this entry on a
		     * subsequent pass.
		     */
		    for (i = 0; i < qp->nuses; i++)
			if (qp->uses[i].link->nuses) {
			    DEBUG(2, ("%s: use entry %d unresolved",
				      _nc_first_name(qp->tterm.term_names), i));
			    goto incomplete;
			}

		    /*
		     * First, make sure there is no garbage in the
		     * merge block.  As a side effect, copy into
		     * the merged entry the name field and string
		     * table pointer.
		     */
		    _nc_copy_termtype(&merged, &(qp->tterm));

		    /*
		     * Now merge in each use entry in the proper
		     * (reverse) order.
		     */
		    for (; qp->nuses; qp->nuses--)
			_nc_merge_entry(&merged,
					&qp->uses[qp->nuses - 1].link->tterm);

		    /*
		     * Now merge in the original entry.
		     */
		    _nc_merge_entry(&merged, &qp->tterm);

		    /*
		     * Replace the original entry with the merged one.
		     */
		    FreeIfNeeded(qp->tterm.Booleans);
		    FreeIfNeeded(qp->tterm.Numbers);
		    FreeIfNeeded(qp->tterm.Strings);
#if NCURSES_XNAMES
		    FreeIfNeeded(qp->tterm.ext_Names);
#endif
		    qp->tterm = merged;
		    _nc_wrap_entry(qp, TRUE);

		    /*
		     * We know every entry is resolvable because name resolution
		     * didn't bomb.  So go back for another pass.
		     */
		    /* FALLTHRU */
		  incomplete:
		    keepgoing = TRUE;
		}
	    }
	} while
	    (keepgoing);

	DEBUG(2, ("MERGES COMPLETED OK"));
    }

    /*
     * We'd like to free entries read in off disk at this point, but can't.
     * The merge_entry() code doesn't copy the strings in the use entries,
     * it just aliases them.  If this ever changes, do a
     * free_entries(lastread) here.
     */

    DEBUG(2, ("RESOLUTION FINISHED"));

    if (fullresolve)
	if (_nc_check_termtype != 0) {
	    _nc_curr_col = -1;
	    for_entry_list(qp) {
		_nc_curr_line = qp->startline;
		_nc_set_type(_nc_first_name(qp->tterm.term_names));
		_nc_check_termtype2(&qp->tterm, literal);
	    }
	    DEBUG(2, ("SANITY CHECK FINISHED"));
	}