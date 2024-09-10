/*
 * load up the categories hash table
 */
static HTAB *
load_categories_hash(char *cats_sql, MemoryContext per_query_ctx)
{
	HTAB	   *crosstab_hash;
	HASHCTL		ctl;
	int			ret;
	int			proc;
	MemoryContext SPIcontext;

	/* initialize the category hash table */
	MemSet(&ctl, 0, sizeof(ctl));
	ctl.keysize = MAX_CATNAME_LEN;
	ctl.entrysize = sizeof(crosstab_HashEnt);
	ctl.hcxt = per_query_ctx;

	/*
	 * use INIT_CATS, defined above as a guess of how many hash table entries
	 * to create, initially
	 */
	crosstab_hash = hash_create("crosstab hash",
								INIT_CATS,
								&ctl,
								HASH_ELEM | HASH_CONTEXT);

	/* Connect to SPI manager */
	if ((ret = SPI_connect()) < 0)
		/* internal error */
		elog(ERROR, "load_categories_hash: SPI_connect returned %d", ret);

	/* Retrieve the category name rows */
	ret = SPI_execute(cats_sql, true, 0);
	proc = SPI_processed;

	/* Check for qualifying tuples */
	if ((ret == SPI_OK_SELECT) && (proc > 0))
	{
		SPITupleTable *spi_tuptable = SPI_tuptable;
		TupleDesc	spi_tupdesc = spi_tuptable->tupdesc;
		int			i;

		/*
		 * The provided categories SQL query must always return one column:
		 * category - the label or identifier for each column
		 */
		if (spi_tupdesc->natts != 1)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("provided \"categories\" SQL must " \
							"return 1 column of at least one row")));

		for (i = 0; i < proc; i++)
		{
			crosstab_cat_desc *catdesc;
			char	   *catname;
			HeapTuple	spi_tuple;

			/* get the next sql result tuple */
			spi_tuple = spi_tuptable->vals[i];

			/* get the category from the current sql result tuple */
			catname = SPI_getvalue(spi_tuple, spi_tupdesc, 1);

			SPIcontext = MemoryContextSwitchTo(per_query_ctx);

			catdesc = (crosstab_cat_desc *) palloc(sizeof(crosstab_cat_desc));
			catdesc->catname = catname;
			catdesc->attidx = i;

			/* Add the proc description block to the hashtable */
			crosstab_HashTableInsert(crosstab_hash, catdesc);

			MemoryContextSwitchTo(SPIcontext);
		}
	}

	if (SPI_finish() != SPI_OK_FINISH)
		/* internal error */
		elog(ERROR, "load_categories_hash: SPI_finish() failed");

	return crosstab_hash;
}