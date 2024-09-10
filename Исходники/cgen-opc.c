void
cgen_keyword_add (CGEN_KEYWORD *kt, CGEN_KEYWORD_ENTRY *ke)
{
  unsigned int hash;
  size_t i;

  if (kt->name_hash_table == NULL)
    build_keyword_hash_tables (kt);

  hash = hash_keyword_name (kt, ke->name, 0);
  ke->next_name = kt->name_hash_table[hash];
  kt->name_hash_table[hash] = ke;

  hash = hash_keyword_value (kt, ke->value);
  ke->next_value = kt->value_hash_table[hash];
  kt->value_hash_table[hash] = ke;

  if (ke->name[0] == 0)
    kt->null_entry = ke;

  for (i = 1; i < strlen (ke->name); i++)
    if (! ISALNUM (ke->name[i])
	&& ! strchr (kt->nonalpha_chars, ke->name[i]))
      {
	size_t idx = strlen (kt->nonalpha_chars);
	
	/* If you hit this limit, please don't just
	   increase the size of the field, instead
	   look for a better algorithm.  */
	if (idx >= sizeof (kt->nonalpha_chars) - 1)
	  abort ();
	kt->nonalpha_chars[idx] = ke->name[i];
	kt->nonalpha_chars[idx+1] = 0;
      }
}