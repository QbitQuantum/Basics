/*
 * Implements numeric sort for -n and -h.
 */
static int
numcoll_impl(struct key_value *kv1, struct key_value *kv2,
    size_t offset __unused, bool use_suffix)
{
	struct bwstring *s1, *s2;
	wchar_t sfrac1[MAX_NUM_SIZE + 1], sfrac2[MAX_NUM_SIZE + 1];
	wchar_t smain1[MAX_NUM_SIZE + 1], smain2[MAX_NUM_SIZE + 1];
	int cmp_res, sign1, sign2;
	size_t frac1, frac2, main1, main2;
	unsigned char SI1, SI2;
	bool e1, e2, key1_read, key2_read;

	s1 = kv1->k;
	s2 = kv2->k;
	sign1 = sign2 = 0;
	main1 = main2 = 0;
	frac1 = frac2 = 0;

	key1_read = key2_read = false;

	if (debug_sort) {
		bwsprintf(stdout, s1, "; k1=<", ">");
		bwsprintf(stdout, s2, ", k2=<", ">");
	}

	if (s1 == s2)
		return (0);

	if (kv1->hint->status == HS_UNINITIALIZED) {
		/* read the number from the string */
		read_number(s1, &sign1, smain1, &main1, sfrac1, &frac1, &SI1);
		key1_read = true;
		kv1->hint->v.nh.n1 = wcstoull(smain1, NULL, 10);
		if(main1 < 1 && frac1 < 1)
			kv1->hint->v.nh.empty=true;
		kv1->hint->v.nh.si = SI1;
		kv1->hint->status = (kv1->hint->v.nh.n1 != ULLONG_MAX) ?
		    HS_INITIALIZED : HS_ERROR;
		kv1->hint->v.nh.neg = (sign1 < 0) ? true : false;
	}

	if (kv2->hint->status == HS_UNINITIALIZED) {
		/* read the number from the string */
		read_number(s2, &sign2, smain2, &main2, sfrac2, &frac2,&SI2);
		key2_read = true;
		kv2->hint->v.nh.n1 = wcstoull(smain2, NULL, 10);
		if(main2 < 1 && frac2 < 1)
			kv2->hint->v.nh.empty=true;
		kv2->hint->v.nh.si = SI2;
		kv2->hint->status = (kv2->hint->v.nh.n1 != ULLONG_MAX) ?
		    HS_INITIALIZED : HS_ERROR;
		kv2->hint->v.nh.neg = (sign2 < 0) ? true : false;
	}

	if (kv1->hint->status == HS_INITIALIZED && kv2->hint->status ==
	    HS_INITIALIZED) {
		unsigned long long n1, n2;
		bool neg1, neg2;

		e1 = kv1->hint->v.nh.empty;
		e2 = kv2->hint->v.nh.empty;

		if (e1 && e2)
			return (0);

		neg1 = kv1->hint->v.nh.neg;
		neg2 = kv2->hint->v.nh.neg;

		if (neg1 && !neg2)
			return (-1);
		if (neg2 && !neg1)
			return (+1);

		if (e1)
			return (neg2 ? +1 : -1);
		else if (e2)
			return (neg1 ? -1 : +1);


		if (use_suffix) {
			cmp_res = cmpsuffix(kv1->hint->v.nh.si, kv2->hint->v.nh.si);
			if (cmp_res)
				return (neg1 ? -cmp_res : cmp_res);
		}

		n1 = kv1->hint->v.nh.n1;
		n2 = kv2->hint->v.nh.n1;
		if (n1 < n2)
			return (neg1 ? +1 : -1);
		else if (n1 > n2)
			return (neg1 ? -1 : +1);
	}

	/* read the numbers from the strings */
	if (!key1_read)
		read_number(s1, &sign1, smain1, &main1, sfrac1, &frac1, &SI1);
	if (!key2_read)
		read_number(s2, &sign2, smain2, &main2, sfrac2, &frac2, &SI2);

	e1 = ((main1 + frac1) == 0);
	e2 = ((main2 + frac2) == 0);

	if (e1 && e2)
		return (0);

	/* we know the result if the signs are different */
	if (sign1 < 0 && sign2 >= 0)
		return (-1);
	if (sign1 >= 0 && sign2 < 0)
		return (+1);

	if (e1)
		return ((sign2 < 0) ? +1 : -1);
	else if (e2)
		return ((sign1 < 0) ? -1 : +1);

	if (use_suffix) {
		cmp_res = cmpsuffix(SI1, SI2);
		if (cmp_res)
			return ((sign1 < 0) ? -cmp_res : cmp_res);
	}

	/* if both numbers are empty assume that the strings are equal */
	if (main1 < 1 && main2 < 1 && frac1 < 1 && frac2 < 1)
		return (0);

	/*
	 * if the main part is of different size, we know the result
	 * (because the leading zeros are removed)
	 */
	if (main1 < main2)
		cmp_res = -1;
	else if (main1 > main2)
		cmp_res = +1;
	/* if the sizes are equal then simple non-collate string compare gives the correct result */
	else
		cmp_res = wcscmp(smain1, smain2);

	/* check fraction */
	if (!cmp_res)
		cmp_res = wcscmp(sfrac1, sfrac2);

	if (!cmp_res)
		return (0);

	/* reverse result if the signs are negative */
	if (sign1 < 0 && sign2 < 0)
		cmp_res = -cmp_res;

	return (cmp_res);
}