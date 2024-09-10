int is_gpustat_get(

  struct pbsnode  *np,      /* I (modified) */
  char           **str_ptr) /* I (modified) */

  {
  int            rc;
  pbs_attribute  temp;
  char          *gpuid;
  char          *str = *str_ptr;
  char           log_buf[LOCAL_LOG_BUF_SIZE];
  int            gpuidx = -1;
  char           gpuinfo[2048];
  int            need_delimiter;
  int            reportedgpucnt = 0;
  int            startgpucnt = 0;
  int            drv_ver;

  if (LOGLEVEL >= 7)
    {
    sprintf(log_buf, "received gpu status from node %s",
      (np != NULL) ? np->nd_name : "NULL");

    log_record(PBSEVENT_SCHED, PBS_EVENTCLASS_REQUEST, __func__, log_buf);
    }

  /* save current gpu count for node */
  startgpucnt = np->nd_ngpus;

  /*
   *  Before filling the "temp" pbs_attribute, initialize it.
   *  The second and third parameter to decode_arst are never
   *  used, so just leave them empty. (GBS)
   */

  memset(&temp, 0, sizeof(temp));
  memset(gpuinfo, 0, 2048);

  rc = DIS_SUCCESS;

  if (decode_arst(&temp, NULL, NULL, NULL, 0))
    {
    DBPRT(("is_gpustat_get:  cannot initialize attribute\n"));

    return(DIS_NOCOMMIT);
    }

  str += strlen(str) + 1;

  for (; str != NULL && *str; str += strlen(str) + 1)
    {
    /* add the info to the "temp" attribute */

    /* get timestamp */
    if (!strncmp(str, "timestamp=", 10))
      {
      if (decode_arst(&temp, NULL, NULL, str, 0))
        {
        DBPRT(("is_gpustat_get: cannot add attributes\n"));

        free_arst(&temp);
        *str_ptr = move_past_gpu_status(str);

        return(DIS_NOCOMMIT);
        }
      continue;
      }

    /* get driver version, if there is one */
    if (!strncmp(str, "driver_ver=", 11))
      {
      if (decode_arst(&temp, NULL, NULL, str, 0))
        {
        DBPRT(("is_gpustat_get: cannot add attributes\n"));

        free_arst(&temp);
        *str_ptr = move_past_gpu_status(str);

        return(DIS_NOCOMMIT);
        }
      drv_ver = atoi(str + 11);
      continue;
      }
    else if (!strcmp(str, END_GPU_STATUS))
      {
      break;
      }

    /* gpuid must come before the rest or we will be in trouble */

    if (!strncmp(str, "gpuid=", 6))
      {
      if (strlen(gpuinfo) > 0)
        {
        if (decode_arst(&temp, NULL, NULL, gpuinfo, 0))
          {
          DBPRT(("is_gpustat_get: cannot add attributes\n"));

          free_arst(&temp);
          *str_ptr = move_past_gpu_status(str);

          return(DIS_NOCOMMIT);
          }
        memset(gpuinfo, 0, 2048);
        }

      gpuid = &str[6];

      /*
       * Get this gpus index, if it does not yet exist then find an empty entry.
       * We need to allow for the gpu status results being returned in
       * different orders since the nvidia order may change upon mom's reboot
       */

      gpuidx = gpu_entry_by_id(np, gpuid, TRUE);
      if (gpuidx == -1)
        {
        /*
         * Failure - we could not get / create a nd_gpusn entry for this gpu,
         * log an error message.
         */

        if (LOGLEVEL >= 3)
          {
          sprintf(log_buf,
            "Failed to get/create entry for gpu %s on node %s\n",
            gpuid,
            np->nd_name);

          log_ext(-1, __func__, log_buf, LOG_DEBUG);
          }

        free_arst(&temp);
        *str_ptr = move_past_gpu_status(str);

        return(DIS_SUCCESS);
        }

      sprintf(gpuinfo, "gpu[%d]=gpu_id=%s;", gpuidx, gpuid);
      need_delimiter = FALSE;
      reportedgpucnt++;
      np->nd_gpusn[gpuidx].driver_ver = drv_ver;

      /* mark that this gpu node is not virtual */
      np->nd_gpus_real = TRUE;
      
      /*
       * if we have not filled in the gpu_id returned by the mom node
       * then fill it in
       */
      if ((gpuidx >= 0) && (np->nd_gpusn[gpuidx].gpuid == NULL))
        {
        np->nd_gpusn[gpuidx].gpuid = strdup(gpuid);
        }      

      }
    else
      {
      if (need_delimiter)
        {
        strcat(gpuinfo, ";");
        }
      strcat(gpuinfo, str);
      need_delimiter = TRUE;
      }

    /* check current gpu mode and determine gpu state */
    
    if (!memcmp(str, "gpu_mode=", 9))
      {
      if ((!memcmp(str + 9, "Normal", 6)) || (!memcmp(str + 9, "Default", 7)))
        {
        np->nd_gpusn[gpuidx].mode = gpu_normal;
        if (gpu_has_job(np, gpuidx))
          {
          np->nd_gpusn[gpuidx].state = gpu_shared;
          }
        else
          {
          np->nd_gpusn[gpuidx].inuse = 0;
          np->nd_gpusn[gpuidx].state = gpu_unallocated;
          }
        }
      else if ((!memcmp(str + 9, "Exclusive", 9)) ||
              (!memcmp(str + 9, "Exclusive_Thread", 16)))
        {
        np->nd_gpusn[gpuidx].mode = gpu_exclusive_thread;
        if (gpu_has_job(np, gpuidx))
          {
          np->nd_gpusn[gpuidx].state = gpu_exclusive;
          }
        else
          {
          np->nd_gpusn[gpuidx].inuse = 0;
          np->nd_gpusn[gpuidx].state = gpu_unallocated;
          }
        }
      else if (!memcmp(str + 9, "Exclusive_Process", 17))
        {
        np->nd_gpusn[gpuidx].mode = gpu_exclusive_process;
        if (gpu_has_job(np, gpuidx))
          {
          np->nd_gpusn[gpuidx].state = gpu_exclusive;
          }
        else
          {
          np->nd_gpusn[gpuidx].inuse = 0;
          np->nd_gpusn[gpuidx].state = gpu_unallocated;
          }
        }
      else if (!memcmp(str + 9, "Prohibited", 10))
        {
        np->nd_gpusn[gpuidx].mode = gpu_prohibited;
        np->nd_gpusn[gpuidx].state = gpu_unavailable;
        }
      else
        {
        /* unknown mode, default to prohibited */
        np->nd_gpusn[gpuidx].mode = gpu_prohibited;
        np->nd_gpusn[gpuidx].state = gpu_unavailable;
        if (LOGLEVEL >= 3)
          {
          sprintf(log_buf,
            "GPU %s has unknown mode on node %s",
            gpuid,
            np->nd_name);

          log_ext(-1, __func__, log_buf, LOG_DEBUG);
          }
        }
 
      /* add gpu_mode so it gets added to the pbs_attribute */

      if (need_delimiter)
        {
        strcat(gpuinfo, ";");
        }

      switch (np->nd_gpusn[gpuidx].state)
        {
        case gpu_unallocated:
          strcat (gpuinfo, "gpu_state=Unallocated");
          break;
        case gpu_shared:
          strcat (gpuinfo, "gpu_state=Shared");
          break;
        case gpu_exclusive:
          strcat (gpuinfo, "gpu_state=Exclusive");
          break;
        case gpu_unavailable:
          strcat (gpuinfo, "gpu_state=Unavailable");
          break;
        }
      }

    } /* end of while disrst */

  if (strlen(gpuinfo) > 0)
    {
    if (decode_arst(&temp, NULL, NULL, gpuinfo, 0))
      {
      DBPRT(("is_gpustat_get: cannot add attributes\n"));
      
      free_arst(&temp);
      *str_ptr = move_past_gpu_status(str);

      return(DIS_NOCOMMIT);
      }
    }

  /* maintain the gpu count, if it has changed we need to update the nodes file */

  if (reportedgpucnt != startgpucnt)
    {
    np->nd_ngpus = reportedgpucnt;

    /* update the nodes file */
    update_nodes_file(np);
    }

  node_gpustatus_list(&temp, np, ATR_ACTION_ALTER);
  *str_ptr = move_past_gpu_status(str);

  return(DIS_SUCCESS);
  }  /* END is_gpustat_get() */