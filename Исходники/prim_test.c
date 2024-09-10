void primitives_flags_str(char* str, size_t len)
{
	int i;

	*str = '\0';
	--len;	/* for the '/0' */

	for (i = 0; i < sizeof(flags) / sizeof(flagpair_t); ++i)
	{
		if (IsProcessorFeaturePresent(flags[i].flag))
		{
			int slen = strlen(flags[i].str) + 1;

			if (len < slen)
				break;

			if (*str != '\0')
				strcat(str, " ");

			strcat(str, flags[i].str);
			len -= slen;
		}
	}
	for (i = 0; i < sizeof(flags_extended) / sizeof(flagpair_t); ++i)
	{
		if (IsProcessorFeaturePresentEx(flags_extended[i].flag))
		{
			int slen = strlen(flags_extended[i].str) + 1;

			if (len < slen)
				break;

			if (*str != '\0')
				strcat(str, " ");

			strcat(str, flags_extended[i].str);
			len -= slen;
		}
	}
}