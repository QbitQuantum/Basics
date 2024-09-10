static void
process_limit (const pam_handle_t *pamh, int source, const char *lim_type,
	       const char *lim_item, const char *lim_value,
	       int ctrl, struct pam_limit_s *pl)
{
    int limit_item;
    int limit_type = 0;
    int int_value = 0;
    rlim_t rlimit_value = 0;
    char *endptr;
    const char *value_orig = lim_value;

    if (ctrl & PAM_DEBUG_ARG)
	 pam_syslog(pamh, LOG_DEBUG, "%s: processing %s %s %s for %s",
		    __FUNCTION__, lim_type, lim_item, lim_value,
		    limits_def_names[source]);

    if (strcmp(lim_item, "cpu") == 0)
        limit_item = RLIMIT_CPU;
    else if (strcmp(lim_item, "fsize") == 0)
        limit_item = RLIMIT_FSIZE;
    else if (strcmp(lim_item, "data") == 0)
	limit_item = RLIMIT_DATA;
    else if (strcmp(lim_item, "stack") == 0)
	limit_item = RLIMIT_STACK;
    else if (strcmp(lim_item, "core") == 0)
	limit_item = RLIMIT_CORE;
    else if (strcmp(lim_item, "rss") == 0)
	limit_item = RLIMIT_RSS;
    else if (strcmp(lim_item, "nproc") == 0)
	limit_item = RLIMIT_NPROC;
    else if (strcmp(lim_item, "nofile") == 0)
	limit_item = RLIMIT_NOFILE;
    else if (strcmp(lim_item, "memlock") == 0)
	limit_item = RLIMIT_MEMLOCK;
    else if (strcmp(lim_item, "as") == 0)
	limit_item = RLIMIT_AS;
#ifdef RLIMIT_LOCKS
    else if (strcmp(lim_item, "locks") == 0)
	limit_item = RLIMIT_LOCKS;
#endif
#ifdef RLIMIT_SIGPENDING
    else if (strcmp(lim_item, "sigpending") == 0)
	limit_item = RLIMIT_SIGPENDING;
#endif
#ifdef RLIMIT_MSGQUEUE
    else if (strcmp(lim_item, "msgqueue") == 0)
	limit_item = RLIMIT_MSGQUEUE;
#endif
#ifdef RLIMIT_NICE
    else if (strcmp(lim_item, "nice") == 0)
	limit_item = RLIMIT_NICE;
#endif
#ifdef RLIMIT_RTPRIO
    else if (strcmp(lim_item, "rtprio") == 0)
	limit_item = RLIMIT_RTPRIO;
#endif
    else if (strcmp(lim_item, "maxlogins") == 0) {
	limit_item = LIMIT_LOGIN;
	pl->flag_numsyslogins = 0;
    } else if (strcmp(lim_item, "maxsyslogins") == 0) {
	limit_item = LIMIT_NUMSYSLOGINS;
	pl->flag_numsyslogins = 1;
    } else if (strcmp(lim_item, "priority") == 0) {
	limit_item = LIMIT_PRI;
    } else {
        pam_syslog(pamh, LOG_DEBUG, "unknown limit item '%s'", lim_item);
        return;
    }

    if (strcmp(lim_type,"soft")==0)
	limit_type=LIMIT_SOFT;
    else if (strcmp(lim_type, "hard")==0)
	limit_type=LIMIT_HARD;
    else if (strcmp(lim_type,"-")==0)
	limit_type=LIMIT_SOFT | LIMIT_HARD;
    else if (limit_item != LIMIT_LOGIN && limit_item != LIMIT_NUMSYSLOGINS) {
        pam_syslog(pamh, LOG_DEBUG, "unknown limit type '%s'", lim_type);
        return;
    }
	if (limit_item != LIMIT_PRI
#ifdef RLIMIT_NICE
	    && limit_item != RLIMIT_NICE
#endif
	    && (strcmp(lim_value, "-1") == 0
		|| strcmp(lim_value, "-") == 0 || strcmp(lim_value, "unlimited") == 0
		|| strcmp(lim_value, "infinity") == 0)) {
		int_value = -1;
		rlimit_value = RLIM_INFINITY;
	} else if (limit_item == LIMIT_PRI || limit_item == LIMIT_LOGIN ||
#ifdef RLIMIT_NICE
		limit_item == RLIMIT_NICE ||
#endif
		limit_item == LIMIT_NUMSYSLOGINS) {
		long temp;
		temp = strtol (lim_value, &endptr, 10);
		temp = temp < INT_MAX ? temp : INT_MAX;
		int_value = temp > INT_MIN ? temp : INT_MIN;
		if (int_value == 0 && value_orig == endptr) {
			pam_syslog(pamh, LOG_DEBUG,
				   "wrong limit value '%s' for limit type '%s'",
				   lim_value, lim_type);
            return;
		}
	} else {
#ifdef __USE_FILE_OFFSET64
		rlimit_value = strtoull (lim_value, &endptr, 10);
#else
		rlimit_value = strtoul (lim_value, &endptr, 10);
#endif
		if (rlimit_value == 0 && value_orig == endptr) {
			pam_syslog(pamh, LOG_DEBUG,
				   "wrong limit value '%s' for limit type '%s'",
				   lim_value, lim_type);
			return;
		}
	}

    /* one more special case when limiting logins */
    if ((source == LIMITS_DEF_ALL || source == LIMITS_DEF_ALLGROUP)
		&& (limit_item != LIMIT_LOGIN)) {
	if (ctrl & PAM_DEBUG_ARG)
	    pam_syslog(pamh, LOG_DEBUG,
		       "'%%' domain valid for maxlogins type only");
	return;
    }

    switch(limit_item) {
        case RLIMIT_CPU:
         if (rlimit_value != RLIM_INFINITY)
            rlimit_value *= 60;
         break;
        case RLIMIT_FSIZE:
        case RLIMIT_DATA:
        case RLIMIT_STACK:
        case RLIMIT_CORE:
        case RLIMIT_RSS:
        case RLIMIT_MEMLOCK:
        case RLIMIT_AS:
         if (rlimit_value != RLIM_INFINITY)
            rlimit_value *= 1024;
    	 break;
#ifdef RLIMIT_NICE
	case RLIMIT_NICE:
	 if (int_value > 19)
	    int_value = 19;
	 rlimit_value = 19 - int_value;
#endif
         break;
    }

    if ( (limit_item != LIMIT_LOGIN)
	 && (limit_item != LIMIT_NUMSYSLOGINS)
	 && (limit_item != LIMIT_PRI) ) {
        if (limit_type & LIMIT_SOFT) {
	    if (pl->limits[limit_item].src_soft < source) {
                return;
	    } else {
                pl->limits[limit_item].limit.rlim_cur = rlimit_value;
                pl->limits[limit_item].src_soft = source;
            }
	}
        if (limit_type & LIMIT_HARD) {
	    if (pl->limits[limit_item].src_hard < source) {
                return;
            } else {
                pl->limits[limit_item].limit.rlim_max = rlimit_value;
                pl->limits[limit_item].src_hard = source;
            }
	}
    } else {
	/* recent kernels support negative priority limits (=raise priority) */

	if (limit_item == LIMIT_PRI) {
		pl->priority = int_value;
	} else {
	        if (pl->login_limit_def < source) {
	            return;
	        } else {
	            pl->login_limit = int_value;
	            pl->login_limit_def = source;
        	}
	}
    }
    return;
}