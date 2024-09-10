Datum
set_timetravel(PG_FUNCTION_ARGS)
{
	Name		relname = PG_GETARG_NAME(0);
	int32		on = PG_GETARG_INT32(1);
	char	   *rname;
	char	   *d;
	char	   *s;
	int32		ret;
	TTOffList  *prev,
			   *pp;

	prev = NULL;
	for (pp = TTOff; pp; prev = pp, pp = pp->next)
	{
		if (namestrcmp(relname, pp->name) == 0)
			break;
	}
	if (pp)
	{
		/* OFF currently */
		if (on != 0)
		{
			/* turn ON */
			if (prev)
				prev->next = pp->next;
			else
				TTOff = pp->next;
			free(pp);
		}
		ret = 0;
	}
	else
	{
		/* ON currently */
		if (on == 0)
		{
			/* turn OFF */
			s = rname = DatumGetCString(DirectFunctionCall1(nameout, NameGetDatum(relname)));
			if (s)
			{
				pp = malloc(offsetof(TTOffList, name) + strlen(rname) + 1);
				if (pp)
				{
					pp->next = NULL;
					d = pp->name;
					while (*s)
						*d++ = tolower((unsigned char) *s++);
					*d = '\0';
					if (prev)
						prev->next = pp;
					else
						TTOff = pp;
				}
				pfree(rname);
			}
		}
		ret = 1;
	}
	PG_RETURN_INT32(ret);
}