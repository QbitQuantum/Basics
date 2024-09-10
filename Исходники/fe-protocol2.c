/*
 * parseInput subroutine to read a 'T' (row descriptions) message.
 * We build a PGresult structure containing the attribute data.
 * Returns: 0 if completed message, EOF if not enough data yet.
 *
 * Note that if we run out of data, we have to release the partially
 * constructed PGresult, and rebuild it again next time.  Fortunately,
 * that shouldn't happen often, since 'T' messages usually fit in a packet.
 */
static int
getRowDescriptions(PGconn *conn)
{
	PGresult   *result = NULL;
	int			nfields;
	int			i;

	result = PQmakeEmptyPGresult(conn, PGRES_TUPLES_OK);
	if (!result)
		goto failure;

	/* parseInput already read the 'T' label. */
	/* the next two bytes are the number of fields	*/
	if (pqGetInt(&(result->numAttributes), 2, conn))
		goto failure;
	nfields = result->numAttributes;

	/* allocate space for the attribute descriptors */
	if (nfields > 0)
	{
		result->attDescs = (PGresAttDesc *)
			pqResultAlloc(result, nfields * sizeof(PGresAttDesc), TRUE);
		if (!result->attDescs)
			goto failure;
		MemSet(result->attDescs, 0, nfields * sizeof(PGresAttDesc));
	}

	/* get type info */
	for (i = 0; i < nfields; i++)
	{
		int			typid;
		int			typlen;
		int			atttypmod;

		if (pqGets(&conn->workBuffer, conn) ||
			pqGetInt(&typid, 4, conn) ||
			pqGetInt(&typlen, 2, conn) ||
			pqGetInt(&atttypmod, 4, conn))
			goto failure;

		/*
		 * Since pqGetInt treats 2-byte integers as unsigned, we need to
		 * coerce the result to signed form.
		 */
		typlen = (int) ((int16) typlen);

		result->attDescs[i].name = pqResultStrdup(result,
												  conn->workBuffer.data);
		if (!result->attDescs[i].name)
			goto failure;
		result->attDescs[i].tableid = 0;
		result->attDescs[i].columnid = 0;
		result->attDescs[i].format = 0;
		result->attDescs[i].typid = typid;
		result->attDescs[i].typlen = typlen;
		result->attDescs[i].atttypmod = atttypmod;
	}

	/* Success! */
	conn->result = result;
	return 0;

failure:
	if (result)
		PQclear(result);
	return EOF;
}