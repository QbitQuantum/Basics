int job_qs_upgrade(

  job *pj,     /* I */
  int fds,    /* I */
  char *path, /* I */
  int version) /* I */

  {
  char  namebuf[MAXPATHLEN];
  char  log_buf[LOCAL_LOG_BUF_SIZE];
  FILE *source; 
  FILE *backup;
  int   c;

  /* reset the file descriptor */
  if (lseek(fds, 0, SEEK_SET) != 0)
    {
    sprintf(log_buf, "unable to reset fds\n");
    log_err(-1, __func__, log_buf);

    return (-1);
    }

  snprintf(namebuf, sizeof(namebuf), "%s", path);
  namebuf[strlen(path) - strlen(JOB_FILE_SUFFIX)] = '\0'; /* cut off the .JB by replacing the '.' with a NULL */
  
  if (strlen(namebuf) + strlen(JOB_FILE_BACKUP) > MAXPATHLEN - 1)
    {
    sprintf(log_buf, "ERROR: path too long for buffer, unable to backup!\n");
    log_err(-1, __func__, log_buf);
    return (-1);
    }

  strcat(namebuf, JOB_FILE_BACKUP);

  source = fdopen(dup(fds), "r");

  if ((backup = fopen(namebuf, "wb")) == NULL)
    {
    sprintf(log_buf, "Cannot open backup file.\n");
    log_err(errno, __func__, log_buf);
    return -1;
    }

  while ((c = fgetc(source)) != EOF)
    {
    fputc(c, backup);
    }

  fclose(backup);
  fclose(source);

  sprintf(log_buf, "backed up to %s\n", namebuf);
  log_err(-1, __func__, log_buf); 

  /* reset the file descriptor */
  if (lseek(fds, 0, SEEK_SET) != 0)
    {
    sprintf(log_buf, "unable to reset fds\n");
    log_err(-1, __func__, log_buf);

    return (-1);
    }

  if (version > PBS_QS_VERSION)
    {
    sprintf(log_buf, "job struct appears to be from an unknown "
            "version of TORQUE and can not be converted");
    log_err(-1, "job_qs_upgrade", log_buf);
    return (-1);
    }
  else if (version - PBS_QS_VERSION_BASE == 1)
    {
    return upgrade_v1(pj, fds);
    }
  /* old style version numbers... */
  else if (version == 0x00020300)
    {
    return  upgrade_2_3_X(pj, fds);
    }
  else if (version == 0x00020200)
    {
    return  upgrade_2_2_X(pj, fds);
    }
  /* predates versioning of ji_qs. assume 2.1.x format */
  else
    {
    return upgrade_2_1_X(pj, fds);
    }


  }