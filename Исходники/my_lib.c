MY_DIR	*my_dir(const char *path, myf MyFlags)
{
  char          *buffer;
  MY_DIR        *result= 0;
  FILEINFO      finfo;
  DYNAMIC_ARRAY *dir_entries_storage;
  MEM_ROOT      *names_storage;
  DIR		*dirp;
  char		tmp_path[FN_REFLEN + 2], *tmp_file;
  const struct dirent *dp;

  DBUG_ENTER("my_dir");
  DBUG_PRINT("my",("path: '%s' MyFlags: %d",path,MyFlags));

  dirp = opendir(directory_file_name(tmp_path,(char *) path));
  if (dirp == NULL ||
      ! (buffer= my_malloc(key_memory_MY_DIR,
                           ALIGN_SIZE(sizeof(MY_DIR)) + 
                           ALIGN_SIZE(sizeof(DYNAMIC_ARRAY)) +
                           sizeof(MEM_ROOT), MyFlags)))
    goto error;

  dir_entries_storage= (DYNAMIC_ARRAY*)(buffer + ALIGN_SIZE(sizeof(MY_DIR)));
  names_storage= (MEM_ROOT*)(buffer + ALIGN_SIZE(sizeof(MY_DIR)) +
                             ALIGN_SIZE(sizeof(DYNAMIC_ARRAY)));

  if (my_init_dynamic_array(dir_entries_storage,
                            key_memory_MY_DIR,
                            sizeof(FILEINFO),
                            NULL,               /* init_buffer */
                            ENTRIES_START_SIZE, ENTRIES_INCREMENT))
  {
    my_free(buffer);
    goto error;
  }
  init_alloc_root(key_memory_MY_DIR, names_storage, NAMES_START_SIZE, NAMES_START_SIZE);

  /* MY_DIR structure is allocated and completly initialized at this point */
  result= (MY_DIR*)buffer;

  tmp_file=strend(tmp_path);

  for (dp= readdir(dirp) ; dp; dp= readdir(dirp))
  {
    if (!(finfo.name= strdup_root(names_storage, dp->d_name)))
      goto error;

    if (MyFlags & MY_WANT_STAT)
    {
      if (!(finfo.mystat= (MY_STAT*)alloc_root(names_storage,
                                               sizeof(MY_STAT))))
        goto error;

      memset(finfo.mystat, 0, sizeof(MY_STAT));
      (void) my_stpcpy(tmp_file,dp->d_name);
      (void) my_stat(tmp_path, finfo.mystat, MyFlags);
      if (!(finfo.mystat->st_mode & MY_S_IREAD))
        continue;
    }
    else
      finfo.mystat= NULL;

    if (insert_dynamic(dir_entries_storage, (uchar*)&finfo))
      goto error;
  }

  (void) closedir(dirp);

  result->dir_entry= (FILEINFO *)dir_entries_storage->buffer;
  result->number_off_files= dir_entries_storage->elements;

  if (!(MyFlags & MY_DONT_SORT))
    my_qsort((void *) result->dir_entry, result->number_off_files,
          sizeof(FILEINFO), (qsort_cmp) comp_names);
  DBUG_RETURN(result);

 error:
  set_my_errno(errno);
  if (dirp)
    (void) closedir(dirp);
  my_dirend(result);
  if (MyFlags & (MY_FAE | MY_WME))
  {
    char errbuf[MYSYS_STRERROR_SIZE];
    my_error(EE_DIR, MYF(0), path,
             my_errno(), my_strerror(errbuf, sizeof(errbuf), my_errno()));
  }
  DBUG_RETURN((MY_DIR *) NULL);
} /* my_dir */