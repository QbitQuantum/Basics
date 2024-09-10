/**
 * @brief Entry point of the user-defined function for pg_bulkload.
 * @return Returns number of loaded tuples.  If the case of errors, -1 will be
 * returned.
 */
Datum
pg_bulkload(PG_FUNCTION_ARGS)
{
	Reader		   *rd = NULL;
	Writer		   *wt = NULL;
	Datum			options;
	MemoryContext	ctx;
	MemoryContext	ccxt;
	PGRUsage		ru0;
	PGRUsage		ru1;
	int64			count;
	int64			parse_errors;
	int64			skip;
	WriterResult	ret;
	char		   *start;
	char		   *end;
	float8			system;
	float8			user;
	float8			duration;
	TupleDesc		tupdesc;
	Datum			values[PG_BULKLOAD_COLS];
	bool			nulls[PG_BULKLOAD_COLS];
	HeapTuple		result;

	/* Build a tuple descriptor for our result type */
	if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE)
		elog(ERROR, "return type must be a row type");

	BULKLOAD_PROFILE_PUSH();

	pg_rusage_init(&ru0);

	/* must be the super user */
	if (!superuser())
		ereport(ERROR,
			(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
			 errmsg("must be superuser to use pg_bulkload")));

	options = PG_GETARG_DATUM(0);

	ccxt = CurrentMemoryContext;

	/*
	 * STEP 1: Initialization
	 */

	/* parse options and create reader and writer */
	ParseOptions(options, &rd, &wt, ru0.tv.tv_sec);

	/* initialize reader */
	ReaderInit(rd);

	/*
	 * We need to split PG_TRY block because gcc optimizes if-branches with
	 * longjmp codes too much. Local variables initialized in either branch
	 * cannot be handled another branch.
	 */
	PG_TRY();
	{
		/* truncate heap */
		if (wt->truncate)
			TruncateTable(wt->relid);

		/* initialize writer */
		WriterInit(wt);

		/* initialize checker */
		CheckerInit(&rd->checker, wt->rel, wt->tchecker);

		/* initialize parser */
		ParserInit(rd->parser, &rd->checker, rd->infile, wt->desc,
				   wt->multi_process, PG_GET_COLLATION());
	}
	PG_CATCH();
	{
		if (rd)
			ReaderClose(rd, true);
		if (wt)
			WriterClose(wt, true);
		PG_RE_THROW();
	}
	PG_END_TRY();

	/* No throwable codes here! */

	PG_TRY();
	{
		/* create logger */
		CreateLogger(rd->logfile, wt->verbose, rd->infile[0] == ':');

		start = timeval_to_cstring(ru0.tv);
		LoggerLog(INFO, "\npg_bulkload %s on %s\n\n",
				   PG_BULKLOAD_VERSION, start);

		ReaderDumpParams(rd);
		WriterDumpParams(wt);
		LoggerLog(INFO, "\n");

		BULKLOAD_PROFILE(&prof_init);

		/*
		 * STEP 2: Build heap
		 */

		/* Switch into its memory context */
		Assert(wt->context);
		ctx = MemoryContextSwitchTo(wt->context);

		/* Loop for each input file record. */
		while (wt->count < rd->limit)
		{
			HeapTuple	tuple;

			CHECK_FOR_INTERRUPTS();

			/* read tuple */
			BULKLOAD_PROFILE_PUSH();
			tuple = ReaderNext(rd);
			BULKLOAD_PROFILE_POP();
			BULKLOAD_PROFILE(&prof_reader);
			if (tuple == NULL)
				break;

			/* write tuple */
			BULKLOAD_PROFILE_PUSH();
			WriterInsert(wt, tuple);
			wt->count += 1;
			BULKLOAD_PROFILE_POP();
			BULKLOAD_PROFILE(&prof_writer);

			MemoryContextReset(wt->context);
			BULKLOAD_PROFILE(&prof_reset);
		}

		MemoryContextSwitchTo(ctx);

		/*
		 * STEP 3: Finalize heap and merge indexes
		 */

		count = wt->count;
		parse_errors = rd->parse_errors;

		/*
		 * close writer first and reader second because shmem_exit callback
		 * is managed by a simple stack.
		 */
		ret = WriterClose(wt, false);
		wt = NULL;
		skip = ReaderClose(rd, false);
		rd = NULL;
	}
	PG_CATCH();
	{
		ErrorData	   *errdata;
		MemoryContext	ecxt;

		ecxt = MemoryContextSwitchTo(ccxt);
		errdata = CopyErrorData();
		LoggerLog(INFO, "%s\n", errdata->message);
		FreeErrorData(errdata);

		/* close writer first, and reader second */
		if (wt)
			WriterClose(wt, true);
		if (rd)
			ReaderClose(rd, true);

		MemoryContextSwitchTo(ecxt);
		PG_RE_THROW();
	}
	PG_END_TRY();

	count -= ret.num_dup_new;

	LoggerLog(INFO, "\n"
			  "  " int64_FMT " Rows skipped.\n"
			  "  " int64_FMT " Rows successfully loaded.\n"
			  "  " int64_FMT " Rows not loaded due to parse errors.\n"
			  "  " int64_FMT " Rows not loaded due to duplicate errors.\n"
			  "  " int64_FMT " Rows replaced with new rows.\n\n",
			  skip, count, parse_errors, ret.num_dup_new, ret.num_dup_old);

	pg_rusage_init(&ru1);
	system = diffTime(ru1.ru.ru_stime, ru0.ru.ru_stime);
	user = diffTime(ru1.ru.ru_utime, ru0.ru.ru_utime);
	duration = diffTime(ru1.tv, ru0.tv);
	end = timeval_to_cstring(ru1.tv);

	memset(nulls, 0, sizeof(nulls));
	values[0] = Int64GetDatum(skip);
	values[1] = Int64GetDatum(count);
	values[2] = Int64GetDatum(parse_errors);
	values[3] = Int64GetDatum(ret.num_dup_new);
	values[4] = Int64GetDatum(ret.num_dup_old);
	values[5] = Float8GetDatumFast(system);
	values[6] = Float8GetDatumFast(user);
	values[7] = Float8GetDatumFast(duration);

	LoggerLog(INFO,
		"Run began on %s\n"
		"Run ended on %s\n\n"
		"CPU %.2fs/%.2fu sec elapsed %.2f sec\n",
		start, end, system, user, duration);

	LoggerClose();

	result = heap_form_tuple(tupdesc, values, nulls);

	BULKLOAD_PROFILE(&prof_fini);
	BULKLOAD_PROFILE_POP();
	BULKLOAD_PROFILE_PRINT();

	PG_RETURN_DATUM(HeapTupleGetDatum(result));
}