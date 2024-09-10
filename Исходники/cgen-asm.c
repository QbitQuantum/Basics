const char *
cgen_parse_keyword (CGEN_CPU_DESC cd ATTRIBUTE_UNUSED,
		    const char **strp,
		    CGEN_KEYWORD *keyword_table,
		    long *valuep)
{
  const CGEN_KEYWORD_ENTRY *ke;
  char buf[256];
  const char *p,*start;

  if (keyword_table->name_hash_table == NULL)
    (void) cgen_keyword_search_init (keyword_table, NULL);

  p = start = *strp;

  /* Allow any first character.  This is to make life easier for
     the fairly common case of suffixes, eg. 'ld.b.w', where the first
     character of the suffix ('.') is special.  */
  if (*p)
    ++p;
  
  /* Allow letters, digits, and any special characters.  */
  while (((p - start) < (int) sizeof (buf))
	 && *p
	 && (ISALNUM (*p)
	     || *p == '_'
	     || strchr (keyword_table->nonalpha_chars, *p)))
    ++p;

  if (p - start >= (int) sizeof (buf))
    {
      /* All non-empty CGEN keywords can fit into BUF.  The only thing
	 we can match here is the empty keyword.  */
      buf[0] = 0;
    }
  else
    {
      memcpy (buf, start, p - start);
      buf[p - start] = 0;
    }

  ke = cgen_keyword_lookup_name (keyword_table, buf);

  if (ke != NULL)
    {
      *valuep = ke->value;
      /* Don't advance pointer if we recognized the null keyword.  */
      if (ke->name[0] != 0)
	*strp = p;
      return NULL;
    }

  return "unrecognized keyword/register name";
}