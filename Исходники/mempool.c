{
	int ret;
	int i;

	__m128i template;	/* 256-bit write was worse... */
	__m128i rxdesc_fields;

	struct rte_mbuf tmp;
	/* DPDK 2.1 specific
	 * packet_type 0 (32 bits)
	 * pkt_len len (32 bits)
	 * data_len len (16 bits)
	 * vlan_tci 0 (16 bits)
	 * rss 0 (32 bits)
	 */
	rxdesc_fields = _mm_setr_epi32(0, len, len, 0);

	ret = rte_mempool_get_bulk(current_pframe_pool(),
			(void**)array, cnt);
	if (ret != 0) {
		return ret;
	}

	template = *((__m128i*)&current_template()->buf_len);

	if (cnt & 1) {
		array[cnt] = &tmp;
	}

	/* 4 at a time didn't help */
	for (i = 0; i < cnt; i+=2) {