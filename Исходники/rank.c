static float
calc_rank_and(float *w, tsvector * t, QUERYTYPE * q)
{
	uint16	  **pos;
	int			i,
				k,
				l,
				p;
	WordEntry  *entry;
	WordEntryPos *post,
			   *ct;
	int4		dimt,
				lenct,
				dist;
	float		res = -1.0;
	ITEM	  **item;
	int			size = q->size;

	item = SortAndUniqItems(GETOPERAND(q), GETQUERY(q), &size);
	if (size < 2)
	{
		pfree(item);
		return calc_rank_or(w, t, q);
	}
	pos = (uint16 **) palloc(sizeof(uint16 *) * q->size);
	memset(pos, 0, sizeof(uint16 *) * q->size);
	*(uint16 *) POSNULL = lengthof(POSNULL) - 1;
	WEP_SETPOS(POSNULL[1], MAXENTRYPOS - 1);

	for (i = 0; i < size; i++)
	{
		entry = find_wordentry(t, q, item[i]);
		if (!entry)
			continue;

		if (entry->haspos)
			pos[i] = (uint16 *) _POSDATAPTR(t, entry);
		else
			pos[i] = (uint16 *) POSNULL;


		dimt = *(uint16 *) (pos[i]);
		post = (WordEntryPos *) (pos[i] + 1);
		for (k = 0; k < i; k++)
		{
			if (!pos[k])
				continue;
			lenct = *(uint16 *) (pos[k]);
			ct = (WordEntryPos *) (pos[k] + 1);
			for (l = 0; l < dimt; l++)
			{
				for (p = 0; p < lenct; p++)
				{
					dist = Abs((int) WEP_GETPOS(post[l]) - (int) WEP_GETPOS(ct[p]));
					if (dist || (dist == 0 && (pos[i] == (uint16 *) POSNULL || pos[k] == (uint16 *) POSNULL)))
					{
						float		curw;

						if (!dist)
							dist = MAXENTRYPOS;
						curw = sqrt(wpos(post[l]) * wpos(ct[p]) * word_distance(dist));
						res = (res < 0) ? curw : 1.0 - (1.0 - res) * (1.0 - curw);
					}
				}
			}
		}
	}
	pfree(pos);
	pfree(item);
	return res;
}