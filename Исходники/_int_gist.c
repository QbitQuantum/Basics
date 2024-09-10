/*
** The GiST PickSplit method for _intments
** We use Guttman's poly time split algorithm
*/
Datum
g_int_picksplit(PG_FUNCTION_ARGS)
{
	GistEntryVector *entryvec = (GistEntryVector *) PG_GETARG_POINTER(0);
	GIST_SPLITVEC *v = (GIST_SPLITVEC *) PG_GETARG_POINTER(1);
	OffsetNumber i,
				j;
	ArrayType  *datum_alpha,
			   *datum_beta;
	ArrayType  *datum_l,
			   *datum_r;
	ArrayType  *union_d,
			   *union_dl,
			   *union_dr;
	ArrayType  *inter_d;
	bool		firsttime;
	float		size_alpha,
				size_beta,
				size_union,
				size_inter;
	float		size_waste,
				waste;
	float		size_l,
				size_r;
	int			nbytes;
	OffsetNumber seed_1 = 0,
				seed_2 = 0;
	OffsetNumber *left,
			   *right;
	OffsetNumber maxoff;
	SPLITCOST  *costvector;

#ifdef GIST_DEBUG
	elog(DEBUG3, "--------picksplit %d", entryvec->n);
#endif

	maxoff = entryvec->n - 2;
	nbytes = (maxoff + 2) * sizeof(OffsetNumber);
	v->spl_left = (OffsetNumber *) palloc(nbytes);
	v->spl_right = (OffsetNumber *) palloc(nbytes);

	firsttime = true;
	waste = 0.0;
	for (i = FirstOffsetNumber; i < maxoff; i = OffsetNumberNext(i))
	{
		datum_alpha = GETENTRY(entryvec, i);
		for (j = OffsetNumberNext(i); j <= maxoff; j = OffsetNumberNext(j))
		{
			datum_beta = GETENTRY(entryvec, j);

			/* compute the wasted space by unioning these guys */
			/* size_waste = size_union - size_inter; */
			union_d = inner_int_union(datum_alpha, datum_beta);
			rt__int_size(union_d, &size_union);
			inter_d = inner_int_inter(datum_alpha, datum_beta);
			rt__int_size(inter_d, &size_inter);
			size_waste = size_union - size_inter;

			pfree(union_d);
			pfree(inter_d);

			/*
			 * are these a more promising split that what we've already seen?
			 */

			if (size_waste > waste || firsttime)
			{
				waste = size_waste;
				seed_1 = i;
				seed_2 = j;
				firsttime = false;
			}
		}
	}

	left = v->spl_left;
	v->spl_nleft = 0;
	right = v->spl_right;
	v->spl_nright = 0;
	if (seed_1 == 0 || seed_2 == 0)
	{
		seed_1 = 1;
		seed_2 = 2;
	}

	datum_alpha = GETENTRY(entryvec, seed_1);
	datum_l = copy_intArrayType(datum_alpha);
	rt__int_size(datum_l, &size_l);
	datum_beta = GETENTRY(entryvec, seed_2);
	datum_r = copy_intArrayType(datum_beta);
	rt__int_size(datum_r, &size_r);

	maxoff = OffsetNumberNext(maxoff);

	/*
	 * sort entries
	 */
	costvector = (SPLITCOST *) palloc(sizeof(SPLITCOST) * maxoff);
	for (i = FirstOffsetNumber; i <= maxoff; i = OffsetNumberNext(i))
	{
		costvector[i - 1].pos = i;
		datum_alpha = GETENTRY(entryvec, i);
		union_d = inner_int_union(datum_l, datum_alpha);
		rt__int_size(union_d, &size_alpha);
		pfree(union_d);
		union_d = inner_int_union(datum_r, datum_alpha);
		rt__int_size(union_d, &size_beta);
		pfree(union_d);
		costvector[i - 1].cost = Abs((size_alpha - size_l) - (size_beta - size_r));
	}
	qsort((void *) costvector, maxoff, sizeof(SPLITCOST), comparecost);

	/*
	 * Now split up the regions between the two seeds.  An important property
	 * of this split algorithm is that the split vector v has the indices of
	 * items to be split in order in its left and right vectors.  We exploit
	 * this property by doing a merge in the code that actually splits the
	 * page.
	 *
	 * For efficiency, we also place the new index tuple in this loop. This is
	 * handled at the very end, when we have placed all the existing tuples
	 * and i == maxoff + 1.
	 */


	for (j = 0; j < maxoff; j++)
	{
		i = costvector[j].pos;

		/*
		 * If we've already decided where to place this item, just put it on
		 * the right list.  Otherwise, we need to figure out which page needs
		 * the least enlargement in order to store the item.
		 */

		if (i == seed_1)
		{
			*left++ = i;
			v->spl_nleft++;
			continue;
		}
		else if (i == seed_2)
		{
			*right++ = i;
			v->spl_nright++;
			continue;
		}

		/* okay, which page needs least enlargement? */
		datum_alpha = GETENTRY(entryvec, i);
		union_dl = inner_int_union(datum_l, datum_alpha);
		union_dr = inner_int_union(datum_r, datum_alpha);
		rt__int_size(union_dl, &size_alpha);
		rt__int_size(union_dr, &size_beta);

		/* pick which page to add it to */
		if (size_alpha - size_l < size_beta - size_r + WISH_F(v->spl_nleft, v->spl_nright, 0.01))
		{
			pfree(datum_l);
			pfree(union_dr);
			datum_l = union_dl;
			size_l = size_alpha;
			*left++ = i;
			v->spl_nleft++;
		}
		else
		{
			pfree(datum_r);
			pfree(union_dl);
			datum_r = union_dr;
			size_r = size_beta;
			*right++ = i;
			v->spl_nright++;
		}
	}
	pfree(costvector);
	*right = *left = FirstOffsetNumber;

	v->spl_ldatum = PointerGetDatum(datum_l);
	v->spl_rdatum = PointerGetDatum(datum_r);

	PG_RETURN_POINTER(v);
}