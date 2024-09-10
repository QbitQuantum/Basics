static enum req_fsm_nxt
cnt_deliver(struct worker *wrk, struct req *req)
{
	struct busyobj *bo;

	CHECK_OBJ_NOTNULL(wrk, WORKER_MAGIC);
	CHECK_OBJ_NOTNULL(req, REQ_MAGIC);
	CHECK_OBJ_NOTNULL(req->objcore, OBJCORE_MAGIC);
	CHECK_OBJ_NOTNULL(req->objcore->objhead, OBJHEAD_MAGIC);
	CHECK_OBJ_NOTNULL(req->vcl, VCL_CONF_MAGIC);
	assert(WRW_IsReleased(wrk));

	assert(req->objcore->refcnt > 0);

	if (req->objcore->exp_flags & OC_EF_EXP)
		EXP_Touch(req->objcore, req->t_prev);

	HTTP_Setup(req->resp, req->ws, req->vsl, SLT_RespMethod);
	AZ(HTTP_Decode(req->resp,
	    ObjGetattr(req->wrk, req->objcore, OA_HEADERS, NULL)));
	http_ForceField(req->resp, HTTP_HDR_PROTO, "HTTP/1.1");

	if (req->wrk->stats->cache_hit)
		http_PrintfHeader(req->resp,
		    "X-Varnish: %u %u", VXID(req->vsl->wid),
		    ObjGetXID(wrk, req->objcore));
	else
		http_PrintfHeader(req->resp,
		    "X-Varnish: %u", VXID(req->vsl->wid));

	/* We base Age calculation upon the last timestamp taken during
	   client request processing. This gives some inaccuracy, but
	   since Age is only full second resolution that shouldn't
	   matter. (Last request timestamp could be a Start timestamp
	   taken before the object entered into cache leading to negative
	   age. Truncate to zero in that case).
	*/
	http_PrintfHeader(req->resp, "Age: %.0f",
	    fmax(0., req->t_prev - req->objcore->exp.t_origin));

	http_SetHeader(req->resp, "Via: 1.1 varnish-v4");

	if (cache_param->http_gzip_support &&
	    ObjCheckFlag(req->wrk, req->objcore, OF_GZIPED) &&
	    !RFC2616_Req_Gzip(req->http))
		RFC2616_Weaken_Etag(req->resp);

	VCL_deliver_method(req->vcl, wrk, req, NULL, req->http->ws);
	VSLb_ts_req(req, "Process", W_TIM_real(wrk));

	/* Stop the insanity before it turns "Hotel California" on us */
	if (req->restarts >= cache_param->max_restarts)
		wrk->handling = VCL_RET_DELIVER;

	if (wrk->handling != VCL_RET_DELIVER) {
		assert(req->objcore == req->objcore);
		(void)HSH_DerefObjCore(wrk, &req->objcore);
		http_Teardown(req->resp);

		switch (wrk->handling) {
		case VCL_RET_RESTART:
			req->req_step = R_STP_RESTART;
			break;
		case VCL_RET_SYNTH:
			req->req_step = R_STP_SYNTH;
			break;
		default:
			INCOMPL();
		}

		return (REQ_FSM_MORE);
	}

	assert(wrk->handling == VCL_RET_DELIVER);

	if (!(req->objcore->flags & OC_F_PASS)
	    && req->esi_level == 0
	    && http_IsStatus(req->resp, 200)
	    && req->http->conds && RFC2616_Do_Cond(req)) {
		http_PutResponse(req->resp, "HTTP/1.1", 304, NULL);
		req->wantbody = 0;
	}

	/* Grab a ref to the bo if there is one, and hand it down */
	bo = HSH_RefBusy(req->objcore);
	if (bo != NULL && req->esi_level == 0 && bo->state == BOS_FINISHED)
		VBO_DerefBusyObj(wrk, &bo);
	V1D_Deliver(req, bo);
	if (bo != NULL)
		VBO_DerefBusyObj(wrk, &bo);

	VSLb_ts_req(req, "Resp", W_TIM_real(wrk));

	if (http_HdrIs(req->resp, H_Connection, "close"))
		req->doclose = SC_RESP_CLOSE;

	if (req->objcore->flags & OC_F_PASS) {
		/*
		 * No point in saving the body if it is hit-for-pass,
		 * but we can't yank it until the fetching thread has
		 * finished/abandoned also.
		 */
		while (req->objcore->busyobj != NULL)
			(void)usleep(100000);
		ObjSlim(wrk, req->objcore);
	}

	assert(WRW_IsReleased(wrk));
	(void)HSH_DerefObjCore(wrk, &req->objcore);
	http_Teardown(req->resp);
	return (REQ_FSM_DONE);
}