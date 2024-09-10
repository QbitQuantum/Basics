/*
 * plr_SPI_execp - The builtin SPI_execp command for the R interpreter
 */
SEXP
plr_SPI_execp(SEXP rsaved_plan, SEXP rargvalues)
{
	saved_plan_desc	   *plan_desc = (saved_plan_desc *) R_ExternalPtrAddr(rsaved_plan);
	void			   *saved_plan = plan_desc->saved_plan;
	int					nargs = plan_desc->nargs;
	Oid				   *typeids = plan_desc->typeids;
	Oid				   *typelems = plan_desc->typelems;
	FmgrInfo		   *typinfuncs = plan_desc->typinfuncs;
	int					i;
	Datum			   *argvalues = NULL;
	char			   *nulls = NULL;
	bool				isnull = false;
	SEXP				obj;
	int					spi_rc = 0;
	char				buf[64];
	int					count = 0;
	int					ntuples;
	SEXP				result = NULL;
	MemoryContext		oldcontext;
	PREPARE_PG_TRY;

	/* set up error context */
	PUSH_PLERRCONTEXT(rsupport_error_callback, "pg.spi.execp");

	if (nargs > 0)
	{
		if (!Rf_isVectorList(rargvalues))
			error("%s", "second parameter must be a list of arguments " \
						"to the prepared plan");

		if (length(rargvalues) != nargs)
			error("list of arguments (%d) is not the same length " \
				  "as that of the prepared plan (%d)",
				  length(rargvalues), nargs);

		argvalues = (Datum *) palloc(nargs * sizeof(Datum));
		nulls = (char *) palloc(nargs * sizeof(char));
	}

	for (i = 0; i < nargs; i++)
	{
		PROTECT(obj = VECTOR_ELT(rargvalues, i));

		argvalues[i] = get_datum(obj, typeids[i], typelems[i], typinfuncs[i], &isnull);
		if (!isnull)
			nulls[i] = ' ';
		else
			nulls[i] = 'n';

		UNPROTECT(1);
	}

	/* switch to SPI memory context */
	SWITCHTO_PLR_SPI_CONTEXT(oldcontext);

	/*
	 * trap elog/ereport so we can let R finish up gracefully
	 * and generate the error once we exit the interpreter
	 */
	PG_TRY();
	{
		/* Execute the plan */
		spi_rc = SPI_execp(saved_plan, argvalues, nulls, count);
	}
	PLR_PG_CATCH();
	PLR_PG_END_TRY();

	/* back to caller's memory context */
	MemoryContextSwitchTo(oldcontext);

	/* check the result */
	switch (spi_rc)
	{
		case SPI_OK_UTILITY:
			snprintf(buf, sizeof(buf), "%d", 0);
			SPI_freetuptable(SPI_tuptable);

			PROTECT(result = NEW_CHARACTER(1));
			SET_STRING_ELT(result, 0, COPY_TO_USER_STRING(buf));
			UNPROTECT(1);

			break;
			
		case SPI_OK_SELINTO:
		case SPI_OK_INSERT:
		case SPI_OK_DELETE:
		case SPI_OK_UPDATE:
			snprintf(buf, sizeof(buf), "%d", SPI_processed);
			SPI_freetuptable(SPI_tuptable);

			PROTECT(result = NEW_CHARACTER(1));
			SET_STRING_ELT(result, 0, COPY_TO_USER_STRING(buf));
			UNPROTECT(1);

			break;
			
		case SPI_OK_SELECT:
			ntuples = SPI_processed;
			if (ntuples > 0)
			{
				result = rpgsql_get_results(ntuples, SPI_tuptable);
				SPI_freetuptable(SPI_tuptable);
			}
			else
				result = R_NilValue;
			break;
			
		case SPI_ERROR_ARGUMENT:
			error("SPI_execp() failed: SPI_ERROR_ARGUMENT");
			break;
			
		case SPI_ERROR_UNCONNECTED:
			error("SPI_execp() failed: SPI_ERROR_UNCONNECTED");
			break;
			
		case SPI_ERROR_COPY:
			error("SPI_execp() failed: SPI_ERROR_COPY");
			break;
			
		case SPI_ERROR_CURSOR:
			error("SPI_execp() failed: SPI_ERROR_CURSOR");
			break;
			
		case SPI_ERROR_TRANSACTION:
			error("SPI_execp() failed: SPI_ERROR_TRANSACTION");
			break;
			
		case SPI_ERROR_OPUNKNOWN:
			error("SPI_execp() failed: SPI_ERROR_OPUNKNOWN");
			break;
			
		default:
			error("SPI_execp() failed: %d", spi_rc);
			break;
	}

	POP_PLERRCONTEXT;
	return result;
}