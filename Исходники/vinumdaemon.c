void
vinum_daemon(void)
{
    int s;
    struct daemonq *request;

    curproc->p_flag |= P_INMEM | P_SYSTEM;		    /* we're a system process */
    daemon_save_config();				    /* start by saving the configuration */
    daemonpid = curproc->p_pid;				    /* mark our territory */
    while (1) {
        tsleep(&vinum_daemon, PRIBIO, "vinum", 0);	    /* wait for something to happen */

        /*
         * It's conceivable that, as the result of an
         * I/O error, we'll be out of action long
         * enough that another daemon gets started.
         * That's OK, just give up gracefully.
         */
        if (curproc->p_pid != daemonpid) {		    /* we've been ousted in our sleep */
            if (daemon_options & daemon_verbose)
                log(LOG_INFO, "vinum: abdicating\n");
            return;
        }
        while (daemonq != NULL) {			    /* we have work to do, */
            s = splhigh();				    /* don't get interrupted here */
            request = daemonq;				    /* get the request */
            daemonq = daemonq->next;			    /* and detach it */
            if (daemonq == NULL)			    /* got to the end, */
                dqend = NULL;				    /* no end any more */
            splx(s);

            switch (request->type) {
            /*
             * We had an I/O error on a request.  Go through the
             * request and try to salvage it
             */
            case daemonrq_ioerror:
                if (daemon_options & daemon_verbose) {
                    struct request *rq = request->info.rq;

                    log(LOG_WARNING,
                        "vinum: recovering I/O request: %p\n%s dev %d.%d, offset 0x%x, length %ld\n",
                        rq,
                        rq->bp->b_flags & B_READ ? "Read" : "Write",
                        major(rq->bp->b_dev),
                        minor(rq->bp->b_dev),
                        rq->bp->b_blkno,
                        rq->bp->b_bcount);
                }
                recover_io(request->info.rq);		    /* the failed request */
                break;

            /*
             * Write the config to disk.  We could end up with
             * quite a few of these in a row.  Only honour the
             * last one
             */
            case daemonrq_saveconfig:
                if ((daemonq == NULL)			    /* no more requests */
                        ||(daemonq->type != daemonrq_saveconfig)) { /* or the next isn't the same */
                    if (((daemon_options & daemon_noupdate) == 0) /* we're allowed to do it */
                            &&((vinum_conf.flags & VF_READING_CONFIG) == 0)) { /* and we're not building the config now */
                        /*
                           * We obviously don't want to save a
                           * partial configuration.  Less obviously,
                           * we don't need to do anything if we're
                           * asked to write the config when we're
                           * building it up, because we save it at
                           * the end.
                         */
                        if (daemon_options & daemon_verbose)
                            log(LOG_INFO, "vinum: saving config\n");
                        daemon_save_config();		    /* save it */
                    }
                }
                break;

            case daemonrq_return:			    /* been told to stop */
                if (daemon_options & daemon_verbose)
                    log(LOG_INFO, "vinum: stopping\n");
                daemon_options |= daemon_stopped;	    /* note that we've stopped */
                Free(request);
                while (daemonq != NULL) {		    /* backed up requests, */
                    request = daemonq;			    /* get the request */
                    daemonq = daemonq->next;		    /* and detach it */
                    Free(request);			    /* then free it */
                }
                wakeup(&vinumclose);			    /* and wake any waiting vinum(8)s */
                return;

            case daemonrq_ping:				    /* tell the caller we're here */
                if (daemon_options & daemon_verbose)
                    log(LOG_INFO, "vinum: ping reply\n");
                wakeup(&vinum_finddaemon);		    /* wake up the caller */
                break;

            case daemonrq_closedrive:			    /* close a drive */
                close_drive(request->info.drive);	    /* do it */
                break;

            case daemonrq_init:				    /* initialize a plex */
            /* XXX */
            case daemonrq_revive:			    /* revive a subdisk */
            /* XXX */
            /* FALLTHROUGH */
            default:
                log(LOG_WARNING, "Invalid request\n");
                break;
            }
            if (request->privateinuse)			    /* one of ours, */
                request->privateinuse = 0;		    /* no longer in use */
            else
                Free(request);				    /* return it */
        }
    }
}