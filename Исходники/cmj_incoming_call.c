void cmj_incoming_call(struct NTD *tsk)
{
	int rval, rc;
	struct CLB *lnk;
	struct sockaddr_in in;
	GTM_SOCKLEN_TYPE sz = SIZEOF(in);
	cmi_status_t status;

	while ((-1 == (rval = ACCEPT(tsk->listen_fd, (struct sockaddr *)&in, (GTM_SOCKLEN_TYPE *)&sz))) && EINTR == errno)
		;
	while (rval >= 0)
	{
		status = cmj_setupfd(rval);
		if (CMI_ERROR(status))
		{
			CLOSEFILE_RESET(rval, rc);	/* resets "rval" to FD_INVALID */
			return;
		}
		status = cmj_set_async(rval);
		if (CMI_ERROR(status))
		{
			CLOSEFILE_RESET(rval, rc);	/* resets "rval" to FD_INVALID */
			return;
		}

		/* grab a clb off of the free list */
		lnk = cmi_alloc_clb();
		if (!lnk || !tsk->acc || !tsk->acc(lnk) || !tsk->crq)
		{
			/* no point if the callbacks are not in place */
			cmi_free_clb(lnk);
			CLOSEFILE_RESET(rval, rc);	/* resets "rval" to FD_INVALID */
			return;
		}
		if (rval > tsk->max_fd)
			tsk->max_fd = rval;
		lnk->mun = rval;
		lnk->sta = CM_CLB_IDLE;
		lnk->peer = in;
		insqh(&lnk->cqe, &tsk->cqh);
		lnk->ntd = tsk;
		FD_SET(rval, &tsk->es);
		/* setup for callback processing */
		lnk->deferred_event = TRUE;
		lnk->deferred_reason = CMI_REASON_CONNECT;
		while ((-1 == (rval = ACCEPT(tsk->listen_fd, (struct sockaddr *)&in, (GTM_SOCKLEN_TYPE *)&sz))) && EINTR == errno)
			;
	}
}