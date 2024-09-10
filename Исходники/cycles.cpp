int processing_dir(TCHAR *fn)
{
  dir_table *new_dir, *temp;
  TCHAR *d_name = (TCHAR *)malloc(sizeof(TCHAR) * PATH_MAX);

#ifdef _WIN32
  _wfullpath(d_name,fn,PATH_MAX);
#else
  realpath(fn,d_name);
#endif

  if (my_table == NULL)
  {
    my_table = (dir_table*)malloc(sizeof(dir_table));
    my_table->name = _tcsdup(d_name);
    my_table->next = NULL;

    free(d_name);
    return TRUE;
  }
 
  temp = my_table;

  while (temp->next != NULL)
  {
    /* We should never be adding a directory that is already here */
    if (!_tcsncmp(temp->name,d_name,PATH_MAX))
    {
      internal_error("%s: Attempt to add existing %s in processing_dir",
		     __progname, d_name);
      // Does not execute
      free(d_name);
      return FALSE;
    }
    temp = temp->next;       
  }

  new_dir = (dir_table*)malloc(sizeof(dir_table));
  new_dir->name = _tcsdup(d_name);
  new_dir->next = NULL;  
  temp->next = new_dir;

  free(d_name);
  return TRUE;
}