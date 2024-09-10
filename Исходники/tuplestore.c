/*
 * tuplestore_trim	- remove all no-longer-needed tuples
 *
 * Calling this function authorizes the tuplestore to delete all tuples
 * before the oldest read pointer, if no read pointer is marked as requiring
 * REWIND capability.
 *
 * Note: this is obviously safe if no pointer has BACKWARD capability either.
 * If a pointer is marked as BACKWARD but not REWIND capable, it means that
 * the pointer can be moved backward but not before the oldest other read
 * pointer.
 */
void
tuplestore_trim(Tuplestorestate *state)
{
	int			oldest;
	int			nremove;
	int			i;

	/*
	 * Truncation is disallowed if any read pointer requires rewind
	 * capability.
	 */
	if (state->eflags & EXEC_FLAG_REWIND)
		return;

	/*
	 * We don't bother trimming temp files since it usually would mean more
	 * work than just letting them sit in kernel buffers until they age out.
	 */
	if (state->status != TSS_INMEM)
		return;

	/* Find the oldest read pointer */
	oldest = state->memtupcount;
	for (i = 0; i < state->readptrcount; i++)
	{
		if (!state->readptrs[i].eof_reached)
			oldest = Min(oldest, state->readptrs[i].current);
	}

	/*
	 * Note: you might think we could remove all the tuples before the oldest
	 * "current", since that one is the next to be returned.  However, since
	 * tuplestore_gettuple returns a direct pointer to our internal copy of
	 * the tuple, it's likely that the caller has still got the tuple just
	 * before "current" referenced in a slot. So we keep one extra tuple
	 * before the oldest "current".  (Strictly speaking, we could require such
	 * callers to use the "copy" flag to tuplestore_gettupleslot, but for
	 * efficiency we allow this one case to not use "copy".)
	 */
	nremove = oldest - 1;
	if (nremove <= 0)
		return;					/* nothing to do */
	Assert(nremove <= state->memtupcount);

	/* Release no-longer-needed tuples */
	for (i = 0; i < nremove; i++)
	{
		FREEMEM(state, GetMemoryChunkSpace(state->memtuples[i]));
		pfree(state->memtuples[i]);
	}

	/*
	 * Slide the array down and readjust pointers.	This may look pretty
	 * stupid, but we expect that there will usually not be very many
	 * tuple-pointers to move, so this isn't that expensive; and it keeps a
	 * lot of other logic simple.
	 *
	 * In fact, in the current usage for merge joins, it's demonstrable that
	 * there will always be exactly one non-removed tuple; so optimize that
	 * case.
	 */
	if (nremove + 1 == state->memtupcount)
		state->memtuples[0] = state->memtuples[nremove];
	else
		memmove(state->memtuples, state->memtuples + nremove,
				(state->memtupcount - nremove) * sizeof(void *));

	state->memtupcount -= nremove;
	for (i = 0; i < state->readptrcount; i++)
	{
		if (!state->readptrs[i].eof_reached)
			state->readptrs[i].current -= nremove;
	}

	/* mark tuplestore as truncated (used for Assert crosschecks only) */
	state->truncated = true;
}