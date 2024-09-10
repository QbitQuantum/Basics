long fpathconf(int fid, int name)
{
  long rv;

#if OS_PARM_CHECK
  /*-------------------------------------------------------------------*/
  /* Ensure file descriptor is valid.                                  */
  /*-------------------------------------------------------------------*/
  if (fid < 0 || fid >= FOPEN_MAX)
  {
    set_errno(EBADF);
    return -1;
  }
#endif

  /*-------------------------------------------------------------------*/
  /* Return error if file is closed.                                   */
  /*-------------------------------------------------------------------*/
  if (Files[fid].ioctl == NULL)
  {
    set_errno(EBADF);
    return -1;
  }

  /*-------------------------------------------------------------------*/
  /* Based on the name variable, get the right value.                  */
  /*-------------------------------------------------------------------*/
  switch (name)
  {
    /*-----------------------------------------------------------------*/
    /* _PC_NAME_MAX and _PC_PATH_MAX have the same value.              */
    /*-----------------------------------------------------------------*/
    case _PC_NAME_MAX:
    case _PC_PATH_MAX:
    {
      rv = PATH_MAX;
      break;
    }

    case _PC_NO_TRUNC:
    {
      rv = _PATH_NO_TRUNC;
      break;
    }

    case _PC_LINK_MAX:
    {
      /*---------------------------------------------------------------*/
      /* The link counter is stored in a "ui8".                        */
      /*---------------------------------------------------------------*/
      rv = 255;
      break;
    }

    /*-----------------------------------------------------------------*/
    /* All other variables have no limit, so return -1 for them.       */
    /*-----------------------------------------------------------------*/
    default:
    {
      rv = -1;
      break;
    }
  }
  return rv;
}