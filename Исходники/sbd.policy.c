static int
cleanupMigJob(struct jobCard *jp)
{
    static char fname[] = "cleanupMigJob()";
    int pid;


    unlockHosts (jp, jp->jobSpecs.numToHosts);

    if (!jp->jobSpecs.postCmd || jp->jobSpecs.postCmd[0] == '\0')
        return 0;


    if ((pid = fork()) < 0) {
	ls_syslog(LOG_ERR, I18N_JOB_FAIL_S_M, fname,
	    lsb_jobid2str(jp->jobSpecs.jobId), "fork");
        lsb_merr2(_i18n_msg_get(ls_catd , NL_SETN, 700,
	    "Unable to fork a child to run the queue's post-exec command for job <%s>.  Please run <%s> manually if necessary.\n"), /* catgets 700 */
	    lsb_jobid2str(jp->jobSpecs.jobId),
	    jp->jobSpecs.postCmd);
	return (pid);
    }

    if (pid)
	return (pid);



    closeBatchSocket();
    putEnv(LS_EXEC_T, "END");

    if (postJobSetup(jp) == -1) {
	ls_syslog(LOG_ERR, I18N_JOB_FAIL_S, fname,
	    lsb_jobid2str(jp->jobSpecs.jobId), "postJobSetup");
	lsb_merr2(_i18n_msg_get(ls_catd , NL_SETN, 701,
	    "Unable to setup the environment for job <%s> to run the queue's post exec.  Please run <%s> manually if necessary.\n"), /* catgets 701 */
	    lsb_jobid2str(jp->jobSpecs.jobId),
	    jp->jobSpecs.postCmd);
	exit(-1);
    }

    runQPost(jp);
    exit(0);
}