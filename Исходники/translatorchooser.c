void
addtranslators_to_list (GtkWidget *widget, GtkWidget *dlg)
{
  char *curr, *buffer = (char *) malloc (sizeof (char) * 65536), *szDriver;
  char driver[1024], _date[1024], _size[1024];
  char *data[4];
  int len, i;
  BOOL careabout;
  UWORD confMode = ODBC_USER_DSN;
  struct stat _stat;

  if (!buffer || !GTK_IS_CLIST (widget))
    return;
  gtk_clist_clear (GTK_CLIST (widget));

  /* Get the current config mode */
  while (confMode != ODBC_SYSTEM_DSN + 1)
    {
      /* Get the list of drivers in the user context */
      SQLSetConfigMode (confMode);
#ifdef WIN32
      len =
	  SQLGetPrivateProfileString ("ODBC 32 bit Translators",
	  NULL, "", buffer, 65535, "odbcinst.ini");
#else
      len =
	  SQLGetPrivateProfileString ("ODBC Translators",
	  NULL, "", buffer, 65535, "odbcinst.ini");
#endif
      if (len)
	goto process;

      goto end;

    process:
      for (curr = buffer; *curr; curr += (STRLEN (curr) + 1))
	{
	  /* Shadowing system odbcinst.ini */
	  for (i = 0, careabout = TRUE; i < GTK_CLIST (widget)->rows; i++)
	    {
	      gtk_clist_get_text (GTK_CLIST (widget), i, 0, &szDriver);
	      if (!strcmp (szDriver, curr))
		{
		  careabout = FALSE;
		  break;
		}
	    }

	  if (!careabout)
	    continue;

	  SQLSetConfigMode (confMode);
#ifdef WIN32
	  SQLGetPrivateProfileString ("ODBC 32 bit Translators",
	      curr, "", driver, sizeof (driver), "odbcinst.ini");
#else
	  SQLGetPrivateProfileString ("ODBC Translators",
	      curr, "", driver, sizeof (driver), "odbcinst.ini");
#endif

	  /* Check if the driver is installed */
	  if (strcasecmp (driver, "Installed"))
	    goto end;

	  /* Get the driver library name */
	  SQLSetConfigMode (confMode);
	  if (!SQLGetPrivateProfileString (curr,
		  "Translator", "", driver, sizeof (driver), "odbcinst.ini"))
	    {
	      SQLSetConfigMode (confMode);
	      SQLGetPrivateProfileString ("Default",
		  "Translator", "", driver, sizeof (driver), "odbcinst.ini");
	    }

	  if (STRLEN (curr) && STRLEN (driver))
	    {
	      data[0] = curr;
	      data[1] = driver;

	      /* Get some information about the driver */
	      if (!stat (driver, &_stat))
		{
		  sprintf (_size, "%lu Kb",
		      (unsigned long) _stat.st_size / 1024L);
		  sprintf (_date, "%s", ctime (&_stat.st_mtime));
		  data[2] = _date;
		  data[3] = _size;
		  gtk_clist_append (GTK_CLIST (widget), data);
		}
	    }
	}

    end:
      if (confMode == ODBC_USER_DSN)
	confMode = ODBC_SYSTEM_DSN;
      else
	confMode = ODBC_SYSTEM_DSN + 1;
    }

  if (GTK_CLIST (widget)->rows > 0)
    {
      gtk_clist_columns_autosize (GTK_CLIST (widget));
      gtk_clist_sort (GTK_CLIST (widget));
    }

  /* Make the clean up */
  free (buffer);
}