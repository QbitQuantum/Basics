/* Define __GNUC__, __GNUC_MINOR__ and __GNUC_PATCHLEVEL__.  */
static void
define__GNUC__ (void)
{
  /* The format of the version string, enforced below, is
     ([^0-9]*-)?[0-9]+[.][0-9]+([.][0-9]+)?([- ].*)?  */
  const char *q, *v = version_string;

  while (*v && ! ISDIGIT (*v))
    v++;
  if (!*v || (v > version_string && v[-1] != '-'))
    abort ();

  q = v;
  while (ISDIGIT (*v))
    v++;
  builtin_define_with_value_n ("__GNUC__", q, v - q);
  if (c_dialect_cxx ())
    builtin_define_with_value_n ("__GNUG__", q, v - q);

  if (*v != '.' || !ISDIGIT (v[1]))
    abort ();
  q = ++v;
  while (ISDIGIT (*v))
    v++;
  builtin_define_with_value_n ("__GNUC_MINOR__", q, v - q);

  if (*v == '.')
    {
      if (!ISDIGIT (v[1]))
	abort ();
      q = ++v;
      while (ISDIGIT (*v))
	v++;
      builtin_define_with_value_n ("__GNUC_PATCHLEVEL__", q, v - q);
    }
  else
    builtin_define_with_value_n ("__GNUC_PATCHLEVEL__", "0", 1);

  if (*v && *v != ' ' && *v != '-')
    abort ();
}