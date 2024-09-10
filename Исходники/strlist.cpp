	// Same as find() but case sensitive
	int findWithCase(const char *s)
	{
		int len = list.length();
		for(int i = 0; i < len; i++)
		{
			const char *ms = (const char *)list.get(i);
			if(Str::equalsCase(ms, s))
				return i;
		}
		return -1;
	}