/* Parse SOURCE as a scope ID for ADDRESS.  Return 0 on success and -1
   on error.  */
internal_function int
__inet6_scopeid_pton (const struct in6_addr *address, const char *scope,
                      uint32_t *result)
{
  if (IN6_IS_ADDR_LINKLOCAL (address)
      || IN6_IS_ADDR_MC_LINKLOCAL (address))
    {
      uint32_t number = __if_nametoindex (scope);
      if (number != 0)
        {
          *result = number;
          return 0;
        }
    }

  if (isdigit_l (scope[0], _nl_C_locobj_ptr))
    {
      char *end;
      unsigned long long number
        = ____strtoull_l_internal (scope, &end, /*base */ 10, /* group */ 0,
                                   _nl_C_locobj_ptr);
      if (*end == '\0' && number <= UINT32_MAX)
        {
          *result = number;
          return 0;
        }
    }

  __set_errno (EINVAL);
  return -1;
}