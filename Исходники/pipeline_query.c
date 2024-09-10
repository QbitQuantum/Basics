/*
 * get_next_id
 *
 * Gets the smallest possible id to assign to the next continuous view.
 * We keep this minimal so that we can minimize the size of bitmaps used
 * to tag stream buffer events with.
 */
static Oid
get_next_id(Relation rel)
{
	HeapScanDesc scandesc;
	HeapTuple tup;
	List *ids_list = NIL;
	int num_ids;

	Assert(MAX_CQS % 32 == 0);

	scandesc = heap_beginscan_catalog(rel, 0, NULL);

	while ((tup = heap_getnext(scandesc, ForwardScanDirection)) != NULL)
	{
		Form_pipeline_query row = (Form_pipeline_query) GETSTRUCT(tup);
		ids_list = lappend_oid(ids_list, row->id);
	}

	heap_endscan(scandesc);

	num_ids = list_length(ids_list);

	if (num_ids)
	{
		Oid ids[num_ids];
		int counts_per_combiner[continuous_query_num_combiners];
		int i = 0;
		Oid max;
		ListCell *lc;
		int j;
		int target_combiner;
		List *potential_ids;

		MemSet(counts_per_combiner, 0, sizeof(counts_per_combiner));

		foreach(lc, ids_list)
		{
			ids[i] = lfirst_oid(lc);
			counts_per_combiner[ids[i] % continuous_query_num_combiners] += 1;
			i++;
		}

		qsort(ids, num_ids, sizeof(Oid), &compare_oid);

		if (num_ids == MAX_CQS - 1) /* -1 because 0 is an invalid id */
			ereport(ERROR,
					(errcode(ERRCODE_TOO_MANY_CONTINUOUS_VIEWS),
					errmsg("maximum number of continuous views exceeded"),
					errhint("Please drop a existing continuous view before trying to create a new one.")));

		max = ids[num_ids - 1];
		Assert(max >= num_ids);

		/*
		 * FIXME(usmanm): We do some randomization of ID generation here to make sure that CQs that
		 * are created and dropped in quick succession don't read an event that was not for them.
		 */

		/*
		 * Collect any unused ids in [1, max].
		 */
		list_free(ids_list);
		ids_list = NIL;

		for (i = 1, j = 0; j < num_ids; i++)
		{
			if (ids[j] > i)
				ids_list = lappend_oid(ids_list, (Oid) i);
			else
				j++;
		}

		/*
		 * Add all IDs between max and the next multiple of 32.
		 */
		j = Min((max / 32 + 1) * 32, MAX_CQS);
		for (i = max + 1; i < j; i++)
			ids_list = lappend_oid(ids_list, (Oid) i);

		/*
		 * Less than 16 options? Throw in some more.
		 */
		if (list_length(ids_list) < 16 && j < MAX_CQS)
			for (i = j; i < j + 32; i++)
				ids_list = lappend_oid(ids_list, (Oid) i);

		/*
		 * Figure out the target combiner (one with least IDs allocated) and try to allocate
		 * an ID that belongs to it.
		 */
		target_combiner = 0;
		for (i = 0; i < continuous_query_num_combiners; i++)
			if (counts_per_combiner[i] < counts_per_combiner[target_combiner])
				target_combiner = i;

		potential_ids = NIL;
		foreach(lc, ids_list)
		{
			Oid id = lfirst_oid(lc);
			if (id % continuous_query_num_combiners == target_combiner)
				potential_ids = lappend_oid(potential_ids, id);
		}