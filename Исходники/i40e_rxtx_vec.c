static inline void
desc_to_olflags_v(__m128i descs[4], struct rte_mbuf **rx_pkts)
{
	__m128i vlan0, vlan1, rss;
	union {
		uint16_t e[4];
		uint64_t dword;
	} vol;

	/* mask everything except rss and vlan flags
	*bit2 is for vlan tag, bits 13:12 for rss
	*/
	const __m128i rss_vlan_msk = _mm_set_epi16(
			0x0000, 0x0000, 0x0000, 0x0000,
			0x3004, 0x3004, 0x3004, 0x3004);

	/* map rss and vlan type to rss hash and vlan flag */
	const __m128i vlan_flags = _mm_set_epi8(0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, PKT_RX_VLAN_PKT,
			0, 0, 0, 0);

	const __m128i rss_flags = _mm_set_epi8(0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			PKT_RX_FDIR, 0, PKT_RX_RSS_HASH, 0);

	vlan0 = _mm_unpackhi_epi16(descs[0], descs[1]);
	vlan1 = _mm_unpackhi_epi16(descs[2], descs[3]);
	vlan0 = _mm_unpacklo_epi32(vlan0, vlan1);

	vlan1 = _mm_and_si128(vlan0, rss_vlan_msk);
	vlan0 = _mm_shuffle_epi8(vlan_flags, vlan1);

	rss = _mm_srli_epi16(vlan1, 12);
	rss = _mm_shuffle_epi8(rss_flags, rss);

	vlan0 = _mm_or_si128(vlan0, rss);
	vol.dword = _mm_cvtsi128_si64(vlan0);

	rx_pkts[0]->ol_flags = vol.e[0];
	rx_pkts[1]->ol_flags = vol.e[1];
	rx_pkts[2]->ol_flags = vol.e[2];
	rx_pkts[3]->ol_flags = vol.e[3];
}