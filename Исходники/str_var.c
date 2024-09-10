/** Set or add data string, depending whether string is already defined. */
StringData *str_var_set(const char *name, const char *string, ...)
{
	/* Variables. */
	StringData *err = NULL, *st;
	va_list args;
	
	st = str_var_find(name);
	
	if (!st)
	{
		st = (StringData *)malloc(sizeof(StringData));
		HIP_IFEL(!st, NULL, "malloc()");
		memset(st, 0, sizeof(StringData));
		STRCPY(st->name, name);
		
		if (str_data_last)
		{
			str_data_last->next = (void *)st;
			str_data_last = st;
		}
		else
		{
			str_data = st;
			str_data_last = st;
		}

		str_count++;
	}
	
	va_start(args, string);
	VSPRINTHUGESTR(st->data, string, args);
	va_end(args);

out_err:
	return err;
}