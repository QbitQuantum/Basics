/*
 * get_database_oids
 *
 * Returns a list of all database OIDs found in pg_database.
 */
static List *
get_database_list(void)
{
	List *dbs = NIL;
	Relation rel;
	HeapScanDesc scan;
	HeapTuple tup;
	MemoryContext resultcxt;

	/* This is the context that we will allocate our output data in */
	resultcxt = CurrentMemoryContext;

	/*
	 * Start a transaction so we can access pg_database, and get a snapshot.
	 * We don't have a use for the snapshot itself, but we're interested in
	 * the secondary effect that it sets RecentGlobalXmin.  (This is critical
	 * for anything that reads heap pages, because HOT may decide to prune
	 * them even if the process doesn't attempt to modify any tuples.)
	 */
	StartTransactionCommand();
	(void) GetTransactionSnapshot();

	/* We take a AccessExclusiveLock so we don't conflict with any DATABASE commands */
	rel = heap_open(DatabaseRelationId, AccessExclusiveLock);
	scan = heap_beginscan_catalog(rel, 0, NULL);

	while (HeapTupleIsValid(tup = heap_getnext(scan, ForwardScanDirection)))
	{
		MemoryContext oldcxt;
		Form_pg_database pgdatabase = (Form_pg_database) GETSTRUCT(tup);
		DatabaseEntry *db_entry;

		/* Ignore template databases or ones that don't allow connections. */
		if (pgdatabase->datistemplate || !pgdatabase->datallowconn)
			continue;

		/*
		 * Allocate our results in the caller's context, not the
		 * transaction's. We do this inside the loop, and restore the original
		 * context at the end, so that leaky things like heap_getnext() are
		 * not called in a potentially long-lived context.
		 */
		oldcxt = MemoryContextSwitchTo(resultcxt);

		db_entry = palloc0(sizeof(DatabaseEntry));
		db_entry->oid = HeapTupleGetOid(tup);
		StrNCpy(NameStr(db_entry->name), NameStr(pgdatabase->datname), NAMEDATALEN);
		dbs = lappend(dbs, db_entry);

		MemoryContextSwitchTo(oldcxt);
	}

	heap_endscan(scan);
	heap_close(rel, AccessExclusiveLock);

	CommitTransactionCommand();

	return dbs;
}