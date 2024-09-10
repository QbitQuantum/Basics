const char *
dos_lbasename (const char *name)
{
  const char *base;

  /* Skip over a possible disk name.  */
  if (ISALPHA (name[0]) && name[1] == ':') 
    name += 2;

  for (base = name; *name; name++)
    if (IS_DOS_DIR_SEPARATOR (*name))
      base = name + 1;

  return base;
}