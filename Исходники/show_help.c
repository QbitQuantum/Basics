static int show_help(const char *filename, const char *topic,
                     const char *output, orte_process_name_t *sender)
{
    int rc;
    tuple_list_item_t *tli = NULL;
    orte_namelist_t *pnli;
    time_t now = time(NULL);

    /* If we're aggregating, check for duplicates.  Otherwise, don't
       track duplicates at all and always display the message. */
    if (orte_help_want_aggregate) {
        rc = get_tli(filename, topic, &tli);
    } else {
        rc = ORTE_ERR_NOT_FOUND;
    }

    /* Was it already displayed? */
    if (ORTE_SUCCESS == rc) {
        /* Yes.  But do we want to print anything?  That's complicated.

           We always show the first message of a given (filename,
           topic) tuple as soon as it arrives.  But we don't want to
           show duplicate notices often, because we could get overrun
           with them.  So we want to gather them up and say "We got N
           duplicates" every once in a while.

           And keep in mind that at termination, we'll unconditionally
           show all accumulated duplicate notices.

           A simple scheme is as follows:
           - when the first of a (filename, topic) tuple arrives
             - print the message
             - if a timer is not set, set T=now
           - when a duplicate (filename, topic) tuple arrives
             - if now>(T+5) and timer is not set (due to
               non-pre-emptiveness of our libevent, a timer *could* be
               set!)
               - print all accumulated duplicates
               - reset T=now
             - else if a timer was not set, set the timer for T+5
             - else if a timer was set, do nothing (just wait)
           - set T=now when the timer expires
        */
        ++tli->tli_count_since_last_display;
        if (now > show_help_time_last_displayed + 5 && !show_help_timer_set) {
            show_accumulated_duplicates(0, 0, NULL);
        } else if (!show_help_timer_set) {
            opal_evtimer_set(&show_help_timer_event,
                             show_accumulated_duplicates, NULL);
            opal_evtimer_add(&show_help_timer_event, &show_help_interval);
            show_help_timer_set = true;
        }
    }
    /* Not already displayed */
    else if (ORTE_ERR_NOT_FOUND == rc) {
        if (orte_xml_output) {
            char *tmp;
            tmp = xml_format((unsigned char*)output);
            fprintf(orte_xml_fp, "%s", tmp);
            fflush(orte_xml_fp);
            free(tmp);
        } else {
            fprintf(stderr, "%s", output);
        }
        if (!show_help_timer_set) {
            show_help_time_last_displayed = now;
        }
    }
    /* Some other error occurred */
    else {
        ORTE_ERROR_LOG(rc);
        return rc;
    }

    /* If we're aggregating, add this process name to the list */
    if (orte_help_want_aggregate) {
        pnli = OBJ_NEW(orte_namelist_t);
        if (NULL == pnli) {
            rc = ORTE_ERR_OUT_OF_RESOURCE;
            ORTE_ERROR_LOG(rc);
            return rc;
        }
        pnli->name = *sender;
        opal_list_append(&(tli->tli_processes), &(pnli->item));
    }
    return ORTE_SUCCESS;
}