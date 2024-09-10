static
int
globus_l_job_manager_parse_events(
    globus_l_job_manager_logfile_state_t *      state)
{
    int                                 rc;
    int                                 protocol_msg_type;
    time_t                              stamp;
    char                                jobid[129];
    char                                nl[2];
    int                                 job_state;
    int                                 exit_code;
    struct tm                           gmstamp, *gmstampp;
    fpos_t                              pos;

    SEG_JOB_MANAGER_DEBUG(SEG_JOB_MANAGER_DEBUG_INFO,
            ("globus_l_job_manager_parse_events() called\n"));


    fgetpos(state->fp, &pos);
    while ((rc = fscanf(state->fp, "%d;%ld;%128[^;];%d;%d%1[\n]",
                    &protocol_msg_type,
                    &stamp,
                    jobid,
                    &job_state,
                    &exit_code,
                    nl)) > 4)
    {
        if (rc == 4 && fscanf(state->fp, "%1[\n]", nl) != 1)
        {
            goto bad_line;
        }

        if (protocol_msg_type != 1)
        {
            goto bad_line;
        }

        gmstampp = globus_libc_gmtime_r(&stamp, &gmstamp);

        if (globus_l_time_is_newer(&state->start_timestamp, &gmstamp))
        {
            /* Ignore events that occur before our start timestamp */
            goto bad_line;
        }

        switch(job_state)
        {
        case GLOBUS_GRAM_PROTOCOL_JOB_STATE_PENDING:
            globus_scheduler_event_pending(stamp, jobid);
            break;

        case GLOBUS_GRAM_PROTOCOL_JOB_STATE_ACTIVE:
            globus_scheduler_event_active(stamp, jobid);
            break;

        case GLOBUS_GRAM_PROTOCOL_JOB_STATE_DONE:
            globus_scheduler_event_done(stamp, jobid, exit_code);
            break;

        case GLOBUS_GRAM_PROTOCOL_JOB_STATE_FAILED:
            globus_scheduler_event_failed(stamp, jobid, exit_code);
            break;

        default:
            goto bad_line;
        }
bad_line:
        fgetpos(state->fp, &pos);
    }
    if (feof(state->fp))
    {
        clearerr(state->fp);
        rc = SEG_JOB_MANAGER_ERROR_LOG_EOF;
    }
    else
    {
        rc = 0;
    }
    fsetpos(state->fp, &pos);

    SEG_JOB_MANAGER_DEBUG(SEG_JOB_MANAGER_DEBUG_INFO,
            ("globus_l_job_manager_parse_events() exits\n"));
    return rc;
}