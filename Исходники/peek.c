static void
peek_report(const struct peak_packet *packet, const struct peak_track *flow,
    const timeslice_t *timer)
{
	unsigned int i;

	for (i = 0; i < use_count; ++i) {
		if (i) {
			pout(", ");
		}

		switch (use_print[i]) {
		case USE_APP:
			pout("app: %s",
			    peak_li_name(peak_li_merge(flow->li)));
			break;
		case USE_APP_LEN:
			pout("app_len: %hu", packet->app_len);
			break;
		case USE_FLOW:
			pout("flow: %llu", (unsigned long long)flow->id);
			break;
		case USE_IP_LEN:
			pout("ip_len: %hu", packet->net_len);
			break;
		case USE_IP_TYPE:
			pout("ip_type: %hhu", packet->net_type);
			break;
		case USE_SRC:
			if (packet->net_family == AF_INET6 &&
			    packet->flow_sport) {
				pout("src: [%s]%s",
				    netprint(&packet->net_saddr),
				    portprint(packet->flow_sport));
			} else {
				pout("src: %s%s",
				    netprint(&packet->net_saddr),
				    portprint(packet->flow_sport));
			}
			break;
		case USE_DST:
			if (packet->net_family == AF_INET6 &&
			    packet->flow_dport) {
				pout("dst: [%s]%s",
				    netprint(&packet->net_daddr),
				    portprint(packet->flow_dport));
			} else {
				pout("dst: %s%s",
				    netprint(&packet->net_daddr),
				    portprint(packet->flow_dport));
			}
			break;
		case USE_TIME: {
			char tsbuf[40];
			pout("time: %s.%06ld", strftime(tsbuf, sizeof(tsbuf),
			    OUTPUT_TIME, &timer->gmt) ? tsbuf : "????",
			    timer->tv.tv_usec);
			break;
		}
		default:
			break;
		}
	}

	pout("\n");
}