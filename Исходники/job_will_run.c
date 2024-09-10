/*
 * job_will_run2 - Determine if, when and where a pending job can be
 *		   initiated with the currently running jobs either preempted
 *		   or left running as on other resources
 * cmd_ptr IN   - CMD=JOBWILLRUN ARG=<JOBID> [STARTTIME=<TIME>]
 *		  NODES=<AVAIL_NODES> [PREEMPT=<JOBID1>[,<JOBID2> ..]]
 * err_code OUT - 0 on success or some error code
 * err_msg OUT  - error message if any of the specified jobs can not be started
 *		  at the specified time (if given) on the available nodes.
 *		  Otherwise information on when and where the pending jobs
 *		  will be initiated
 *                ARG=<JOBID> TASKS=<CPU_COUNT> STARTTIME=<TIME>
 *			NODES=<USED_NODES> [PREEMPT=<JOBID1>[,<JOBID2> ..]]
 * NOTE: xfree() err_msg if err_code is zero
 * RET 0 on success, -1 on failure
 */
extern int	job_will_run2(char *cmd_ptr, int *err_code, char **err_msg)
{
	char *arg_ptr, *buf, *tmp_buf, *tmp_char;
	int preemptee_cnt = 0;
	uint32_t jobid, *preemptee = NULL, tmp_id;
	time_t start_time;
	char *avail_nodes = NULL;
	/* Locks: write job, read node and partition info */
	slurmctld_lock_t job_write_lock = {
		NO_LOCK, WRITE_LOCK, READ_LOCK, READ_LOCK, NO_LOCK };

	arg_ptr = strstr(cmd_ptr, "ARG=");
	if (arg_ptr == NULL) {
		*err_code = -300;
		*err_msg = "JOBWILLRUN lacks ARG";
		error("wiki: JOBWILLRUN lacks ARG");
		return -1;
	}
	arg_ptr += 4;

	jobid = strtoul(arg_ptr, &tmp_char, 10);
	if ((tmp_char[0] != ' ') && (tmp_char[0] != '\0')) {
		*err_code = -300;
		*err_msg = "Invalid ARG value";
		error("wiki: JOBWILLRUN has invalid ARG value");
		return -1;
	}

	arg_ptr = strstr(cmd_ptr, "STARTTIME=");
	if (arg_ptr) {
		arg_ptr += 10;
		start_time = strtoul(arg_ptr, &tmp_char, 10);
		if ((tmp_char[0] != ' ') && (tmp_char[0] != '\0')) {
			*err_code = -300;
			*err_msg = "Invalid STARTTIME value";
			error("wiki: JOBWILLRUN has invalid STARTTIME value");
			return -1;
		}
	} else {
		start_time = time(NULL);
	}

	arg_ptr = strstr(cmd_ptr, "PREEMPT=");
	if (arg_ptr) {
		arg_ptr += 8;
		preemptee = xmalloc(sizeof(uint32_t) * strlen(arg_ptr));
		while (1) {
			tmp_id = strtoul(arg_ptr, &tmp_char, 10);
			if ((tmp_char[0] != ' ') && (tmp_char[0] != '\0') &&
			    (tmp_char[0] != ',')) {
				*err_code = -300;
				*err_msg = "Invalid PREEMPT value";
				error("wiki: JOBWILLRUN has invalid PREEMPT "
				      "value");
				xfree(preemptee);
				xfree(avail_nodes);
				return -1;
			}
			preemptee[preemptee_cnt++] = tmp_id;
			if (tmp_char[0] != ',')
				break;
			arg_ptr = tmp_char + 1;
		}
	}

	/* Keep this last, since we modify the input string */
	arg_ptr = strstr(cmd_ptr, "NODES=");
	if (arg_ptr) {
		arg_ptr += 6;
		avail_nodes = xstrdup(arg_ptr);
		arg_ptr = strchr(avail_nodes, ' ');
		if (arg_ptr)
			arg_ptr[0] = '\0';
	} else {
		*err_code = -300;
		*err_msg = "Missing NODES value";
		error("wiki: JOBWILLRUN lacks NODES value");
		xfree(preemptee);
		return -1;
	}

	lock_slurmctld(job_write_lock);
	buf = _will_run_test2(jobid, start_time, avail_nodes,
			      preemptee, preemptee_cnt,
			      err_code, err_msg);
	unlock_slurmctld(job_write_lock);

	xfree(preemptee);
	xfree(avail_nodes);
	if (!buf)
		return -1;

	tmp_buf = xmalloc(strlen(buf) + 32);
	sprintf(tmp_buf, "SC=0 ARG=%s", buf);
	xfree(buf);
	*err_code = 0;
	*err_msg = tmp_buf;
	return 0;
}