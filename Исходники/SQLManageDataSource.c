BOOL
ManageDataSources (HWND hwndParent)
{
  void *handle;
  pAdminBoxFunc pAdminBox;
  BOOL retcode = FALSE;
#if defined (__APPLE__) && !(defined (NO_FRAMEWORKS) || defined (_LP64))
  CFStringRef libname = NULL;
  CFBundleRef bundle;
  CFURLRef liburl;
  char name[1024] = { 0 };
#endif

  /* Load the Admin dialbox function */
#if defined (__APPLE__) && !(defined (NO_FRAMEWORKS) || defined (_LP64))
  bundle = CFBundleGetBundleWithIdentifier (CFSTR ("org.iodbc.inst"));
  if (bundle)
    {
      /* Search for the iODBCadm library */
      liburl =
	  CFBundleCopyResourceURL (bundle, CFSTR ("iODBCadm.bundle"),
	  NULL, NULL);
      if (liburl && (libname =
	      CFURLCopyFileSystemPath (liburl, kCFURLPOSIXPathStyle)))
	{
	  CFStringGetCString (libname, name, sizeof (name),
	      kCFStringEncodingASCII);
	  STRCAT (name, "/Contents/MacOS/iODBCadm");
	  CALL_ADMIN_DIALBOX (name);
	}
      if (liburl)
	CFRelease (liburl);
      if (libname)
	CFRelease (libname);
    }

#else
  CALL_ADMIN_DIALBOX ("libiodbcadm.so.2");
#endif

  return retcode;
}