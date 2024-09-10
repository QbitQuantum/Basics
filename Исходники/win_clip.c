PUBLIC LONGINT
GetScrapX (LONGINT type, char **h)
{
  UINT format;
  LONGINT retval;

  retval = -1;
  switch (type)
    {
    case T ('T', 'E', 'X', 'T'):
      format = CF_TEXT;
      break;
    default:
      format = ROMlib_executor_format (type);
      if (type == T('P','I','C','T'))
	{
	  typeof (format) newval;
	  UINT formats[2] = { format, CF_DIB };
	  
	  newval = GetPriorityClipboardFormat (formats, NELEM (formats));
	  if (newval != 0 && newval != (UINT) -1)
	    format = newval;
 	  }
      break;
    }
  if (IsClipboardFormatAvailable (format) && OpenClipboard (cygwin_sdlwindow ()))
    {
      HANDLE data;

      data = GetClipboardData (format);
      if (data)
	{
	  LPVOID lp;

	  lp = GlobalLock (data);
	  switch (type)
	    {
	    case T ('T', 'E', 'X', 'T'):
	      {
		int len;

		len = strlen (lp);
		retval = get_scrap_helper (h, lp, len, TRUE);
	      }
	    break;
	    default:
	      {
#if defined (SDL)
		if (format == CF_DIB)
		  retval = get_scrap_helper_dib (h, lp);
		else
#endif
		  {
		    int32 len;
		    len = *(int32 *)lp;

		    retval = get_scrap_helper (h, lp+sizeof(int32),
					       len, FALSE);
		  }
	      }
	      break;
	    }
	  GlobalUnlock (data);
	  CloseClipboard ();
	}
    }
  return retval;
}