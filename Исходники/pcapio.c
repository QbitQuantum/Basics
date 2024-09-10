gboolean
libpcap_write_interface_statistics_block(FILE *fp,
                                         guint32 interface_id,
                                         pcap_t *pd,
                                         long *bytes_written,
                                         int *err)
{
	struct isb isb;
#ifdef _WIN32
	FILETIME now;
#else
	struct timeval now;
#endif
	struct option option;
	struct pcap_stat stats;
	guint32 block_total_length;
	guint64 timestamp;
	guint64 counter;
	gboolean stats_retrieved;
	
#ifdef _WIN32
	/*
	 * Current time, represented as 100-nanosecond intervals since
	 * January 1, 1601, 00:00:00 UTC.
	 *
	 * I think DWORD might be signed, so cast both parts of "now"
	 * to guint32 so that the sign bit doesn't get treated specially.
	 */
	GetSystemTimeAsFileTime(&now);
	timestamp = (((guint64)(guint32)now.dwHighDateTime) << 32) +
	            (guint32)now.dwLowDateTime;

	/*
	 * Convert to same thing but as 1-microsecond, i.e. 1000-nanosecond,
	 * intervals.
	 */
	timestamp /= 10;

	/*
	 * Subtract difference, in microseconds, between January 1, 1601
	 * 00:00:00 UTC and January 1, 1970, 00:00:00 UTC.
	 */
	timestamp -= G_GINT64_CONSTANT(11644473600000000U);
#else
	/*
	 * Current time, represented as seconds and microseconds since
	 * January 1, 1970, 00:00:00 UTC.
	 */
	gettimeofday(&now, NULL);

	/*
	 * Convert to delta in microseconds.
	 */
	timestamp = (guint64)(now.tv_sec) * 1000000 +
	            (guint64)(now.tv_usec);
#endif
	if (pcap_stats(pd, &stats) < 0) {
		stats_retrieved = FALSE;
		g_warning("pcap_stats() failed.");
	} else {
		stats_retrieved = TRUE;
	}
	block_total_length = sizeof(struct isb) +
	                     sizeof(guint32);
	if (stats_retrieved) {
		block_total_length += 3 * sizeof(struct option) + 2 * sizeof(guint64);
	}
	isb.block_type = INTERFACE_STATISTICS_BLOCK_TYPE;
	isb.block_total_length = block_total_length;
	isb.interface_id = interface_id;
	isb.timestamp_high = (guint32)((timestamp>>32) & 0xffffffff);
	isb.timestamp_low = (guint32)(timestamp & 0xffffffff);
	WRITE_DATA(fp, &isb, sizeof(struct isb), *bytes_written, err);
	if (stats_retrieved) {
		/* */
		option.type = ISB_IFRECV;
		option.value_length = sizeof(guint64);
		counter = stats.ps_recv;
		WRITE_DATA(fp, &option, sizeof(struct option), *bytes_written, err);
		WRITE_DATA(fp, &counter, sizeof(guint64), *bytes_written, err);
		/* */
		option.type = ISB_IFDROP;
		option.value_length = sizeof(guint64);
		counter = stats.ps_drop;
		WRITE_DATA(fp, &option, sizeof(struct option), *bytes_written, err);
		WRITE_DATA(fp, &counter, sizeof(guint64), *bytes_written, err);
		/* last option */
		option.type = OPT_ENDOFOPT;
		option.value_length = 0;
		WRITE_DATA(fp, &option, sizeof(struct option), *bytes_written, err);
	}
	WRITE_DATA(fp, &block_total_length, sizeof(guint32), *bytes_written, err);
	
	return TRUE;
}