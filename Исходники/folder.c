/* A folder could be remote (IMAP), or local(a spool directory) like $HOME/Mail
   etc ..  We maintain a list of known folders to avoid creating multiple
   folders for the same URL.  So, when mu_folder_create is called we check if
   we already have a folder for that URL and return it, otherwise we create a
   new one.  Downsides: the scheme to detect the same URL is very weak, and
   there could be cases where you'll want a different folder for the same URL,
   there is not easy way to do this.  */
int
mu_folder_create_from_record (mu_folder_t *pfolder, mu_url_t url,
			      mu_record_t record)
{
  if (!pfolder)
    return MU_ERR_OUT_PTR_NULL;

  if (record || 
      /* Look in the registrar list(iterator), for a possible concrete mailbox
	 implementation that could match the URL.  */
      mu_registrar_lookup_url (url, MU_FOLDER_ATTRIBUTE_DIRECTORY, &record,
			       NULL) == 0)
    {
      int (*f_init) (mu_folder_t) = NULL;
      
      mu_record_get_folder (record, &f_init);
      if (f_init)
        {
	  int status, mask;
	  mu_folder_t folder;
	  int (*u_init) (mu_url_t) = NULL;

	  status = mu_record_check_url (record, url, &mask);
	  if (status)
	    /* FIXME: mask would provide more info */
	    return status;
	  
	  mu_record_get_url (record, &u_init);
	  if (u_init)
	    {
	      status = u_init (url);
	      if (status)
		return status;
	    }
	  
	  mu_monitor_wrlock (&folder_lock);

	  /* Check if we already have the same URL folder.  */
	  if (is_known_folder (url, &folder))
	    {
	      folder->ref++;
	      *pfolder = folder;
	      mu_url_destroy (&url); /* FIXME: Hmm */
	      mu_monitor_unlock (&folder_lock);
	      return  0;
	    }
	  else
	    mu_monitor_unlock (&folder_lock);
	  
	  /* Create a new folder.  */

	  /* Allocate memory for the folder.  */
	  folder = calloc (1, sizeof (*folder));
	  if (folder != NULL)
	    {
	      folder->url = url;
	      /* Initialize the internal foilder lock, now so the
		 concrete folder could use it.  */
	      status = mu_monitor_create (&folder->monitor, 0, folder);
	      if (status == 0)
		{
		  /* Create the concrete folder type.  */
		  status = f_init (folder);
		  if (status == 0)
		    {
		      if (!folder->_match)
			folder->_match = mu_folder_imap_match;
		      *pfolder = folder;
		      folder->ref++;
		      /* Put on the internal list of known folders.  */
		      if (known_folder_list == NULL)
			mu_list_create (&known_folder_list);
		      mu_list_append (known_folder_list, folder);
		    }
		}
	      /* Something went wrong, destroy the object. */
	      if (status)
		{
		  if (folder->monitor)
		    mu_monitor_destroy (&folder->monitor, folder);
		  free (folder);
		}
	    }
	  return status;
	}
    }

  return MU_ERR_NOENT;
}