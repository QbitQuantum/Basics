int CheckPerm(FCOM_T *comm_ptr, int permissions)
{
  uid_t uid;
  gid_t gid;

  /*-------------------------------------------------------------------*/
  /* Get group and user ID for current process.                        */
  /*-------------------------------------------------------------------*/
  FsGetId(&uid, &gid);

  /*-------------------------------------------------------------------*/
  /* Check if we need to look at read permissions.                     */
  /*-------------------------------------------------------------------*/
  if (permissions & F_READ)
  {
    /*-----------------------------------------------------------------*/
    /* If other has no read permission, check group.                   */
    /*-----------------------------------------------------------------*/
    if ((comm_ptr->mode & S_IROTH) == FALSE)
    {
      /*---------------------------------------------------------------*/
      /* If not in group or group has no read permission, check owner. */
      /*---------------------------------------------------------------*/
      if ((gid != comm_ptr->group_id) || !(comm_ptr->mode & S_IRGRP))
      {
        /*-------------------------------------------------------------*/
        /* If not user or user has no read permissions, return error.  */
        /*-------------------------------------------------------------*/
        if ((uid != comm_ptr->user_id) || !(comm_ptr->mode & S_IRUSR))
        {
          set_errno(EACCES);
          return -1;
        }
      }
    }
  }

  /*-------------------------------------------------------------------*/
  /* Check if we need to look at write permissions.                    */
  /*-------------------------------------------------------------------*/
  if (permissions & F_WRITE)
  {
    /*-----------------------------------------------------------------*/
    /* If other has no write permission, check group.                  */
    /*-----------------------------------------------------------------*/
    if ((comm_ptr->mode & S_IWOTH) == 0)
    {
      /*---------------------------------------------------------------*/
      /* If not in group or group has no write permission, check owner.*/
      /*---------------------------------------------------------------*/
      if ((gid != comm_ptr->group_id) || !(comm_ptr->mode & S_IWGRP))
      {
        /*-------------------------------------------------------------*/
        /* If not user or user has no write permissions, return error. */
        /*-------------------------------------------------------------*/
        if ((uid != comm_ptr->user_id) || !(comm_ptr->mode & S_IWUSR))
        {
          set_errno(EACCES);
          return -1;
        }
      }
    }
  }

  /*-------------------------------------------------------------------*/
  /* Check if we need to look at execute permissions.                  */
  /*-------------------------------------------------------------------*/
  if (permissions & F_EXECUTE)
  {
    /*-----------------------------------------------------------------*/
    /* If other has no execute permission, check group.                */
    /*-----------------------------------------------------------------*/
    if ((comm_ptr->mode & S_IXOTH) == 0)
    {
      /*---------------------------------------------------------------*/
      /* If not in group or group can't execute, check owner.          */
      /*---------------------------------------------------------------*/
      if ((gid != comm_ptr->group_id) || !(comm_ptr->mode & S_IXGRP))
      {
        /*-------------------------------------------------------------*/
        /* If not user or user can't execute, return error.            */
        /*-------------------------------------------------------------*/
        if ((uid != comm_ptr->user_id) || !(comm_ptr->mode & S_IXUSR))
        {
          set_errno(EACCES);
          return -1;
        }
      }
    }
  }
  return 0;
}