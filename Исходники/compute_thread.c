inline static struct minmaxmean
calc_min_max_mean_gap(struct slist *list, int decim8, int rxtx)
{
	struct slist *ln;
	int32_t size = slist_size(list);
	int32_t gap_lengths[MAX_LIST_LEN] = { 0 };
	int32_t gap_idx = 0;
	int found_gap = 0;
	int32_t min_gap = decim8 + 1;
	int32_t max_gap = 0;
	int32_t sum_gap = 0;
	int32_t mean_gap = 0;

	assert(size >= decim8);
	assert(decim8 > 0);

	ln = slist_idx(list, size - decim8);
	for (int i = decim8; i > 0; i--) {
		struct sample *s = ln->s;
		if (((RX == rxtx) && (0 == s->rx_packets_delta)) ||
		    ((TX == rxtx) && (0 == s->tx_packets_delta))) {
			found_gap = 1;
			gap_lengths[gap_idx]++;
			max_gap = (max_gap > gap_lengths[gap_idx])
			              ? max_gap
			              : gap_lengths[gap_idx];
		} else if (found_gap) {
			found_gap = 0;
			gap_idx++;
		}
		ln = ln->next;
	}

	assert(gap_idx <= decim8);
	assert(max_gap <= decim8);

	for (int i = 0; i <= gap_idx; i++) {
		sum_gap += gap_lengths[i];
		if (min_gap > gap_lengths[i]) {
			min_gap = gap_lengths[i];
		}
	}
	assert(sum_gap <= decim8);
	assert((min_gap <= decim8) || (sum_gap == 0));

	/* gap is the last index into the gap_lengths, so +1 for count. */
	mean_gap = roundl((1000.0 * sum_gap) / (gap_idx + 1));
	assert(1000 * min_gap <= mean_gap);

	return (struct minmaxmean){min_gap, max_gap, mean_gap};
}