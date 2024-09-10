int expand_names( int argc, LPWSTR argv[] )
{
  HANDLE fh;
  WIN32_FIND_DATA fd;
  LPWSTR path, name;
  int	 first;
  int	 keep;
  int	 i;

  for (i = 0; i < globbed; ++i)
    free( glob[i] );

  globbed = 0;
  for (i = 0; i < argc; ++i)
  {
    if (*argv[i] == '\0')
      continue;

    wcscpy( glob_name, argv[i] );
    keep = (all && !recurse &&
	    glob_name == glob_path && wcspbrk( glob_name, L"*?" ) == NULL);
    fh = FindFirstFile( glob_path, &fd );
    if (fh == INVALID_HANDLE_VALUE)
    {
      if (keep)
	add_name();
      continue;
    }

    for (path = name = glob_name; *path; ++path)
      if (*path == '\\' || *path == '/')
	name = path + 1;

    first = globbed;
    do
    {
      if (fd.dwFileAttributes & (hidden | FILE_ATTRIBUTE_DIRECTORY))
      {
	if (keep)
	  add_name();
	continue;
      }
      wcscpy( name, fd.cFileName );
      add_name();
    } while (FindNextFile( fh, &fd ));
    FindClose( fh );

    qsort( glob + first, globbed - first, sizeof(LPWSTR), glob_sort );
  }

  return (globbed != 0);
}