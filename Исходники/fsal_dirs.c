fsal_status_t GPFSFSAL_readdir(fsal_dir_t * dir_desc,       /* IN */
                           fsal_cookie_t startposition,        /* IN */
                           fsal_attrib_mask_t get_attr_mask,    /* IN */
                           fsal_mdsize_t buffersize,    /* IN */
                           fsal_dirent_t * p_pdirent,   /* OUT */
                           fsal_cookie_t * end_position,      /* OUT */
                           fsal_count_t * p_nb_entries, /* OUT */
                           fsal_boolean_t * p_end_of_dir        /* OUT */
    )
{
  fsal_status_t st;
  fsal_count_t max_dir_entries;
  fsal_name_t entry_name;
  char buff[BUF_SIZE];
  struct linux_dirent *dp = NULL;
  int bpos = 0;
  int tmpfd = 0;
  gpfsfsal_dir_t *p_dir_descriptor = (gpfsfsal_dir_t *)dir_desc;
  gpfsfsal_cookie_t start_position;
  gpfsfsal_cookie_t *p_end_position = (gpfsfsal_cookie_t *)end_position;

  char d_type;
  struct stat buffstat;

  int rc = 0;

  memset(buff, 0, BUF_SIZE);
  memset(&entry_name, 0, sizeof(fsal_name_t));

  /*****************/
  /* sanity checks */
  /*****************/

  if(!p_dir_descriptor || !p_pdirent || !p_end_position || !p_nb_entries || !p_end_of_dir)
    Return(ERR_FSAL_FAULT, 0, INDEX_FSAL_readdir);

  max_dir_entries = (buffersize / sizeof(fsal_dirent_t));

  /***************************/
  /* seek into the directory */
  /***************************/
  start_position.data.cookie = (off_t)startposition.data;
  errno = 0;
  if(start_position.data.cookie == 0)
    {
      //rewinddir(p_dir_descriptor->p_dir);
      rc = errno;
    }
  else
    {
      //seekdir(p_dir_descriptor->p_dir, start_position.cookie);
      rc = errno;
    }

  if(rc)
    Return(posix2fsal_error(rc), rc, INDEX_FSAL_readdir);

  /************************/
  /* browse the directory */
  /************************/

  *p_nb_entries = 0;
  while(*p_nb_entries < max_dir_entries)
    {
    /***********************/
      /* read the next entry */
    /***********************/
      TakeTokenFSCall();
      rc = syscall(SYS_getdents, p_dir_descriptor->fd, buff, BUF_SIZE);
      ReleaseTokenFSCall();
      if(rc < 0)
        {
          rc = errno;
          Return(posix2fsal_error(rc), rc, INDEX_FSAL_readdir);
        }
      /* End of directory */
      if(rc == 0)
        {
          *p_end_of_dir = 1;
          break;
        }

    /***********************************/
      /* Get information about the entry */
    /***********************************/

      for(bpos = 0; bpos < rc;)
        {
          dp = (struct linux_dirent *)(buff + bpos);
          d_type = *(buff + bpos + dp->d_reclen - 1);
                                                    /** @todo not used for the moment. Waiting for information on symlink management */
          bpos += dp->d_reclen;

          /* LogFullDebug(COMPONENT_FSAL,
                          "\tino=%8ld|%8lx off=%d|%x reclen=%d|%x name=%s|%d",
                          dp->d_ino, dp->d_ino, (int)dp->d_off, (int)dp->d_off,
                          dp->d_reclen, dp->d_reclen, dp->d_name, (int)dp->d_name[0]  ) ; */

          if(!(*p_nb_entries < max_dir_entries))
            break;

          /* skip . and .. */
          if(!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
            continue;

          /* build the full path of the file into "fsalpath */
          if(FSAL_IS_ERROR
             (st =
              FSAL_str2name(dp->d_name, FSAL_MAX_NAME_LEN,
                            &(p_pdirent[*p_nb_entries].name))))
            ReturnStatus(st, INDEX_FSAL_readdir);

          d_type = DT_UNKNOWN;

          // TODO: there is a race here, because between handle fetch
          // and open at things might change.  we need to figure out if there
          // is another way to open without the pcontext

          strncpy(entry_name.name, dp->d_name, sizeof(entry_name.name));
          entry_name.len = strlen(entry_name.name);

          if(FSAL_IS_ERROR
             (st =
              fsal_internal_get_handle_at(p_dir_descriptor->fd, &entry_name,
                                          &(p_pdirent[*p_nb_entries].handle))))
            ReturnStatus(st, INDEX_FSAL_readdir);

          if(FSAL_IS_ERROR
             (st =
              fsal_internal_handle2fd_at(p_dir_descriptor->fd,
                                         &(p_pdirent[*p_nb_entries].handle), &tmpfd,
                                         O_RDONLY | O_NOFOLLOW)))
            {
              if(errno != ELOOP)        /* ( p_dir_descriptor->fd, dp->d_name) is not a symlink */
                ReturnStatus(st, INDEX_FSAL_readdir);
              else
                d_type = DT_LNK;
            }

          /* get object handle */
          TakeTokenFSCall();
          if(d_type != DT_LNK)
            {
              close(tmpfd);
            }
          else
            {
              if(fstatat(p_dir_descriptor->fd, dp->d_name, &buffstat, AT_SYMLINK_NOFOLLOW)
                 < 0)
                {
                  ReleaseTokenFSCall();
                  Return(posix2fsal_error(errno), errno, INDEX_FSAL_readdir);
                }

              p_pdirent[*p_nb_entries].attributes.asked_attributes = get_attr_mask;

              st = posix2fsal_attributes(&buffstat, &p_pdirent[*p_nb_entries].attributes);
              if(FSAL_IS_ERROR(st))
                {
                  ReleaseTokenFSCall();
                  FSAL_CLEAR_MASK(p_pdirent[*p_nb_entries].attributes.asked_attributes);
                  FSAL_SET_MASK(p_pdirent[*p_nb_entries].attributes.asked_attributes,
                                FSAL_ATTR_RDATTR_ERR);
                  ReturnStatus(st, INDEX_FSAL_getattrs);
                }

            }
          ReleaseTokenFSCall();

          if(FSAL_IS_ERROR(st))
            ReturnStatus(st, INDEX_FSAL_readdir);

    /************************
     * Fills the attributes *
     ************************/
          if(d_type != DT_LNK)
            {
              p_pdirent[*p_nb_entries].attributes.asked_attributes = get_attr_mask;

              st = GPFSFSAL_getattrs(&(p_pdirent[*p_nb_entries].handle),
				     (fsal_op_context_t *)&p_dir_descriptor->context,
                                 &p_pdirent[*p_nb_entries].attributes);
              if(FSAL_IS_ERROR(st))
                {
                  FSAL_CLEAR_MASK(p_pdirent[*p_nb_entries].attributes.asked_attributes);
                  FSAL_SET_MASK(p_pdirent[*p_nb_entries].attributes.asked_attributes,
                                FSAL_ATTR_RDATTR_ERR);
                }
            }
          ((gpfsfsal_cookie_t *)(&p_pdirent[*p_nb_entries].cookie))->data.cookie = dp->d_off;
          p_pdirent[*p_nb_entries].nextentry = NULL;
          if(*p_nb_entries)
            p_pdirent[*p_nb_entries - 1].nextentry = &(p_pdirent[*p_nb_entries]);

	  memcpy((char *)p_end_position, (char *)&p_pdirent[*p_nb_entries].cookie,
                 sizeof(gpfsfsal_cookie_t));
          (*p_nb_entries)++;

        }                       /* for */
    }                           /* While */

  Return(ERR_FSAL_NO_ERROR, 0, INDEX_FSAL_readdir);

}