char *catcierge_relative_path(const char *pfrom, const char *pto)
{
	char pout[1024];
	int is_from_dir = 0;
	int is_to_dir =  0;
	char last_from_char = 0;
	char last_to_char = 0;

	if (!pfrom) return NULL;
	if (!pto) return NULL;

	last_from_char = pfrom[strlen(pfrom) - 1];
	last_to_char = pto[strlen(pto) - 1];

	// If we got a trailing slash we consider the path
	// a directory. This is required for the windows version.
	if ((last_to_char == '/') || (last_to_char == '\\'))
	{
		is_to_dir = 1;
	}

	if ((last_from_char == '/') || (last_from_char == '\\'))
	{
		is_from_dir = 1;
	}

	#ifdef _WIN32
	if (!PathRelativePathToA(pout,
			pfrom,
			is_from_dir ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL,
			pto,
			is_to_dir ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL))
	{
		return NULL;
	}

	// TODO: Make sure paths are returned wiht a / on windows

	return strdup(pout);

	#else // Unix
	{
		// Remove common first part of path.
		const char *f = pfrom;
		const char *t = pto; // Relative to.
		int i;
		size_t prefix_len;
		char dst[4096] = {0};

		// Special case :)
		if (!strcmp(pfrom, "/") && !strcmp(pto, "/"))
			return strdup("/");

		prefix_len = catcierge_path_common_prefix(f, t);
		f += prefix_len;
		t += prefix_len;

		if (*t == '/') t++;
		if (*f == '/') f++;

		i = 0;

		while ((f = catcierge_path_find_next_component(f)) != NULL)
		{
			i++;

			// If we are calculating relative from a file path
			// remove the file first, or it will be counted as a dir.
			if ((i == 1) && !is_from_dir)
			{
				continue;
			}

			strcat(dst, "../");
		}

		strcat(dst, t);

		return strdup(dst);
	}

	return NULL;

	#endif
}