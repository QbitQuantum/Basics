static int
str2signum (char const *signame)
{
  if (ISDIGIT (*signame))
    {
      char *endp;
      long int n = strtol (signame, &endp, 10);
      if (! *endp && n <= SIGNUM_BOUND)
        return n;
    }
  else
    {
      unsigned int i;
      for (i = 0; i < NUMNAME_ENTRIES; i++)
        if (strcmp (numname_table[i].name, signame) == 0)
          return numname_table[i].num;

      {
        char *endp;
        int rtmin = SIGRTMIN;
        int rtmax = SIGRTMAX;

        if (0 < rtmin && strncmp (signame, "RTMIN", 5) == 0)
          {
            long int n = strtol (signame + 5, &endp, 10);
            if (! *endp && 0 <= n && n <= rtmax - rtmin)
              return rtmin + n;
          }
        else if (0 < rtmax && strncmp (signame, "RTMAX", 5) == 0)
          {
            long int n = strtol (signame + 5, &endp, 10);
            if (! *endp && rtmin - rtmax <= n && n <= 0)
              return rtmax + n;
          }
      }
    }

  return -1;
}