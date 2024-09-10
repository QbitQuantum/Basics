static inline void
fm10k_desc_to_olflags_v(__m128i descs[4], struct rte_mbuf **rx_pkts)
{
	__m128i ptype0, ptype1, vtag0, vtag1, eflag0, eflag1, cksumflag;
	union {
		uint16_t e[4];
		uint64_t dword;
	} vol;

	const __m128i pkttype_msk = _mm_set_epi16(
			0x0000, 0x0000, 0x0000, 0x0000,
			PKT_RX_VLAN_PKT, PKT_RX_VLAN_PKT,
			PKT_RX_VLAN_PKT, PKT_RX_VLAN_PKT);

	/* mask everything except rss type */
	const __m128i rsstype_msk = _mm_set_epi16(
			0x0000, 0x0000, 0x0000, 0x0000,
			0x000F, 0x000F, 0x000F, 0x000F);

	/* mask for HBO and RXE flag flags */
	const __m128i rxe_msk = _mm_set_epi16(
			0x0000, 0x0000, 0x0000, 0x0000,
			0x0001, 0x0001, 0x0001, 0x0001);

	const __m128i l3l4cksum_flag = _mm_set_epi8(0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			PKT_RX_IP_CKSUM_BAD | PKT_RX_L4_CKSUM_BAD,
			PKT_RX_IP_CKSUM_BAD, PKT_RX_L4_CKSUM_BAD, 0);

	const __m128i rxe_flag = _mm_set_epi8(0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, PKT_RX_RECIP_ERR, 0);

	/* map rss type to rss hash flag */
	const __m128i rss_flags = _mm_set_epi8(0, 0, 0, 0,
			0, 0, 0, PKT_RX_RSS_HASH,
			PKT_RX_RSS_HASH, 0, PKT_RX_RSS_HASH, 0,
			PKT_RX_RSS_HASH, PKT_RX_RSS_HASH, PKT_RX_RSS_HASH, 0);

	/* Calculate RSS_hash and Vlan fields */
	ptype0 = _mm_unpacklo_epi16(descs[0], descs[1]);
	ptype1 = _mm_unpacklo_epi16(descs[2], descs[3]);
	vtag0 = _mm_unpackhi_epi16(descs[0], descs[1]);
	vtag1 = _mm_unpackhi_epi16(descs[2], descs[3]);

	ptype0 = _mm_unpacklo_epi32(ptype0, ptype1);
	ptype0 = _mm_and_si128(ptype0, rsstype_msk);
	ptype0 = _mm_shuffle_epi8(rss_flags, ptype0);

	vtag1 = _mm_unpacklo_epi32(vtag0, vtag1);
	eflag0 = vtag1;
	cksumflag = vtag1;
	vtag1 = _mm_srli_epi16(vtag1, VP_SHIFT);
	vtag1 = _mm_and_si128(vtag1, pkttype_msk);

	vtag1 = _mm_or_si128(ptype0, vtag1);

	/* Process err flags, simply set RECIP_ERR bit if HBO/IXE is set */
	eflag1 = _mm_srli_epi16(eflag0, RXEFLAG_SHIFT);
	eflag0 = _mm_srli_epi16(eflag0, HBOFLAG_SHIFT);
	eflag0 = _mm_or_si128(eflag0, eflag1);
	eflag0 = _mm_and_si128(eflag0, rxe_msk);
	eflag0 = _mm_shuffle_epi8(rxe_flag, eflag0);

	vtag1 = _mm_or_si128(eflag0, vtag1);

	/* Process L4/L3 checksum error flags */
	cksumflag = _mm_srli_epi16(cksumflag, L3L4EFLAG_SHIFT);
	cksumflag = _mm_shuffle_epi8(l3l4cksum_flag, cksumflag);
	vtag1 = _mm_or_si128(cksumflag, vtag1);

	vol.dword = _mm_cvtsi128_si64(vtag1);

	rx_pkts[0]->ol_flags = vol.e[0];
	rx_pkts[1]->ol_flags = vol.e[1];
	rx_pkts[2]->ol_flags = vol.e[2];
	rx_pkts[3]->ol_flags = vol.e[3];
}