void
tcp_dooptions( struct tcpcb *tp, u_char *cp, int cnt,
	struct tcpiphdr *ti, int *ts_present,
	u_long *ts_val, u_long *ts_ecr)
{
	u_short mss;
	int opt, optlen;

	for (; cnt > 0; cnt -= optlen, cp += optlen) {
		opt = cp[0];
		if (opt == TCPOPT_EOL)
			break;
		if (opt == TCPOPT_NOP)
			optlen = 1;
		else {
			optlen = cp[1];
			if (optlen <= 0)
				break;
		}
		switch (opt) {

		default:
			continue;

		case TCPOPT_MAXSEG:
			if (optlen != TCPOLEN_MAXSEG)
				continue;
			if (!(ti->ti_flags & TH_SYN))
				continue;
			bcopy((char *) cp + 2, (char *) &mss, sizeof(mss));
			NTOHS(mss);
			tcp_mss(tp, mss);	// sets t_maxseg
			break;

		case TCPOPT_WINDOW:
			if (optlen != TCPOLEN_WINDOW)
				continue;
			if (!(ti->ti_flags & TH_SYN))
				continue;
			tp->t_flags |= TF_RCVD_SCALE;
			tp->requested_s_scale = min(cp[2], TCP_MAX_WINSHIFT);
			break;

		case TCPOPT_TIMESTAMP:
			if (optlen != TCPOLEN_TIMESTAMP)
				continue;
			*ts_present = 1;
			bcopy((char *)cp + 2, (char *) ts_val, sizeof(*ts_val));
			NTOHL(*ts_val);
			bcopy((char *)cp + 6, (char *) ts_ecr, sizeof(*ts_ecr));
			NTOHL(*ts_ecr);

			// A timestamp received in a SYN makes
			// it ok to send timestamp requests and replies.
			if (ti->ti_flags & TH_SYN) {
				tp->t_flags |= TF_RCVD_TSTMP;
				tp->ts_recent = *ts_val;
				tp->ts_recent_age = g_tcp_now;
			}
			break;
		}
	}
}