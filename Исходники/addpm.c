int
main (int argc, char *argv[])
{
  char start_folder[MAX_PATH + 1];
  int shortcuts_created = 0;
  int com_available = 1;
  char modname[MAX_PATH];
  const char *prog_name;
  const char *emacs_path;
  char *p;
  int quiet = 0;
  HRESULT result;
  IShellLinkA *shortcut;

  /* If no args specified, use our location to set emacs_path.  */

  if (argc > 1
      && (argv[1][0] == '/' || argv[1][0] == '-')
      && argv[1][1] == 'q')
    {
      quiet = 1;
      --argc;
      ++argv;
    }

  if (argc > 1)
    emacs_path = argv[1];
  else
    {
      if (!GetModuleFileName (NULL, modname, MAX_PATH) ||
	  (p = strrchr (modname, '\\')) == NULL)
	{
	  fprintf (stderr, "fatal error");
	  exit (1);
	}
      *p = 0;

      /* Set emacs_path to emacs_dir if we are in "%emacs_dir%\bin".  */
      if ((p = strrchr (modname, '\\')) && stricmp (p, "\\bin") == 0)
	{
	  *p = 0;
	  emacs_path = modname;
	}
      else
	{
	  fprintf (stderr, "usage: addpm emacs_path\n");
	  exit (1);
	}

      /* Tell user what we are going to do.  */
      if (!quiet)
	{
	  int result;

	  char msg[ MAX_PATH ];
	  sprintf (msg, "Install Emacs at %s?\n", emacs_path);
	  result = MessageBox (NULL, msg, "Install Emacs",
			       MB_OKCANCEL | MB_ICONQUESTION);
	  if (result != IDOK)
	    {
	      fprintf (stderr, "Install cancelled\n");
	      exit (1);
	    }
	}
    }

  add_registry (emacs_path);
  prog_name =  "runemacs.exe";

  /* Try to install globally.  */

  if (!SUCCEEDED (CoInitialize (NULL))
      || !SUCCEEDED (CoCreateInstance (&CLSID_ShellLink, NULL,
					CLSCTX_INPROC_SERVER, &IID_IShellLinkA,
					(void **) &shortcut)))
    {
      com_available = 0;
    }

  if (com_available
      && SHGetSpecialFolderPath (NULL, start_folder, CSIDL_COMMON_PROGRAMS, 0))
    {
      if (strlen (start_folder) < (MAX_PATH - 20))
	{
	  strcat (start_folder, "\\Gnu Emacs");
	  if (CreateDirectory (start_folder, NULL)
	      || GetLastError () == ERROR_ALREADY_EXISTS)
	    {
	      char full_emacs_path[MAX_PATH + 1];
	      IPersistFile *lnk;
	      strcat (start_folder, "\\Emacs.lnk");
	      sprintf (full_emacs_path, "%s\\bin\\%s", emacs_path, prog_name);
	      IShellLinkA_SetPath (shortcut, full_emacs_path);
	      IShellLinkA_SetDescription (shortcut, "GNU Emacs");
	      result = IShellLinkA_QueryInterface (shortcut, &IID_IPersistFile,
						   (void **) &lnk);
	      if (SUCCEEDED (result))
		{
		  wchar_t unicode_path[MAX_PATH];
		  MultiByteToWideChar (CP_ACP, 0, start_folder, -1,
				       unicode_path, MAX_PATH);
		  if (SUCCEEDED (IPersistFile_Save (lnk, unicode_path, TRUE)))
		    shortcuts_created = 1;
		  IPersistFile_Release (lnk);
		}
	    }
	}
    }

  if (!shortcuts_created && com_available
      && SHGetSpecialFolderPath (NULL, start_folder, CSIDL_PROGRAMS, 0))
    {
      /* Ensure there is enough room for "...\GNU Emacs\Emacs.lnk".  */
      if (strlen (start_folder) < (MAX_PATH - 20))
	{
	  strcat (start_folder, "\\Gnu Emacs");
	  if (CreateDirectory (start_folder, NULL)
	      || GetLastError () == ERROR_ALREADY_EXISTS)
	    {
	      char full_emacs_path[MAX_PATH + 1];
	      IPersistFile *lnk;
	      strcat (start_folder, "\\Emacs.lnk");
	      sprintf (full_emacs_path, "%s\\bin\\%s", emacs_path, prog_name);
	      IShellLinkA_SetPath (shortcut, full_emacs_path);
	      IShellLinkA_SetDescription (shortcut, "GNU Emacs");
	      result = IShellLinkA_QueryInterface (shortcut, &IID_IPersistFile,
						   (void **) &lnk);
	      if (SUCCEEDED (result))
		{
		  wchar_t unicode_path[MAX_PATH];
		  MultiByteToWideChar (CP_ACP, 0, start_folder, -1,
				       unicode_path, MAX_PATH);
		  if (SUCCEEDED (IPersistFile_Save (lnk, unicode_path, TRUE)))
		    shortcuts_created = 1;
		  IPersistFile_Release (lnk);

		}
	    }
	}
    }

  if (com_available)
    IShellLinkA_Release (shortcut);

  /* Need to call uninitialize, even if ComInitialize failed.  */
  CoUninitialize ();

  /* Fallback on old DDE method if the above failed.  */
  if (!shortcuts_created)
    {
      DWORD dde = 0;
      HCONV conversation;
      HSZ progman;
      char add_item[MAX_PATH*2 + 100];

      DdeInitialize (&dde, (PFNCALLBACK) DdeCallback, APPCMD_CLIENTONLY, 0);
      progman = DdeCreateStringHandle (dde, "PROGMAN", CP_WINANSI);
      conversation = DdeConnect (dde, progman, progman, NULL);
      if (conversation)
	{
	  DdeCommand ("[CreateGroup (\"Gnu Emacs\")]");
	  DdeCommand ("[ReplaceItem (Emacs)]");
	  sprintf (add_item, "[AddItem (\"%s\\bin\\%s\", Emacs)]",
		   emacs_path, prog_name);
	  DdeCommand (add_item);

	  DdeDisconnect (conversation);
	}

      DdeFreeStringHandle (dde, progman);
      DdeUninitialize (dde);
   }

  return 0;
}