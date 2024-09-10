/*
 * This function takes a pointer to a struct batch_status for a job, and
 * fills in the appropriate fields of the supplied job struct.  It returns
 * the number of items that were found.
 */
int
schd_get_jobinfo(Batch_Status *bs, Job *job)
  {
  char *id = "schd_get_jobinfo";
  int     changed = 0;
  int     cpu_req = 0;
  size_t  mem_req = 0;
  char     *host;
  char *p, *tmp_p, *var_p;
  AttrList *attr;
  char      canon[PBS_MAXHOSTNAME + 1];
  int     istrue;

  memset((void *)job, 0, sizeof(Job));

  job->jobid = schd_strdup(bs->name);

  if (job->jobid == NULL)
    {
    log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
               "schd_strdup(bs->name)");
    return (-1);
    }

  changed ++;

  for (attr = bs->attribs; attr != NULL; attr = attr->next)
    {

    /*
     * If this is the 'owner' field, chop it into 'owner' and 'host'
     * fields, and copy them into the Job struct.
     */
    if (!strcmp(attr->name, ATTR_owner))
      {

      /* Look for the '@' that separates user and hostname. */
      host = strchr(attr->value, '@');

      if (host)
        {
        *host = '\0'; /* Replace '@' with NULL (ends username). */
        host ++; /* Move to first character of hostname. */
        }

      job->owner = schd_strdup(attr->value);

      if (job->owner == NULL)
        {
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                   "schd_strdup(job->owner)");
        return (-1);
        }

      changed ++;

      job->host  = schd_strdup(host);

      if (job->host == NULL)
        {
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                   "schd_strdup(job->host)");
        return (-1);
        }

      changed ++;

      /*
       * We don't "own" the attribute strings, so put back the '@'
       * character we removed above, in case something else expects
       * it to be there.
       * Note that 'host' points to the first character of the host-
       * name, not the hole one character behind.
       */

      if (host)
        {
        host --; /* Step back one character. */
        *host = '@'; /* Replace the '@' that was deleted above. */
        }

      /* That's all for the owner field. */
      continue;
      }

    /* The group to which to charge the resources for this job. */
    if (!strcmp(attr->name, ATTR_egroup))
      {
      job->group = schd_strdup(attr->value);

      if (job->group == NULL)
        {
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                   "schd_strdup(job->group)");
        return (-1);
        }

      changed ++;

      continue;
      }

    /* The comment currently assigned to this job. */
    if (!strcmp(attr->name, ATTR_comment))
      {
      job->comment = schd_strdup(attr->value);

      if (job->comment == NULL)
        {
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                   "schd_strdup(job->comment)");
        return (-1);
        }

      changed ++;

      continue;
      }

    /* The host on which this job is running. */
    if (!strcmp(attr->name, ATTR_exechost))
      {
      job->exechost = schd_strdup(attr->value);

      if (job->exechost == NULL)
        {
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                   "schd_strdup(job->exechost)");
        return (-1);
        }

      changed ++;

      continue;
      }

    if (!strcmp(attr->name, ATTR_inter))
      {
      /* Is this job interactive or not? */
      if (schd_val2bool(attr->value, &istrue) == 0)
        {
        if (istrue)
          job->flags |= JFLAGS_INTERACTIVE;
        else
          job->flags &= ~JFLAGS_INTERACTIVE;

        changed ++;
        }
      else
        {
        DBPRT(("%s: can't parse %s = %s into boolean\n", id,
               attr->name, attr->value));
        }

      continue;
      }

    if (!strcmp(attr->name, ATTR_state))
      {
      /* State is one of 'R', 'Q', 'E', etc. */
      job->state = attr->value[0];
      changed ++;

      continue;
      }

    if (!strcmp(attr->name, ATTR_queue))
      {
      job->qname = schd_strdup(attr->value);

      if (job->qname == NULL)
        {
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                   "schd_strdup(job->qname)");
        return (-1);
        }

      job->flags |= JFLAGS_QNAME_LOCAL;

      changed ++;

      continue;
      }

    if (!strcmp(attr->name, ATTR_v))
      {
      var_p = schd_strdup(attr->value);

      if (var_p == NULL)
        {
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                   "schd_strdup(Variable_List)");
        return (-1);
        }

      p = NULL;

      tmp_p = strstr(var_p, "PBS_O_QUEUE");

      if (tmp_p)
        {
        p = strtok(tmp_p, "=");
        p = strtok(NULL,  ", ");
        }

      if (p != NULL)
        {
        job->oqueue = schd_strdup(p);
        }
      else
        {
        /* if the originating queue is unknown, default
         * to the locally defined "submit" queue.
         */
        job->oqueue = schd_strdup(schd_SubmitQueue->queue->qname);
        }

      free(var_p);

      changed ++;
      continue;
      }

    if (!strcmp(attr->name, ATTR_l))
      {
      if (!strcmp(attr->resource, "walltime"))
        {
        job->walltime = schd_val2sec(attr->value);
        changed ++;

        }
      else if (!strcmp(attr->resource, "ncpus"))
        {
        cpu_req = atoi(attr->value);
        job->nodes = MAX(job->nodes, NODES_FROM_CPU(cpu_req));
        changed ++;

        }
      else if (!strcmp(attr->resource, "mem"))
        {
        mem_req = schd_val2byte(attr->value);
        job->nodes = MAX(job->nodes, NODES_FROM_MEM(mem_req));
        changed ++;

#ifdef NODEMASK
        }
      else if (!strcmp(attr->resource, "nodemask"))
        {
        if (schd_str2mask(attr->value, &job->nodemask))
          {
          (void)sprintf(log_buffer,
                        "bad nodemask %s for job %s", attr->value, job->jobid);
          log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                     log_buffer);
          }
        else
          changed++; /* Job nodemask was valid. */

#endif /* NODEMASK */

        }

      if (!strcmp(attr->resource, HPM_ATTRIBUTE))
        {
        /*
         * If the job requests hpm support, set the flag, otherwise
         * turn it off.
         */
        if (schd_val2bool(attr->value, &istrue) == 0)
          {
          if (istrue)
            job->flags |= JFLAGS_NEEDS_HPM;
          else
            job->flags &= ~JFLAGS_NEEDS_HPM;

          changed ++;
          }
        else
          {
          DBPRT(("%s: can't parse %s = %s into boolean\n", id,
                 attr->name, attr->value));
          }
        }

      /* That's all for requested resources. */
      continue;
      }

    if (!strcmp(attr->name, ATTR_used))
      {
      if (!strcmp(attr->resource, "walltime"))
        {
        job->walltime_used = schd_val2sec(attr->value);

        changed ++;
        }

      /* No other interesting cases. */
      continue;
      }

    /* Creation time attribute. */
    if (!strcmp(attr->name, ATTR_ctime))
      {
      /* How long ago was it put in the queue ? */
      job->time_queued = schd_TimeNow - atoi(attr->value);

      continue;
      }

    /* Modified time attribute. */
    if (!strcmp(attr->name, ATTR_mtime))
      {
      /* When was the job last modified? */
      job->mtime = atoi(attr->value);

      continue;
      }

#ifdef ATTR_etime
    /*
     * When was the job last eligible to run?  When a user-hold is
     * released, this value is updated to the current time.  This
     * prevents users from gaining higher priority from holding their
     * jobs.
     */
    if (!strcmp(attr->name, ATTR_etime))
      {
      job->eligible = schd_TimeNow - atoi(attr->value);

      continue;
      }

#endif /* ATTR_etime */
    }

  /*
   * If this job is in the "Running" state, compute how many seconds
   * remain until it is completed.
   */
  if (job->state == 'R')
    {
    job->time_left = job->walltime - job->walltime_used;
    }

  /*
   * If this job was enqueued since the last time we ran, set the job
   * flag to indicate that we have not yet seen this job.  This makes it
   * a candidate for additional processing.  There may be some inaccuracy,
   * since the time_t has resolution of 1 second.  Attempt to err on the
   * side of caution.
   */
  if ((job->state == 'Q') && (job->time_queued != UNSPECIFIED))
    {
    if (job->time_queued <= (schd_TimeNow - schd_TimeLast))
      {
      job->flags |= JFLAGS_FIRST_SEEN;
      }
    }

  /*
   * If the 'etime' attribute wasn't found, set it to the time the job has
   * been queued.  Most jobs will be eligible to run their entire lifetime.
   * The exception is a job that has been held - if it was a user hold,
   * the release will reset the etime to the latest value.
   * If not eligible time was given, use the job's creation time.
   */
  if (!job->eligible)
    job->eligible = job->time_queued;

  /*
   * If the job provided a memory or CPU resource that does not match
   * the resources that will be allocated by the assigned nodes (i.e.
   * a request for 100mb of memory and 16 CPUs - the job will "get" all
   * 4GB of memory anyway), alter the job attributes such that they
   * will align with the assigned nodes later.
   */
  bump_rsrc_requests(job, cpu_req, mem_req);

  return (changed);
  }