static void
add_one_ISBN_range(const char *the_begin, const char *the_end,
		   const char *the_countries, size_t where)
{	/* add an entry at slot where, without bounds checking, but with
	   valid-value checking */

    if (
	(the_begin != (const char*)NULL) && (is_valid_ISBN_prefix(the_begin) == NO) ||
        (the_end != (const char*)NULL) && (is_valid_ISBN_prefix(the_end) == NO)
    )
    {
	fprintf(stdlog, "Invalid country/language-publisher ISBN prefix [%s] in ISBN file [%s]\n", the_begin, ISBN_file);
	return;
    }
    else if ((the_begin != (const char*)NULL) && (the_end != (const char*)NULL) && STRGREATER(the_begin,the_end))
    {
	fprintf(stdlog,
		      "Non-increasing country/language-publisher ISBN range [%s .. %s] in ISBN file [%s]\n",
		      the_begin, the_end, ISBN_file);
	return;
    }

    ISBN_range[where].begin = (the_begin == (const char *)NULL) ? the_begin : Strdup(the_begin);
    ISBN_range[where].end = (the_end == (const char *)NULL) ? the_end : Strdup(the_end);
    ISBN_range[where].countries = (the_countries == (const char *)NULL) ? "" : Strdup(the_countries);
}