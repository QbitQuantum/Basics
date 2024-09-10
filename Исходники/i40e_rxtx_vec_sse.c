static inline void
desc_to_ptype_v(__m128i descs[4], struct rte_mbuf **rx_pkts,
		uint32_t *ptype_tbl)
{
	__m128i ptype0 = _mm_unpackhi_epi64(descs[0], descs[1]);
	__m128i ptype1 = _mm_unpackhi_epi64(descs[2], descs[3]);

	ptype0 = _mm_srli_epi64(ptype0, 30);
	ptype1 = _mm_srli_epi64(ptype1, 30);

	rx_pkts[0]->packet_type = ptype_tbl[_mm_extract_epi8(ptype0, 0)];
	rx_pkts[1]->packet_type = ptype_tbl[_mm_extract_epi8(ptype0, 8)];
	rx_pkts[2]->packet_type = ptype_tbl[_mm_extract_epi8(ptype1, 0)];
	rx_pkts[3]->packet_type = ptype_tbl[_mm_extract_epi8(ptype1, 8)];
}