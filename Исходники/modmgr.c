unsigned long ModLoadExeModule(char *          pszName,
                               unsigned long   cbName,
                               char const *    pszModname,
                               unsigned long * phmod)
{
  int rc = 0;
  
  rc = OpenModule(pszName, cbName, pszModname, 1, phmod);

  if (rc) 
    return rc;
  
  rc = LoadModule(pszName, cbName, phmod);
  return rc;