static bool
parse_feature_tag (const char **pp, const char *end, hb_feature_t *feature)
{
  parse_space (pp, end);

  char quote = 0;

  if (*pp < end && (**pp == '\'' || **pp == '"'))
  {
    quote = **pp;
    (*pp)++;
  }

  const char *p = *pp;
  while (*pp < end && ISALNUM(**pp))
    (*pp)++;

  if (p == *pp || *pp - p > 4)
    return false;

  feature->tag = hb_tag_from_string (p, *pp - p);

  if (quote)
  {
    /* CSS expects exactly four bytes.  And we only allow quotations for
     * CSS compatibility.  So, enforce the length. */
     if (*pp - p != 4)
       return false;
    if (*pp == end || **pp != quote)
      return false;
    (*pp)++;
  }

  return true;
}