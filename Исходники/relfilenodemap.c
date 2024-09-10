/*
 * Map a relation's (tablespace, filenode) to a relation's oid and cache the
 * result.
 *
 * Returns InvalidOid if no relation matching the criteria could be found.
 */
Oid
RelidByRelfilenode(Oid reltablespace, Oid relfilenode)
{
	RelfilenodeMapKey key;
	RelfilenodeMapEntry *entry;
	bool		found;
	SysScanDesc scandesc;
	Relation	relation;
	HeapTuple	ntp;
	ScanKeyData skey[2];
	Oid			relid;

	if (RelfilenodeMapHash == NULL)
		InitializeRelfilenodeMap();

	/* pg_class will show 0 when the value is actually MyDatabaseTableSpace */
	if (reltablespace == MyDatabaseTableSpace)
		reltablespace = 0;

	MemSet(&key, 0, sizeof(key));
	key.reltablespace = reltablespace;
	key.relfilenode = relfilenode;

	/*
	 * Check cache and return entry if one is found. Even if no target
	 * relation can be found later on we store the negative match and return a
	 * InvalidOid from cache. That's not really necessary for performance
	 * since querying invalid values isn't supposed to be a frequent thing,
	 * but it's basically free.
	 */
	entry = hash_search(RelfilenodeMapHash, (void *) &key, HASH_FIND, &found);

	if (found)
		return entry->relid;

	/* ok, no previous cache entry, do it the hard way */

	/* initialize empty/negative cache entry before doing the actual lookups */
	relid = InvalidOid;

	if (reltablespace == GLOBALTABLESPACE_OID)
	{
		/*
		 * Ok, shared table, check relmapper.
		 */
		relid = RelationMapFilenodeToOid(relfilenode, true);
	}
	else
	{
		/*
		 * Not a shared table, could either be a plain relation or a
		 * non-shared, nailed one, like e.g. pg_class.
		 */

		/* check for plain relations by looking in pg_class */
		relation = heap_open(RelationRelationId, AccessShareLock);

		/* copy scankey to local copy, it will be modified during the scan */
		memcpy(skey, relfilenode_skey, sizeof(skey));

		/* set scan arguments */
		skey[0].sk_argument = ObjectIdGetDatum(reltablespace);
		skey[1].sk_argument = ObjectIdGetDatum(relfilenode);

		scandesc = systable_beginscan(relation,
									  ClassTblspcRelfilenodeIndexId,
									  true,
									  NULL,
									  2,
									  skey);

		found = false;

		while (HeapTupleIsValid(ntp = systable_getnext(scandesc)))
		{
			if (found)
				elog(ERROR,
					 "unexpected duplicate for tablespace %u, relfilenode %u",
					 reltablespace, relfilenode);
			found = true;

#ifdef USE_ASSERT_CHECKING
			{
				bool		isnull;
				Oid			check;

				check = fastgetattr(ntp, Anum_pg_class_reltablespace,
									RelationGetDescr(relation),
									&isnull);
				Assert(!isnull && check == reltablespace);

				check = fastgetattr(ntp, Anum_pg_class_relfilenode,
									RelationGetDescr(relation),
									&isnull);
				Assert(!isnull && check == relfilenode);
			}
#endif
			relid = HeapTupleGetOid(ntp);
		}

		systable_endscan(scandesc);
		heap_close(relation, AccessShareLock);

		/* check for tables that are mapped but not shared */
		if (!found)
			relid = RelationMapFilenodeToOid(relfilenode, false);
	}

	/*
	 * Only enter entry into cache now, our opening of pg_class could have
	 * caused cache invalidations to be executed which would have deleted a
	 * new entry if we had entered it above.
	 */
	entry = hash_search(RelfilenodeMapHash, (void *) &key, HASH_ENTER, &found);
	if (found)
		elog(ERROR, "corrupted hashtable");
	entry->relid = relid;

	return relid;
}