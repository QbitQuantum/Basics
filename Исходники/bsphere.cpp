static int sort_and_split(BSPHERE_TREE **Root, BSPHERE_TREE ***Elements, int *nElem, int first, int last, int& maxelements)
{
	int size, i, best_loc;
	DBL *area_left, *area_right;
	DBL best_index, new_index;
	BSPHERE_TREE *cd;

	int Axis = find_axis(*Elements, first, last);

	size = last - first;

	if (size <= 0)
	{
		return (1);
	}

	/*
	 * Actually, we could do this faster in several ways. We could use a
	 * logn algorithm to find the median along the given axis, and then a
	 * linear algorithm to partition along the axis. Oh well.
	 */

	switch(Axis)
	{
		case X:
			QSORT((void *)(*Elements + first), size, sizeof(BSPHERE_TREE *), comp_elements<X>);
			break;
		case Y:
			QSORT((void *)(*Elements + first), size, sizeof(BSPHERE_TREE *), comp_elements<Y>);
			break;
		case Z:
			QSORT((void *)(*Elements + first), size, sizeof(BSPHERE_TREE *), comp_elements<Z>);
			break;
	}

	/*
	 * area_left[] and area_right[] hold the surface areas of the bounding
	 * boxes to the left and right of any given point. E.g. area_left[i] holds
	 * the surface area of the bounding box containing Elements 0 through i and
	 * area_right[i] holds the surface area of the box containing Elements
	 * i through size-1.
	 */

	area_left  = (DBL *)POV_MALLOC(size * sizeof(DBL), "blob bounding hierarchy");
	area_right = (DBL *)POV_MALLOC(size * sizeof(DBL), "blob bounding hierarchy");

	/* Precalculate the areas for speed. */

	build_area_table(*Elements, first, last - 1, area_left);
	build_area_table(*Elements, last - 1, first, area_right);

	best_index = area_right[0] * (size - 3.0);

	best_loc = - 1;

	/*
	 * Find the most effective point to split. The best location will be
	 * the one that minimizes the function N1*A1 + N2*A2 where N1 and N2
	 * are the number of objects in the two groups and A1 and A2 are the
	 * surface areas of the bounding boxes of the two groups.
	 */

	for (i = 0; i < size - 1; i++)
	{
		new_index = (i + 1) * area_left[i] + (size - 1 - i) * area_right[i + 1];

		if (new_index < best_index)
		{
			best_index = new_index;
			best_loc = i + first;
		}
	}

	POV_FREE(area_left);
	POV_FREE(area_right);

	/*
	 * Stop splitting if the BRANCHING_FACTOR is reached or
	 * if splitting stops being effective.
	 */

	if ((size <= BRANCHING_FACTOR) || (best_loc < 0))
	{
		cd = (BSPHERE_TREE *)POV_MALLOC(sizeof(BSPHERE_TREE), "blob bounding hierarchy");

		cd->Entries = (short)size;

		cd->Node = (BSPHERE_TREE **)POV_MALLOC(size*sizeof(BSPHERE_TREE *), "blob bounding hierarchy");

		for (i = 0; i < size; i++)
		{
			cd->Node[i] = (*Elements)[first+i];
		}

		recompute_bound(cd);

		*Root = cd;

		if (*nElem >= maxelements)
		{
			/* Prim array overrun, increase array by 50%. */

			maxelements = 1.5 * maxelements;

			/* For debugging only. */

// TODO FIXME			Debug_Info("Reallocing elements to %d\n", maxelements);

			*Elements = (BSPHERE_TREE **)POV_REALLOC(*Elements, maxelements * sizeof(BSPHERE_TREE *), "bounding slabs");
		}

		(*Elements)[*nElem] = cd;

		(*nElem)++;

		return (1);
	}
	else
	{
		sort_and_split(Root, Elements, nElem, first, best_loc + 1, maxelements);

		sort_and_split(Root, Elements, nElem, best_loc + 1, last, maxelements);

		return (0);
	}
}