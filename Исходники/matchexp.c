match
gfc_match_defined_op_name (char *result, int error_flag)
{
  static const char * const badops[] = {
    "and", "or", "not", "eqv", "neqv", "eq", "ne", "ge", "le", "lt", "gt",
      NULL
  };

  char name[GFC_MAX_SYMBOL_LEN + 1];
  locus old_loc;
  match m;
  int i;

  old_loc = gfc_current_locus;

  m = gfc_match (" . %n .", name);
  if (m != MATCH_YES)
    return m;

  /* .true. and .false. have interpretations as constants.  Trying to
     use these as operators will fail at a later time.  */

  if (strcmp (name, "true") == 0 || strcmp (name, "false") == 0)
    {
      if (error_flag)
	goto error;
      gfc_current_locus = old_loc;
      return MATCH_NO;
    }

  for (i = 0; badops[i]; i++)
    if (strcmp (badops[i], name) == 0)
      goto error;

  for (i = 0; name[i]; i++)
    if (!ISALPHA (name[i]))
      {
	gfc_error ("Bad character %qc in OPERATOR name at %C", name[i]);
	return MATCH_ERROR;
      }

  strcpy (result, name);
  return MATCH_YES;

error:
  gfc_error ("The name %qs cannot be used as a defined operator at %C",
	     name);

  gfc_current_locus = old_loc;
  return MATCH_ERROR;
}