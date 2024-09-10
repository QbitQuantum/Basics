int CPADestroyPartition(

  job *pjob)

  {
  char id[] = "CPADestroyPartition";

  int rc;
  int ErrorP;        /* O - non-zero if users of partition encountered error */
  unsigned long ParID;
  unsigned long long AdminCookie;

  resource              *presc;         /* Requested Resource List */
  resource_def          *prd;
  attribute             *pattr;

  pattr = &pjob->ji_wattr[JOB_ATR_resource];

  prd = find_resc_def(svr_resc_def, "cpapartition", svr_resc_size);

  if (prd == NULL)
    {
    return(PBSE_SYSTEM);
    }

  if ((presc = find_resc_entry(pattr, prd)) == NULL)
    {
    return(PBSE_SYSTEM);  /* is this a real error? */
    }

  ParID = atoL(presc->rs_value.at_val.at_str);

  prd = find_resc_def(svr_resc_def, "cpaadmincookie", svr_resc_size);

  if (prd == NULL)
    {
    return(PBSE_SYSTEM);
    }

  if ((presc = find_resc_entry(pattr, prd)) == NULL)
    {
    return(PBSE_SYSTEM);  /* is this a real error? */
    }

  AdminCookie = atoL(presc->rs_value.at_val.at_str);

  if (LOGLEVEL >= 2)
    {
    printf("INFO:  destroying partition %lu with cookie %llu\n",
           ParID,
           AdminCookie);

    log_record(
      PBSEVENT_JOB,
      PBS_EVENTCLASS_JOB,
      pjob->ji_qs.ji_jobid,
      log_buffer);
    }

  /* will fail if yod is present */

  rc = cpa_destroy_partition(
         ParID,
         AdminCookie,
         &ErrorP);      /* O - if set, destroy failed on one or more tasks */

  if (rc != 0)
    {
    sprintf(log_buffer, "cpa_destroy_partition: rc=%d (%s)\n",
            rc,
            cpa_rc2str(rc));

    log_err(-1, id, log_buffer);

    return(1);
    }

  return(0);
  }  /* END CPADestroyPartition() */