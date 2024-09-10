static int
quoted_file_exists (const char* pz_src_path,
                    const char* pz_file_path, 
                    const char* pz_file)
{
  char z[ MAXPATHLEN ];
  char* pz;
  sprintf (z, "%s/%s/", pz_src_path, pz_file_path);
  pz = z + strlen ( z );

  for (;;) {
    char ch = *pz_file++;
    if (! ISGRAPH( ch ))
      return 0;
    if (ch == '"')
      break;
    *pz++ = ch;
  }
  *pz = '\0';
  {
    struct stat s;
    if (stat (z, &s) != 0)
      return 0;
    return S_ISREG( s.st_mode );
  }
}