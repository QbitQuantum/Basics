/* We provide support for some special names.  This helps debugging
   and may be useful for advanced usage of the provided information
   outside C.  */
void
locale_special (const char *name, int show_category_name,
		int show_keyword_name)
{
#if 0
  /* "collate-elements": print collation elements of locale.  */
  if (strcmp (name, "collate-elements") == 0)
    {
      size_t nelem = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_ELEM_HASH_SIZE);

      if (show_category_name)
	puts ("LC_COLLATE");
      if (show_keyword_name)
	fputs ("collate-elements=", stdout);

      if (nelem != 0)
	{
	  int first = 1;
	  size_t cnt;

	  for (cnt = 0; cnt < nelem; ++cnt)
	    if (__collate_element_hash[2 * cnt] != (~((u_int32_t) 0)))
	      {
		size_t idx = __collate_element_hash[2 * cnt];

		printf ("%s<%s>", first ? "" : ";",
			&__collate_element_strings[idx]);

		/* We don't print the string.  This is only confusing
		   because only the programs have to know the
		   encoding.  The code is left in place because it
		   shows how to get the information.  */
		{
		  const wchar_t *wp;

		  idx = __collate_element_hash[2 * cnt + 1];
		  wp = &__collate_element_values[idx];
		  while (*wp != L'\0')
		    {
		      /********************************************\
		      |* XXX The element values are really wide	  *|
		      |* chars.  But we are currently not able to *|
		      |* print these so fake here.		  *|
		      \********************************************/
		      int ch = wctob (*wp++);
		      if (ch != EOF)
			putchar (ch);
		      else
			fputs ("<??\?>", stdout);
		    }

		  putchar ('"');
		}
		first = 0;
	      }
	}
      putchar ('\n');
      return;
    }

  if (strcmp (name, "collate-classes") == 0)
    {
      size_t nelem = _NL_CURRENT_WORD (LC_COLLATE, _NL_COLLATE_SYMB_HASH_SIZE);
      size_t cnt;
      int first = 1;

      if (show_category_name)
	puts ("LC_COLLATE");
      if (show_keyword_name)
	fputs ("collate-classes=", stdout);

      for (cnt = 0; cnt < nelem; ++cnt)
	if (__collate_symbol_hash[2 * cnt] != 0xffffffff)
	  {
	    printf ("%s<%s>", first ? "" : ",",
		    &__collate_symbol_strings[__collate_symbol_hash[2 * cnt]]);
#if 0
	    {
	      size_t idx = __collate_symbol_hash[2 * cnt + 1];
	      size_t cls;

	      putchar ('=');
	      for (cls = 0; cls < __collate_symbol_classes[idx]; ++cls)
		printf ("%s%d", cls == 0 ? "" : ":",
			__collate_symbol_classes[idx + 1 + cls]);
	    }
#endif
	    first = 0;
	  }
      putchar ('\n');
      return;
    }
#endif
}