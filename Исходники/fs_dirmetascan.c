/**
 * Start a directory scanner thread.
 *
 * @param filename name of the directory to scan
 * @param disable_extractor GNUNET_YES to not to run libextractor on files (only build a tree)
 * @param ex if not NULL, must be a list of extra plugins for extractor
 * @param cb the callback to call when there are scanning progress messages
 * @param cb_cls closure for 'cb'
 * @return directory scanner object to be used for controlling the scanner
 */
struct GNUNET_FS_DirScanner *
GNUNET_FS_directory_scan_start (const char *filename,
				int disable_extractor, const char *ex,
				GNUNET_FS_DirScannerProgressCallback cb, 
				void *cb_cls)
{
  struct stat sbuf;
  char *filename_expanded;
  struct GNUNET_FS_DirScanner *ds;

  if (0 != STAT (filename, &sbuf))
    return NULL;
  filename_expanded = GNUNET_STRINGS_filename_expand (filename);
  if (NULL == filename_expanded)
    return NULL;
  GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
	      "Starting to scan directory `%s'\n",
	      filename_expanded);
  ds = GNUNET_malloc (sizeof (struct GNUNET_FS_DirScanner));
  ds->progress_callback = cb;
  ds->progress_callback_cls = cb_cls;
  ds->filename_expanded = filename_expanded;
  if (disable_extractor)  
    ds->ex_arg = GNUNET_strdup ("-");
  else 
    ds->ex_arg = (NULL != ex) ? GNUNET_strdup (ex) : NULL;
  ds->args[0] = "gnunet-helper-fs-publish";
  ds->args[1] = ds->filename_expanded;
  ds->args[2] = ds->ex_arg;
  ds->args[3] = NULL;
  ds->helper = GNUNET_HELPER_start (GNUNET_NO,
				    "gnunet-helper-fs-publish",
				    ds->args,
				    &process_helper_msgs,
				    &helper_died_cb, ds);
  if (NULL == ds->helper)
    {
    GNUNET_free (filename_expanded);
    GNUNET_free (ds);
    return NULL;
  }
  return ds;
}