/*
 * Form a tuple for entry tree.
 *
 * If the tuple would be too big to be stored, function throws a suitable
 * error if errorTooBig is TRUE, or returns NULL if errorTooBig is FALSE.
 *
 * On leaf pages, Index tuple has non-traditional layout. Tuple may contain
 * posting list or root blocknumber of posting tree.
 * Macros: GinIsPostingTree(itup) / GinSetPostingTree(itup, blkno)
 * 1) Posting list
 *		- itup->t_info & INDEX_SIZE_MASK contains total size of tuple as usual
 *		- ItemPointerGetBlockNumber(&itup->t_tid) contains original
 *		  size of tuple (without posting list).
 *		  Macros: GinGetOrigSizePosting(itup) / GinSetOrigSizePosting(itup,n)
 *		- ItemPointerGetOffsetNumber(&itup->t_tid) contains number
 *		  of elements in posting list (number of heap itempointers)
 *		  Macros: GinGetNPosting(itup) / GinSetNPosting(itup,n)
 *		- After standard part of tuple there is a posting list, ie, array
 *		  of heap itempointers
 *		  Macros: GinGetPosting(itup)
 * 2) Posting tree
 *		- itup->t_info & INDEX_SIZE_MASK contains size of tuple as usual
 *		- ItemPointerGetBlockNumber(&itup->t_tid) contains block number of
 *		  root of posting tree
 *		- ItemPointerGetOffsetNumber(&itup->t_tid) contains magic number
 *		  GIN_TREE_POSTING, which distinguishes this from posting-list case
 *
 * Attributes of an index tuple are different for single and multicolumn index.
 * For single-column case, index tuple stores only value to be indexed.
 * For multicolumn case, it stores two attributes: column number of value
 * and value.
 */
IndexTuple
GinFormTuple(Relation index, GinState *ginstate,
			 OffsetNumber attnum, Datum key,
			 ItemPointerData *ipd, uint32 nipd, bool errorTooBig)
{
	bool		isnull[2] = {FALSE, FALSE};
	IndexTuple	itup;
	uint32		newsize;

	if (ginstate->oneCol)
		itup = index_form_tuple(ginstate->origTupdesc, &key, isnull);
	else
	{
		Datum		datums[2];

		datums[0] = UInt16GetDatum(attnum);
		datums[1] = key;
		itup = index_form_tuple(ginstate->tupdesc[attnum - 1], datums, isnull);
	}

	GinSetOrigSizePosting(itup, IndexTupleSize(itup));

	if (nipd > 0)
	{
		newsize = MAXALIGN(SHORTALIGN(IndexTupleSize(itup)) + sizeof(ItemPointerData) * nipd);
		if (newsize > Min(INDEX_SIZE_MASK, GinMaxItemSize))
		{
			if (errorTooBig)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("index row size %lu exceeds maximum %lu for index \"%s\"",
								(unsigned long) newsize,
								(unsigned long) Min(INDEX_SIZE_MASK,
													GinMaxItemSize),
								RelationGetRelationName(index))));
			return NULL;
		}

		itup = repalloc(itup, newsize);

		/* set new size */
		itup->t_info &= ~INDEX_SIZE_MASK;
		itup->t_info |= newsize;

		if (ipd)
			memcpy(GinGetPosting(itup), ipd, sizeof(ItemPointerData) * nipd);
		GinSetNPosting(itup, nipd);
	}
	else
	{
		/*
		 * Gin tuple without any ItemPointers should be large enough to keep
		 * one ItemPointer, to prevent inconsistency between
		 * ginHeapTupleFastCollect and ginEntryInsert called by
		 * ginHeapTupleInsert.	ginHeapTupleFastCollect forms tuple without
		 * extra pointer to heap, but ginEntryInsert (called for pending list
		 * cleanup during vacuum) will form the same tuple with one
		 * ItemPointer.
		 */
		newsize = MAXALIGN(SHORTALIGN(IndexTupleSize(itup)) + sizeof(ItemPointerData));
		if (newsize > Min(INDEX_SIZE_MASK, GinMaxItemSize))
		{
			if (errorTooBig)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("index row size %lu exceeds maximum %lu for index \"%s\"",
								(unsigned long) newsize,
								(unsigned long) Min(INDEX_SIZE_MASK,
													GinMaxItemSize),
								RelationGetRelationName(index))));
			return NULL;
		}

		GinSetNPosting(itup, 0);
	}
	return itup;
}