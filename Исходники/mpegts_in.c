static void M2TS_FlushRequested(M2TSIn *m2ts)
{
	u32 i, j, req_prog_count, count, prog_id, found;

	gf_mx_p(m2ts->mx);

	found = 0;
	count = gf_list_count(m2ts->ts->requested_pids);
	for (i=0; i<count; i++) {
		M2TSIn_Prog *req_pid = gf_list_get(m2ts->ts->requested_pids, i);
		GF_M2TS_ES *es = m2ts->ts->ess[req_pid->pid];
		if (es==NULL) continue;

		/*move to skip mode for all PES until asked for playback*/
		if (!(es->flags & GF_M2TS_ES_IS_SECTION) && !es->user)
			gf_m2ts_set_pes_framing((GF_M2TS_PES *)es, GF_M2TS_PES_FRAMING_SKIP);
		MP2TS_DeclareStream(m2ts, (GF_M2TS_PES *)es, NULL, 0);
		gf_list_rem(m2ts->ts->requested_pids, i);
		gf_free(req_pid);
		i--;
		count--;
		found++;
	}
	req_prog_count = gf_list_count(m2ts->ts->requested_progs);
	for (i = 0; i < req_prog_count; i++) {
		M2TSIn_Prog *req_prog = gf_list_get(m2ts->ts->requested_progs, i);
		prog_id = atoi(req_prog->fragment);
		count = gf_list_count(m2ts->ts->SDTs);
		for (j=0; j<count; j++) {
			GF_M2TS_SDT *sdt = gf_list_get(m2ts->ts->SDTs, j);
			if (!stricmp((const char *) sdt->service, req_prog->fragment)) req_prog->id = sdt->service_id;
			else if (sdt->service_id==prog_id)  req_prog->id = sdt->service_id;
		}
		if (req_prog->id) {
			GF_M2TS_Program *ts_prog;
			count = gf_list_count(m2ts->ts->programs);
			for (j=0; j<count; j++) {
				ts_prog = gf_list_get(m2ts->ts->programs, j);
				if (ts_prog->number==req_prog->id) {
					MP2TS_SetupProgram(m2ts, ts_prog, 0, 0);
					found++;
					gf_free(req_prog->fragment);
					gf_free(req_prog);
					gf_list_rem(m2ts->ts->requested_progs, i);
					req_prog_count--;
					i--;
					break;
				}
			}
		}
	}

	if (m2ts->epg_requested) {
		if (!m2ts->has_eit) {
			GF_ObjectDescriptor *od = M2TS_GenerateEPG_OD(m2ts);
			/*declare but don't regenerate scene*/
			gf_term_add_media(m2ts->service, (GF_Descriptor*)od, 0);
			m2ts->has_eit = 1;
		}
	} else {
		/*force scene regeneration only when EPG is not requested*/
		if (found)
			gf_term_add_media(m2ts->service, NULL, 0);
	}

	gf_mx_v(m2ts->mx);
}