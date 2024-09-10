/*
 * bms_subset_compare - compare A and B for equality/subset relationships
 *
 * This is more efficient than testing bms_is_subset in both directions.
 */
BMS_Comparison
bms_subset_compare(const Bitmapset *a, const Bitmapset *b)
{
	BMS_Comparison result;
	int			shortlen;
	int			longlen;
	int			i;

	/* Handle cases where either input is NULL */
	if (a == NULL)
	{
		if (b == NULL)
			return BMS_EQUAL;
		return bms_is_empty(b) ? BMS_EQUAL : BMS_SUBSET1;
	}
	if (b == NULL)
		return bms_is_empty(a) ? BMS_EQUAL : BMS_SUBSET2;
	/* Check common words */
	result = BMS_EQUAL;			/* status so far */
	shortlen = Min(a->nwords, b->nwords);
	for (i = 0; i < shortlen; i++)
	{
		bitmapword	aword = a->words[i];
		bitmapword	bword = b->words[i];

		if ((aword & ~bword) != 0)
		{
			/* a is not a subset of b */
			if (result == BMS_SUBSET1)
				return BMS_DIFFERENT;
			result = BMS_SUBSET2;
		}
		if ((bword & ~aword) != 0)
		{
			/* b is not a subset of a */
			if (result == BMS_SUBSET2)
				return BMS_DIFFERENT;
			result = BMS_SUBSET1;
		}
	}
	/* Check extra words */
	if (a->nwords > b->nwords)
	{
		longlen = a->nwords;
		for (; i < longlen; i++)
		{
			if (a->words[i] != 0)
			{
				/* a is not a subset of b */
				if (result == BMS_SUBSET1)
					return BMS_DIFFERENT;
				result = BMS_SUBSET2;
			}
		}
	}
	else if (a->nwords < b->nwords)
	{
		longlen = b->nwords;
		for (; i < longlen; i++)
		{
			if (b->words[i] != 0)
			{
				/* b is not a subset of a */
				if (result == BMS_SUBSET2)
					return BMS_DIFFERENT;
				result = BMS_SUBSET1;
			}
		}
	}
	return result;
}