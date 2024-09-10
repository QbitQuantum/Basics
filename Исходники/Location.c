void
boundary_set_from_string (boundary *bound, char *loc_str)
{
  /* Must search in reverse since the file name field may
   * contain `.' or `:'.  */
  char *delim = _mbsrchr (loc_str, '.');
  aver (delim);
  *delim = '\0';
  bound->column = atoi (delim+1);
  delim = _mbsrchr (loc_str, ':');
  aver (delim);
  *delim = '\0';
  bound->line = atoi (delim+1);
  bound->file = uniqstr_new (loc_str);
}