int
STRCOLL (const STRING_TYPE *s1, const STRING_TYPE *s2, locale_t l)
{
  struct __locale_data *current = l->__locales[LC_COLLATE];
  uint_fast32_t nrules = current->values[_NL_ITEM_INDEX (_NL_COLLATE_NRULES)].word;
  /* We don't assign the following values right away since it might be
     unnecessary in case there are no rules.  */
  const unsigned char *rulesets;
  const int32_t *table;
  const USTRING_TYPE *weights;
  const USTRING_TYPE *extra;
  const int32_t *indirect;

  if (nrules == 0)
    return STRCMP (s1, s2);

  /* Catch empty strings.  */
  if (__glibc_unlikely (*s1 == '\0') || __glibc_unlikely (*s2 == '\0'))
    return (*s1 != '\0') - (*s2 != '\0');

  rulesets = (const unsigned char *)
    current->values[_NL_ITEM_INDEX (_NL_COLLATE_RULESETS)].string;
  table = (const int32_t *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_TABLE,SUFFIX))].string;
  weights = (const USTRING_TYPE *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_WEIGHT,SUFFIX))].string;
  extra = (const USTRING_TYPE *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_EXTRA,SUFFIX))].string;
  indirect = (const int32_t *)
    current->values[_NL_ITEM_INDEX (CONCAT(_NL_COLLATE_INDIRECT,SUFFIX))].string;

  assert (((uintptr_t) table) % __alignof__ (table[0]) == 0);
  assert (((uintptr_t) weights) % __alignof__ (weights[0]) == 0);
  assert (((uintptr_t) extra) % __alignof__ (extra[0]) == 0);
  assert (((uintptr_t) indirect) % __alignof__ (indirect[0]) == 0);

  int result = 0, rule = 0;

  coll_seq seq1, seq2;
  seq1.len = 0;
  seq1.idxmax = 0;
  seq1.rule = 0;
  seq2.len = 0;
  seq2.idxmax = 0;

  for (int pass = 0; pass < nrules; ++pass)
    {
      seq1.idxcnt = 0;
      seq1.idx = 0;
      seq2.idx = 0;
      seq1.backw_stop = ~0ul;
      seq1.backw = ~0ul;
      seq2.idxcnt = 0;
      seq2.backw_stop = ~0ul;
      seq2.backw = ~0ul;

      /* We need the elements of the strings as unsigned values since they
	 are used as indices.  */
      seq1.us = (const USTRING_TYPE *) s1;
      seq2.us = (const USTRING_TYPE *) s2;

      /* We assume that if a rule has defined `position' in one section
	 this is true for all of them.  Please note that the localedef programs
	 makes sure that `position' is not used at the first level.  */

      int position = rulesets[rule * nrules + pass] & sort_position;

      while (1)
	{
	  get_next_seq (&seq1, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  get_next_seq (&seq2, nrules, rulesets, weights, table,
				    extra, indirect, pass);
	  /* See whether any or both strings are empty.  */
	  if (seq1.len == 0 || seq2.len == 0)
	    {
	      if (seq1.len == seq2.len)
		{
		  /* Both strings ended and are equal at this level.  Do a
		     byte-level comparison to ensure that we don't waste time
		     going through multiple passes for totally equal strings
		     before proceeding to subsequent passes.  */
		  if (pass == 0 && STRCMP (s1, s2) == 0)
		    return result;
		  else
		    break;
	        }

	      /* This means one string is shorter than the other.  Find out
		 which one and return an appropriate value.  */
	      return seq1.len == 0 ? -1 : 1;
	    }

	  result = do_compare (&seq1, &seq2, position, weights);
	  if (result != 0)
	    return result;
	}

      rule = seq1.rule;
    }

  return result;
}