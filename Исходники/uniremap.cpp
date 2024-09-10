//--------------------------------------------------------------------------
char *uniremap_init(char *table)
{
  const char *cur = setlocale(LC_CTYPE, NULL);
  if(!cur) cur = "C"; // PARANOYA
  cur = qstrdup(cur);

#ifdef __UNIX__
  table = create_map("", &lm[0], table);
  lm[1] = lm[0];
#else
  {
    char  s[16];
    int oemcp, acp = get_codepages(&oemcp);
    if ( acp == CP_ACP )      acp   = GetACP();
    if ( oemcp == CP_OEMCP )  oemcp = GetOEMCP();
    qsnprintf(s, sizeof(s), ".%u", oemcp);
    table = create_map(s, &lm[0], table);
    qsnprintf(s, sizeof(s), ".%u", acp);
    create_map(s, &lm[1], NULL);
  }
#endif
  setlocale(LC_CTYPE, cur); // restore default locale
  qfree((void*)cur);
  return(table);
}