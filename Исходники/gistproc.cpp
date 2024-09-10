/*
 * --------------------------------------------------------------------------
 * Double sorting split algorithm. This is used for both boxes and points.
 *
 * The algorithm finds split of boxes by considering splits along each axis.
 * Each entry is first projected as an interval on the X-axis, and different
 * ways to split the intervals into two groups are considered, trying to
 * minimize the overlap of the groups. Then the same is repeated for the
 * Y-axis, and the overall best split is chosen. The quality of a split is
 * determined by overlap along that axis and some other criteria (see
 * g_box_consider_split).
 *
 * After that, all the entries are divided into three groups:
 *
 * 1) Entries which should be placed to the left group
 * 2) Entries which should be placed to the right group
 * 3) "Common entries" which can be placed to any of groups without affecting
 *	  of overlap along selected axis.
 *
 * The common entries are distributed by minimizing penalty.
 *
 * For details see:
 * "A new___ double sorting-based node splitting algorithm for R-tree", A. Korotkov
 * http://syrcose.ispras.ru/2011/files/SYRCoSE2011_Proceedings.pdf#page=36
 * --------------------------------------------------------------------------
 */
Datum
gist_box_picksplit(PG_FUNCTION_ARGS)
{
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);
	GIST_SPLITVEC *v = (GIST_SPLITVEC *) PG_GETARG_POINTER(1);
	OffsetNumber i,
				maxoff;
	ConsiderSplitContext context;
	BOX		   *box,
			   *leftBox,
			   *rightBox;
	int			dim,
				commonEntriesCount;
	SplitInterval *intervalsLower,
			   *intervalsUpper;
	CommonEntry *commonEntries;
	int			nentries;

	memset(&context, 0, sizeof(ConsiderSplitContext));

	maxoff = entryvec->n - 1;
	nentries = context.entriesCount = maxoff - FirstOffsetNumber + 1;

	/* Allocate arrays for intervals along axes */
	intervalsLower = (SplitInterval *) palloc(nentries * sizeof(SplitInterval));
	intervalsUpper = (SplitInterval *) palloc(nentries * sizeof(SplitInterval));

	/*
	 * Calculate the overall minimum bounding box over all the entries.
	 */
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		box = DatumGetBoxP(entryvec->vector[i].key);
		if (i == FirstOffsetNumber)
			context.boundingBox = *box;
		else
			adjustBox(&context.boundingBox, box);
	}

	/*
	 * Iterate over axes for optimal split searching.
	 */
	context.first = true;		/* nothing selected yet */
	for (dim = 0; dim < 2; dim++)
	{
		double		leftUpper,
					rightLower;
		int			i1,
					i2;

		/* Project each entry as an interval on the selected axis. */
		for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
		{
			box = DatumGetBoxP(entryvec->vector[i].key);
			if (dim == 0)
			{
				intervalsLower[i - FirstOffsetNumber].lower = box->low.x;
				intervalsLower[i - FirstOffsetNumber].upper = box->high.x;
			}
			else
			{
				intervalsLower[i - FirstOffsetNumber].lower = box->low.y;
				intervalsLower[i - FirstOffsetNumber].upper = box->high.y;
			}
		}

		/*
		 * Make two arrays of intervals: one sorted by lower bound and another
		 * sorted by upper bound.
		 */
		memcpy(intervalsUpper, intervalsLower,
			   sizeof(SplitInterval) * nentries);
		qsort(intervalsLower, nentries, sizeof(SplitInterval),
			  interval_cmp_lower);
		qsort(intervalsUpper, nentries, sizeof(SplitInterval),
			  interval_cmp_upper);

		/*----
		 * The goal is to form a left and right interval, so that every entry
		 * interval is contained by either left or right interval (or both).
		 *
		 * For example, with the intervals (0,1), (1,3), (2,3), (2,4):
		 *
		 * 0 1 2 3 4
		 * +-+
		 *	 +---+
		 *	   +-+
		 *	   +---+
		 *
		 * The left and right intervals are of the form (0,a) and (b,4).
		 * We first consider splits where b is the lower bound of an entry.
		 * We iterate through all entries, and for each b, calculate the
		 * smallest possible a. Then we consider splits where a is the
		 * uppper bound of an entry, and for each a, calculate the greatest
		 * possible b.
		 *
		 * In the above example, the first loop would consider splits:
		 * b=0: (0,1)-(0,4)
		 * b=1: (0,1)-(1,4)
		 * b=2: (0,3)-(2,4)
		 *
		 * And the second loop:
		 * a=1: (0,1)-(1,4)
		 * a=3: (0,3)-(2,4)
		 * a=4: (0,4)-(2,4)
		 */

		/*
		 * Iterate over lower bound of right group, finding smallest possible
		 * upper bound of left group.
		 */
		i1 = 0;
		i2 = 0;
		rightLower = intervalsLower[i1].lower;
		leftUpper = intervalsUpper[i2].lower;
		while (true)
		{
			/*
			 * Find next lower bound of right group.
			 */
			while (i1 < nentries && rightLower == intervalsLower[i1].lower)
			{
				leftUpper = Max(leftUpper, intervalsLower[i1].upper);
				i1++;
			}
			if (i1 >= nentries)
				break;
			rightLower = intervalsLower[i1].lower;

			/*
			 * Find count of intervals which anyway should be placed to the
			 * left group.
			 */
			while (i2 < nentries && intervalsUpper[i2].upper <= leftUpper)
				i2++;

			/*
			 * Consider found split.
			 */
			g_box_consider_split(&context, dim, rightLower, i1, leftUpper, i2);
		}

		/*
		 * Iterate over upper bound of left group finding greates possible
		 * lower bound of right group.
		 */
		i1 = nentries - 1;
		i2 = nentries - 1;
		rightLower = intervalsLower[i1].upper;
		leftUpper = intervalsUpper[i2].upper;
		while (true)
		{
			/*
			 * Find next upper bound of left group.
			 */
			while (i2 >= 0 && leftUpper == intervalsUpper[i2].upper)
			{
				rightLower = Min(rightLower, intervalsUpper[i2].lower);
				i2--;
			}
			if (i2 < 0)
				break;
			leftUpper = intervalsUpper[i2].upper;

			/*
			 * Find count of intervals which anyway should be placed to the
			 * right group.
			 */
			while (i1 >= 0 && intervalsLower[i1].lower >= rightLower)
				i1--;

			/*
			 * Consider found split.
			 */
			g_box_consider_split(&context, dim,
								 rightLower, i1 + 1, leftUpper, i2 + 1);
		}
	}

	/*
	 * If we failed to find any acceptable splits, use trivial split.
	 */
	if (context.first)
	{
		fallbackSplit(entryvec, v);
		PG_RETURN_POINTER(v);
	}

	/*
	 * Ok, we have now selected the split across one axis.
	 *
	 * While considering the splits, we already determined that there will be
	 * enough entries in both groups to reach the desired ratio, but we did
	 * not memorize which entries go to which group. So determine that now.
	 */

	/* Allocate vectors for results */
	v->spl_left = (OffsetNumber *) palloc(nentries * sizeof(OffsetNumber));
	v->spl_right = (OffsetNumber *) palloc(nentries * sizeof(OffsetNumber));
	v->spl_nleft = 0;
	v->spl_nright = 0;

	/* Allocate bounding boxes of left and right groups */
	leftBox = static_cast<BOX *>(palloc0(sizeof(BOX)));
	rightBox = static_cast<BOX *>(palloc0(sizeof(BOX)));

	/*
	 * Allocate an array for "common entries" - entries which can be placed to
	 * either group without affecting overlap along selected axis.
	 */
	commonEntriesCount = 0;
	commonEntries = (CommonEntry *) palloc(nentries * sizeof(CommonEntry));

	/* Helper macros to place an entry in the left or right group */
#define PLACE_LEFT(box, off)					\
	do {										\
		if (v->spl_nleft > 0)					\
			adjustBox(leftBox, box);			\
		else									\
			*leftBox = *(box);					\
		v->spl_left[v->spl_nleft++] = off;		\
	} while(0)

#define PLACE_RIGHT(box, off)					\
	do {										\
		if (v->spl_nright > 0)					\
			adjustBox(rightBox, box);			\
		else									\
			*rightBox = *(box);					\
		v->spl_right[v->spl_nright++] = off;	\
	} while(0)

	/*
	 * Distribute entries which can be distributed unambiguously, and collect
	 * common entries.
	 */
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		double		lower,
					upper;

		/*
		 * Get upper and lower bounds along selected axis.
		 */
		box = DatumGetBoxP(entryvec->vector[i].key);
		if (context.dim == 0)
		{
			lower = box->low.x;
			upper = box->high.x;
		}
		else
		{
			lower = box->low.y;
			upper = box->high.y;
		}

		if (upper <= context.leftUpper)
		{
			/* Fits to the left group */
			if (lower >= context.rightLower)
			{
				/* Fits also to the right group, so "common entry" */
				commonEntries[commonEntriesCount++].index = i;
			}
			else
			{
				/* Doesn't fit to the right group, so join to the left group */
				PLACE_LEFT(box, i);
			}
		}
		else
		{
			/*
			 * Each entry should fit on either left or right group. Since this
			 * entry didn't fit on the left group, it better fit in the right
			 * group.
			 */
			Assert(lower >= context.rightLower);

			/* Doesn't fit to the left group, so join to the right group */
			PLACE_RIGHT(box, i);
		}
	}

	/*
	 * Distribute "common entries", if any.
	 */
	if (commonEntriesCount > 0)
	{
		/*
		 * Calculate minimum number of entries that must be placed in both
		 * groups, to reach LIMIT_RATIO.
		 */
		int			m = ceil(LIMIT_RATIO * (double) nentries);

		/*
		 * Calculate delta between penalties of join "common entries" to
		 * different groups.
		 */
		for (i = 0; i < commonEntriesCount; i++)
		{
			box = DatumGetBoxP(entryvec->vector[commonEntries[i].index].key);
			commonEntries[i].delta = Abs(box_penalty(leftBox, box) -
										 box_penalty(rightBox, box));
		}

		/*
		 * Sort "common entries" by calculated deltas in order to distribute
		 * the most ambiguous entries first.
		 */
		qsort(commonEntries, commonEntriesCount, sizeof(CommonEntry), common_entry_cmp);

		/*
		 * Distribute "common entries" between groups.
		 */
		for (i = 0; i < commonEntriesCount; i++)
		{
			box = DatumGetBoxP(entryvec->vector[commonEntries[i].index].key);

			/*
			 * Check if we have to place this entry in either group to achieve
			 * LIMIT_RATIO.
			 */
			if (v->spl_nleft + (commonEntriesCount - i) <= m)
				PLACE_LEFT(box, commonEntries[i].index);
			else if (v->spl_nright + (commonEntriesCount - i) <= m)
				PLACE_RIGHT(box, commonEntries[i].index);
			else
			{
				/* Otherwise select the group by minimal penalty */
				if (box_penalty(leftBox, box) < box_penalty(rightBox, box))
					PLACE_LEFT(box, commonEntries[i].index);
				else
					PLACE_RIGHT(box, commonEntries[i].index);
			}
		}
	}

	v->spl_ldatum = PointerGetDatum(leftBox);
	v->spl_rdatum = PointerGetDatum(rightBox);
	PG_RETURN_POINTER(v);
}