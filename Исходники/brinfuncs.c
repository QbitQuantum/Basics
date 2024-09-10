/*
 * Extract all item values from a BRIN index page
 *
 * Usage: SELECT * FROM brin_page_items(get_raw_page('idx', 1), 'idx'::regclass);
 */
Datum
brin_page_items(PG_FUNCTION_ARGS)
{
	brin_page_state *state;
	FuncCallContext *fctx;

	if (!superuser())
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 (errmsg("must be superuser to use raw page functions"))));

	if (SRF_IS_FIRSTCALL())
	{
		bytea	   *raw_page = PG_GETARG_BYTEA_P(0);
		Oid			indexRelid = PG_GETARG_OID(1);
		Page		page;
		TupleDesc	tupdesc;
		MemoryContext mctx;
		Relation	indexRel;
		AttrNumber	attno;

		/* minimally verify the page we got */
		page = verify_brin_page(raw_page, BRIN_PAGETYPE_REGULAR, "regular");

		/* create a function context for cross-call persistence */
		fctx = SRF_FIRSTCALL_INIT();

		/* switch to memory context appropriate for multiple function calls */
		mctx = MemoryContextSwitchTo(fctx->multi_call_memory_ctx);

		/* Build a tuple descriptor for our result type */
		if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
			elog(ERROR, "return type must be a row type");

		indexRel = index_open(indexRelid, AccessShareLock);

		state = palloc(offsetof(brin_page_state, columns) +
					   sizeof(brin_column_state) * RelationGetDescr(indexRel)->natts);

		state->bdesc = brin_build_desc(indexRel);
		state->page = page;
		state->offset = FirstOffsetNumber;
		state->unusedItem = false;
		state->done = false;
		state->dtup = NULL;

		/*
		 * Initialize output functions for all indexed datatypes; simplifies
		 * calling them later.
		 */
		for (attno = 1; attno <= state->bdesc->bd_tupdesc->natts; attno++)
		{
			Oid		output;
			bool	isVarlena;
			BrinOpcInfo *opcinfo;
			int		i;
			brin_column_state *column;

			opcinfo = state->bdesc->bd_info[attno - 1];
			column = palloc(offsetof(brin_column_state, outputFn) +
							sizeof(FmgrInfo) * opcinfo->oi_nstored);

			column->nstored = opcinfo->oi_nstored;
			for (i = 0; i < opcinfo->oi_nstored; i++)
			{
				getTypeOutputInfo(opcinfo->oi_typids[i], &output, &isVarlena);
				fmgr_info(output, &column->outputFn[i]);
			}

			state->columns[attno - 1] = column;
		}

		index_close(indexRel, AccessShareLock);

		fctx->user_fctx = state;
		fctx->tuple_desc = BlessTupleDesc(tupdesc);

		MemoryContextSwitchTo(mctx);
	}

	fctx = SRF_PERCALL_SETUP();
	state = fctx->user_fctx;

	if (!state->done)
	{
		HeapTuple	result;
		Datum		values[7];
		bool		nulls[7];

		/*
		 * This loop is called once for every attribute of every tuple in the
		 * page.  At the start of a tuple, we get a NULL dtup; that's our
		 * signal for obtaining and decoding the next one.  If that's not the
		 * case, we output the next attribute.
		 */
		if (state->dtup == NULL)
		{
			BrinTuple	   *tup;
			MemoryContext mctx;
			ItemId		itemId;

			/* deformed tuple must live across calls */
			mctx = MemoryContextSwitchTo(fctx->multi_call_memory_ctx);

			/* verify item status: if there's no data, we can't decode */
			itemId = PageGetItemId(state->page, state->offset);
			if (ItemIdIsUsed(itemId))
			{
				tup = (BrinTuple *) PageGetItem(state->page,
											  PageGetItemId(state->page,
															state->offset));
				state->dtup = brin_deform_tuple(state->bdesc, tup);
				state->attno = 1;
				state->unusedItem = false;
			}
			else
				state->unusedItem = true;

			MemoryContextSwitchTo(mctx);
		}
		else
			state->attno++;

		MemSet(nulls, 0, sizeof(nulls));

		if (state->unusedItem)
		{
			values[0] = UInt16GetDatum(state->offset);
			nulls[1] = true;
			nulls[2] = true;
			nulls[3] = true;
			nulls[4] = true;
			nulls[5] = true;
			nulls[6] = true;
		}
		else
		{
			int		att = state->attno - 1;

			values[0] = UInt16GetDatum(state->offset);
			values[1] = UInt32GetDatum(state->dtup->bt_blkno);
			values[2] = UInt16GetDatum(state->attno);
			values[3] = BoolGetDatum(state->dtup->bt_columns[att].bv_allnulls);
			values[4] = BoolGetDatum(state->dtup->bt_columns[att].bv_hasnulls);
			values[5] = BoolGetDatum(state->dtup->bt_placeholder);
			if (!state->dtup->bt_columns[att].bv_allnulls)
			{
				BrinValues   *bvalues = &state->dtup->bt_columns[att];
				StringInfoData	s;
				bool		first;
				int			i;

				initStringInfo(&s);
				appendStringInfoChar(&s, '{');

				first = true;
				for (i = 0; i < state->columns[att]->nstored; i++)
				{
					char   *val;

					if (!first)
						appendStringInfoString(&s, " .. ");
					first = false;
					val = OutputFunctionCall(&state->columns[att]->outputFn[i],
											 bvalues->bv_values[i]);
					appendStringInfoString(&s, val);
					pfree(val);
				}
				appendStringInfoChar(&s, '}');

				values[6] = CStringGetTextDatum(s.data);
				pfree(s.data);
			}
			else
			{
				nulls[6] = true;
			}
		}

		result = heap_form_tuple(fctx->tuple_desc, values, nulls);

		/*
		 * If the item was unused, jump straight to the next one; otherwise,
		 * the only cleanup needed here is to set our signal to go to the next
		 * tuple in the following iteration, by freeing the current one.
		 */
		if (state->unusedItem)
			state->offset = OffsetNumberNext(state->offset);
		else if (state->attno >= state->bdesc->bd_tupdesc->natts)
		{
			pfree(state->dtup);
			state->dtup = NULL;
			state->offset = OffsetNumberNext(state->offset);
		}

		/*
		 * If we're beyond the end of the page, set flag to end the function in
		 * the following iteration.
		 */
		if (state->offset > PageGetMaxOffsetNumber(state->page))
			state->done = true;

		SRF_RETURN_NEXT(fctx, HeapTupleGetDatum(result));
	}

	brin_free_desc(state->bdesc);

	SRF_RETURN_DONE(fctx);
}