int
check_macro (const char *line, sb *expand,
	     const char **error, macro_entry **info)
{
  const char *s;
  char *copy, *cs;
  macro_entry *macro;
  sb line_sb;

  if (! ISALPHA (*line)
      && *line != '_'
      && *line != '$'
      && (! macro_mri || *line != '.'))
    return 0;

  s = line + 1;
  while (ISALNUM (*s)
	 || *s == '_'
	 || *s == '$')
    ++s;

  copy = (char *) alloca (s - line + 1);
  memcpy (copy, line, s - line);
  copy[s - line] = '\0';
  for (cs = copy; *cs != '\0'; cs++)
    *cs = TOLOWER (*cs);

  macro = (macro_entry *) hash_find (macro_hash, copy);

  if (macro == NULL)
    return 0;

  /* Wrap the line up in an sb.  */
  sb_new (&line_sb);
  while (*s != '\0' && *s != '\n' && *s != '\r')
    sb_add_char (&line_sb, *s++);

  sb_new (expand);
  *error = macro_expand (0, &line_sb, macro, expand);

  sb_kill (&line_sb);

  /* Export the macro information if requested.  */
  if (info)
    *info = macro;

  return 1;
}