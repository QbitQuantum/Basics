int
schd_run_job_on(Job *job, Queue *destq, char *exechost, int set_comment)
  {
  char   *id = "schd_run_job_on";
  char    reason[128], tmp_word[20];
  char   *date;
  Queue  *srcq = NULL;
  int     ret = 0;
  int     local_errno = 0;

  /* Get the datestamp from 'ctime()'.  Remove the trailing '\n'. */
  date = ctime(&schd_TimeNow);
  date[strlen(date) - 1] = '\0';

  if (set_comment)
    {
    sprintf(reason, "Started on %s", date);

    if (job->flags & JFLAGS_PRIORITY)
      {
      strcat(reason, " (EXPRESS/high priority job)");
      }

    if (job->flags & JFLAGS_WAITING)
      {
      strcat(reason, " (long-waiting job)");
      }

    schd_comment_job(job, reason, JOB_COMMENT_REQUIRED);
    }

  /* If this is NOT a suspended job... */
  if (!(job->flags & JFLAGS_SUSPENDED))
    {

    /*
     * If a destination Queue is provided, and it is different from the
     * source queue, then ask PBS to move the job to that queue before
     * running it.
     */
    srcq = job->queue;

    /*
     * Move the job from its queue to the specified run queue.
     */

    if ((destq != NULL) && (strcmp(destq->qname, srcq->qname) != 0))
      {
      if (pbs_movejob_err(connector, job->jobid, destq->qname, NULL, &local_errno))
        {
        (void)sprintf(log_buffer, "move job %s to queue %s failed, %d",
                      job->jobid, destq->qname, local_errno);
        log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER,
                   id, log_buffer);
        DBPRT(("%s: %s\n", id, log_buffer));
        return (-1);
        }

      schd_move_job_to(job, destq);
      }

    /*
    * Give the job handle (JOBID) to PBS to run.
    */
    if (pbs_runjob_err(connector, job->jobid, exechost, NULL, &local_errno))
      {
      (void)sprintf(log_buffer, "failed start job %s on queue %s@%s, %d",
                    job->jobid, destq->qname, exechost, local_errno);
      log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id, log_buffer);
      DBPRT(("%s: %s\n", id, log_buffer));

      /*
       * Running failed! Move the job back to the source queue (if
       * applicable) before returning. This prevents jobs being left
       * in execution queues.
       */

      if (srcq)
        {
        DBPRT(("Attempting to move job %s back to queue %s\n",
               job->jobid, srcq->qname));

        if (pbs_movejob_err(connector, job->jobid, srcq->qname, NULL, &local_errno))
          {
          (void)sprintf(log_buffer,
                        "failed to move job %s back to queue %s, %d",
                        job->jobid, srcq->qname, local_errno);
          log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id,
                     log_buffer);
          DBPRT(("%s: %s\n", id, log_buffer));
          }

        schd_move_job_to(job, srcq);
        }

      return (-1);
      }

    strcpy(tmp_word, "started");
    }
  else    /* it IS a suspended job */
    {

    schd_move_job_to(job, destq);
    ret = pbs_sigjob(connector, job->jobid, "resume", NULL);

    if (ret)
      {
      sprintf(log_buffer, "resume of job %s FAILED (%d)",
              job->jobid, ret);
      return (-1);
      }

    job->flags &= ~JFLAGS_SUSPENDED;

    strcpy(tmp_word, "resumed");
    }

  /* PBS accepted the job (and presumably will run it). Log the fact. */
  (void)sprintf(log_buffer, "job %s %s on %s@%s", job->jobid, tmp_word,
                destq->qname, exechost);

  log_record(PBSEVENT_SYSTEM, PBS_EVENTCLASS_SERVER, id, log_buffer);

  DBPRT(("%s: %s\n", id, log_buffer));

  /*
   * Change the state of the local representation of the job to "Running".
   */
  job->state = 'R';

  /*
   * Account for the job on this queue's statistics.  'queued' will be
   * bumped up if the queued job was moved to a new destination queue.
   */

  job->queue->queued --;

  job->queue->running ++;

  /* The queue is no longer idle.  Unset the idle timer. */
  job->queue->idle_since = 0;

  return (0);    /* Job successfully started. */
  }