cmddatas_t *
read_cmdfile(
    char *filename)
{
    cmddatas_t *cmddatas = g_new0(cmddatas_t, 1);
    cmddata_t  *cmddata;
    char  *s, *fp, *operation;
    char   ch;
    char **xlines;
    int    i;
    int    pid;
    pid_t  pids[NB_PIDS];
    pid_t  new_pids[NB_PIDS];
    int    nb_pids = 0;
    int    result;

    cmddatas->lock = file_lock_new(filename);
    cmddatas->cmdfile = g_hash_table_new_full(g_direct_hash, g_direct_equal,
					      NULL, &free_cmddata);
    // open
    while ((result = file_lock_lock(cmddatas->lock)) == 1) {
        sleep(1);
    }
    if (result != 0) {
        g_debug("read_cmdfile open failed: %s", strerror(errno));
    }

    if (!cmddatas->lock->data) {
	cmddatas->version = 1;
	cmddatas->max_id = 0;
	return cmddatas;
    }
    xlines = g_strsplit(cmddatas->lock->data, "\n", 0);

    // read
    if (sscanf(xlines[0], "VERSION %d", &cmddatas->version) != 1) {};
    if (sscanf(xlines[1], "ID %d", &cmddatas->max_id) != 1) {};

    // read cmd
    for (i=2; xlines[i] != NULL; i++) {
	int id;
	s = xlines[i];
	if (*s == '\0') continue;
	ch = *s++;
	skip_whitespace(s, ch);
	if (ch == '\0' || sscanf((s - 1), "%d", &id) != 1) {
	    continue;
	}
	skip_integer(s, ch);
	skip_whitespace(s, ch);
	operation = s - 1;
        skip_non_whitespace(s, ch);
        s[-1] = '\0';
	if (!g_str_equal(operation, "FLUSH") &&
	    !g_str_equal(operation, "COPY")) {
	    g_debug("BAD operation %s: %s", operation, s);
	    continue;
	}
	cmddata = g_new0(cmddata_t, 1);
	cmddata->id = id;
	skip_whitespace(s, ch);
	fp = s - 1;
        skip_non_whitespace(s, ch);
        s[-1] = '\0';
        cmddata->config = unquote_string(fp);
	if (g_str_equal(operation, "FLUSH")) {
	    cmddata->operation = CMD_FLUSH;
	    skip_whitespace(s,ch);
	    fp = s - 1;
	    skip_quoted_string(s, ch);
	    s[-1] = '\0';
	    cmddata->holding_file = unquote_string(fp);
	} else if (g_str_equal(operation, "COPY")) {
	    char *src_labels;
	    char *slabels;
	    char *a;

	    cmddata->operation = CMD_COPY;
	    skip_whitespace(s,ch);
	    fp = s - 1;
	    skip_quoted_string(s, ch);
	    s[-1] = '\0';
	    cmddata->src_storage = unquote_string(fp);
	    skip_whitespace(s,ch);
	    fp = s - 1;
	    skip_quoted_string(s, ch);
	    s[-1] = '\0';
	    cmddata->src_pool = unquote_string(fp);
	    skip_whitespace(s,ch);
	    fp = s - 1;
	    skip_quoted_string(s, ch);
	    s[-1] = '\0';
	    cmddata->src_label = unquote_string(fp);
	    skip_whitespace(s,ch);
	    fp = s - 1;
	    skip_integer(s, ch);
	    s[-1] = '\0';
	    cmddata->src_fileno = atoi(fp);

	    skip_whitespace(s,ch);
	    fp = s - 1;
	    skip_quoted_string(s, ch);
	    s[-1] = '\0';
	    slabels = src_labels = unquote_string(fp);
	    cmddata->src_labels_str = g_strdup(src_labels);
	    a = strstr(slabels, " ;");
	    if (a) {
		slabels = a+2;
		while ((a = strstr(slabels, " ;"))) {
		    *a = '\0';
		    cmddata->src_labels = g_slist_append(cmddata->src_labels, g_strdup(slabels));
		    slabels = a+2;
		}
	    }
	    g_free(src_labels);

	    skip_whitespace(s,ch);
	    fp = s - 1;
	    skip_integer(s, ch);
	    s[-1] = '\0';
	    cmddata->start_time = atoll(fp);
	} else {
	}
	skip_whitespace(s, ch);
	fp = s - 1;
	skip_quoted_string(s, ch);
	s[-1] = '\0';
	cmddata->hostname = unquote_string(fp);
	skip_whitespace(s, ch);
	fp = s - 1;
	skip_quoted_string(s, ch);
	s[-1] = '\0';
	cmddata->diskname = unquote_string(fp);
	skip_whitespace(s, ch);
	fp = s - 1;
	skip_quoted_string(s, ch);
	s[-1] = '\0';
	cmddata->dump_timestamp = unquote_string(fp);
	skip_whitespace(s,ch);
	fp = s - 1;
	skip_quoted_string(s, ch);
	s[-1] = '\0';
	cmddata->level = atoi(fp);
	skip_whitespace(s, ch);
	fp = s - 1;
	skip_quoted_string(s, ch);
	s[-1] = '\0';
	cmddata->dst_storage = unquote_string(fp);
	skip_whitespace(s, ch);
	fp = s - 1;
	skip_non_whitespace(s, ch);
	s[-1] = '\0';
	if (sscanf(fp, "WORKING:%d", &pid) != 1) {
	}
	cmddata->working_pid = pid;
	skip_whitespace(s, ch);
	fp = s - 1;
	skip_non_whitespace(s, ch);
	s[-1] = '\0';
	if (g_str_equal(fp, "DONE")) {
	    cmddata->status = CMD_DONE;
	} else if (g_str_equal(fp, "TODO")) {
	    cmddata->status = CMD_TODO;
	} else if (strncmp(fp, "PARTIAL", 7) == 0) {
	    long long lsize;
	    cmddata->status = CMD_PARTIAL;
	    if (sscanf(fp, "PARTIAL:%lld", &lsize) != 1) {
	    } else {
		cmddata->size = lsize;
	    }
	} else {
	}

	/* validate working_pid */
	if (!checked_working_pid && cmddata->working_pid != 0) {
	    int   i;

	    for (i = 0; i < nb_pids; i++) {
		if (pids[i] == cmddata->working_pid) {
		    cmddata->working_pid = new_pids[i];
		    i += 100;
		    continue;
		}
	    }
	    if (nb_pids < NB_PIDS) {
		pids[nb_pids] = cmddata->working_pid;
		if (kill(cmddata->working_pid, 0) != 0)
		    cmddata->working_pid =0;
		new_pids[nb_pids] = cmddata->working_pid;
		nb_pids++;
	    }
	}

	g_hash_table_insert(cmddatas->cmdfile, GINT_TO_POINTER(cmddata->id), cmddata);
    }

    g_strfreev(xlines);
    checked_working_pid = 1;

    return cmddatas;
}