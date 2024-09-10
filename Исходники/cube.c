/* make up a metric in which one box will be 'lower' than the other
   -- this can be useful for sorting and to determine uniqueness */
int32
cube_cmp_v0(NDBOX *a, NDBOX *b)
{
	int			i;
	int			dim;

	dim = Min(DIM(a), DIM(b));

	/* compare the common dimensions */
	for (i = 0; i < dim; i++)
	{
		if (Min(LL_COORD(a, i), UR_COORD(a, i)) >
			Min(LL_COORD(b, i), UR_COORD(b, i)))
			return 1;
		if (Min(LL_COORD(a, i), UR_COORD(a, i)) <
			Min(LL_COORD(b, i), UR_COORD(b, i)))
			return -1;
	}
	for (i = 0; i < dim; i++)
	{
		if (Max(LL_COORD(a, i), UR_COORD(a, i)) >
			Max(LL_COORD(b, i), UR_COORD(b, i)))
			return 1;
		if (Max(LL_COORD(a, i), UR_COORD(a, i)) <
			Max(LL_COORD(b, i), UR_COORD(b, i)))
			return -1;
	}

	/* compare extra dimensions to zero */
	if (DIM(a) > DIM(b))
	{
		for (i = dim; i < DIM(a); i++)
		{
			if (Min(LL_COORD(a, i), UR_COORD(a, i)) > 0)
				return 1;
			if (Min(LL_COORD(a, i), UR_COORD(a, i)) < 0)
				return -1;
		}
		for (i = dim; i < DIM(a); i++)
		{
			if (Max(LL_COORD(a, i), UR_COORD(a, i)) > 0)
				return 1;
			if (Max(LL_COORD(a, i), UR_COORD(a, i)) < 0)
				return -1;
		}

		/*
		 * if all common dimensions are equal, the cube with more dimensions
		 * wins
		 */
		return 1;
	}
	if (DIM(a) < DIM(b))
	{
		for (i = dim; i < DIM(b); i++)
		{
			if (Min(LL_COORD(b, i), UR_COORD(b, i)) > 0)
				return -1;
			if (Min(LL_COORD(b, i), UR_COORD(b, i)) < 0)
				return 1;
		}
		for (i = dim; i < DIM(b); i++)
		{
			if (Max(LL_COORD(b, i), UR_COORD(b, i)) > 0)
				return -1;
			if (Max(LL_COORD(b, i), UR_COORD(b, i)) < 0)
				return 1;
		}

		/*
		 * if all common dimensions are equal, the cube with more dimensions
		 * wins
		 */
		return -1;
	}

	/* They're really equal */
	return 0;
}