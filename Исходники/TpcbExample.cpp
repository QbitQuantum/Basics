//
// Initialize the database to the specified number of accounts, branches,
// history records, and tellers.
//
int
TpcbExample::populate()
{
	DB *dbp;

	int err;
	u_int32_t balance, idnum;
	u_int32_t end_anum, end_bnum, end_tnum;
	u_int32_t start_anum, start_bnum, start_tnum;

	idnum = BEGID;
	balance = 500000;

	if ((err = db_create(&dbp, dbenv, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "db_create of accounts db failed.");
		return (1);
	}
	dbp->set_h_nelem(dbp, (unsigned int)accounts);

	if ((err = dbp->open(dbp, NULL, "account", NULL, DB_HASH,
			     DB_CREATE, 0644)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Account file create failed. error: %s.", db_strerror(err));
		return (1);
	}

	start_anum = idnum;
	if ((err =
	    populateTable(dbp, idnum, balance, accounts, "account")) != 0)
		return (1);
	idnum += accounts;
	end_anum = idnum - 1;
	if ((err = dbp->close(dbp, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Account file close failed. error: %s.", db_strerror(err));
		return (1);
	}

	if ((err = db_create(&dbp, dbenv, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "db_create of branches db failed.");
		return (1);
	}
	//
	// Since the number of branches is very small, we want to use very
	// small pages and only 1 key per page.  This is the poor-man's way
	// of getting key locking instead of page locking.
	//
	dbp->set_h_ffactor(dbp, 1);
	dbp->set_h_nelem(dbp, (unsigned int)branches);
	dbp->set_pagesize(dbp, 512);

	if ((err = dbp->open(dbp, NULL, "branch", NULL, DB_HASH,
			     DB_CREATE, 0644)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Branch file create failed. error: %s.", db_strerror(err));
		return (1);
	}
	start_bnum = idnum;
	if ((err = populateTable(dbp, idnum, balance, branches, "branch")) != 0)
		return (1);
	idnum += branches;
	end_bnum = idnum - 1;
	if ((err = dbp->close(dbp, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Close of branch file failed. error: %s.",
		    db_strerror(err));
		return (1);
	}

	if ((err = db_create(&dbp, dbenv, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "db_create of teller db failed.");
		return (1);
	}
	//
	// In the case of tellers, we also want small pages, but we'll let
	// the fill factor dynamically adjust itself.
	//
	dbp->set_h_ffactor(dbp, 0);
	dbp->set_h_nelem(dbp, (unsigned int)tellers);
	dbp->set_pagesize(dbp, 512);

	if ((err = dbp->open(dbp, NULL, "teller", NULL, DB_HASH,
			     DB_CREATE, 0644)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Teller file create failed. error: %s.", db_strerror(err));
		return (1);
	}

	start_tnum = idnum;
	if ((err = populateTable(dbp, idnum, balance, tellers, "teller")) != 0)
		return (1);
	idnum += tellers;
	end_tnum = idnum - 1;
	if ((err = dbp->close(dbp, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Close of teller file failed. error: %s.",
		    db_strerror(err));
		return (1);
	}

	if ((err = db_create(&dbp, dbenv, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "db_create of history db failed.");
		return (1);
	}
	dbp->set_re_len(dbp, HISTORY_LEN);
	if ((err = dbp->open(dbp, NULL, "history", NULL, DB_RECNO,
			     DB_CREATE, 0644)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Create of history file failed. error: %s.",
		    db_strerror(err));
		return (1);
	}

	populateHistory(dbp, history, accounts, branches, tellers);
	if ((err = dbp->close(dbp, 0)) != 0) {
		_snprintf(msgString, ERR_STRING_MAX,
		    "Close of history file failed. error: %s.",
		    db_strerror(err));
		return (1);
	}

	_snprintf(msgString, ERR_STRING_MAX, "Populated OK.");
	return (0);
}