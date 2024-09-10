static bool
decode_num (uintmax_t *num, char const *arg, uintmax_t maxval,
	    char const *keyword)
{
  uintmax_t u;
  char *arg_lim;

  if (! (ISDIGIT (*arg)
	 && (errno = 0, u = strtoumax (arg, &arg_lim, 10), !*arg_lim)))
    {
      ERROR ((0, 0, _("Malformed extended header: invalid %s=%s"),
	      keyword, arg));
      return false;
    }

  if (! (u <= maxval && errno != ERANGE))
    {
      out_of_range_header (keyword, arg, 0, maxval);
      return false;
    }

  *num = u;
  return true;
}