static int RenRRD(char *oldName, char *newName)
{ char     first[PATHNAMESIZE], second[PATHNAMESIZE];
  Object   *root;

  strcpy(first, oldName);
  strcpy(second, newName);

  if ( !RemoveRootPath(first) || !RemoveRootPath(second) )
  { fprintf(stderr, 
	    "RenRRD: trying to rename '%s' as '%s' - this shouldn't happen!\n",
	    oldName, second);
    exit(2);
  }

  if ( (root=Locate(NULL, ROOTDIR)) == NULL)
  { fprintf(stderr, "RenRRD: failed to locate root directory '%s'\n", ROOTDIR);
    exit(2);
  }

  if ( Rename(root, first, second) != 0 )
    return 0;
  else
    return 1;
}