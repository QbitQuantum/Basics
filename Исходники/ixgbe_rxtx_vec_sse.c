static inline void
desc_to_olflags_v(__m128i descs[4], uint8_t vlan_flags,
	struct rte_mbuf **rx_pkts)
{
	__m128i ptype0, ptype1, vtag0, vtag1, csum;
	union {
		uint16_t e[4];
		uint64_t dword;
	} vol;

	/* mask everything except rss type */
	const __m128i rsstype_msk = _mm_set_epi16(
			0x0000, 0x0000, 0x0000, 0x0000,
			0x000F, 0x000F, 0x000F, 0x000F);

	/* mask the lower byte of ol_flags */
	const __m128i ol_flags_msk = _mm_set_epi16(
			0x0000, 0x0000, 0x0000, 0x0000,
			0x00FF, 0x00FF, 0x00FF, 0x00FF);

	/* map rss type to rss hash flag */
	const __m128i rss_flags = _mm_set_epi8(PKT_RX_FDIR, 0, 0, 0,
			0, 0, 0, PKT_RX_RSS_HASH,
			PKT_RX_RSS_HASH, 0, PKT_RX_RSS_HASH, 0,
			PKT_RX_RSS_HASH, PKT_RX_RSS_HASH, PKT_RX_RSS_HASH, 0);

	/* mask everything except vlan present and l4/ip csum error */
	const __m128i vlan_csum_msk = _mm_set_epi16(
		(IXGBE_RXDADV_ERR_TCPE | IXGBE_RXDADV_ERR_IPE) >> 16,
		(IXGBE_RXDADV_ERR_TCPE | IXGBE_RXDADV_ERR_IPE) >> 16,
		(IXGBE_RXDADV_ERR_TCPE | IXGBE_RXDADV_ERR_IPE) >> 16,
		(IXGBE_RXDADV_ERR_TCPE | IXGBE_RXDADV_ERR_IPE) >> 16,
		IXGBE_RXD_STAT_VP, IXGBE_RXD_STAT_VP,
		IXGBE_RXD_STAT_VP, IXGBE_RXD_STAT_VP);
	/* map vlan present (0x8), IPE (0x2), L4E (0x1) to ol_flags */
	const __m128i vlan_csum_map_lo = _mm_set_epi8(
		0, 0, 0, 0,
		vlan_flags | PKT_RX_IP_CKSUM_BAD | PKT_RX_L4_CKSUM_BAD,
		vlan_flags | PKT_RX_IP_CKSUM_BAD,
		vlan_flags | PKT_RX_IP_CKSUM_GOOD | PKT_RX_L4_CKSUM_BAD,
		vlan_flags | PKT_RX_IP_CKSUM_GOOD,
		0, 0, 0, 0,
		PKT_RX_IP_CKSUM_BAD | PKT_RX_L4_CKSUM_BAD,
		PKT_RX_IP_CKSUM_BAD,
		PKT_RX_IP_CKSUM_GOOD | PKT_RX_L4_CKSUM_BAD,
		PKT_RX_IP_CKSUM_GOOD);

	const __m128i vlan_csum_map_hi = _mm_set_epi8(
		0, 0, 0, 0,
		0, PKT_RX_L4_CKSUM_GOOD >> sizeof(uint8_t), 0,
		PKT_RX_L4_CKSUM_GOOD >> sizeof(uint8_t),
		0, 0, 0, 0,
		0, PKT_RX_L4_CKSUM_GOOD >> sizeof(uint8_t), 0,
		PKT_RX_L4_CKSUM_GOOD >> sizeof(uint8_t));

	ptype0 = _mm_unpacklo_epi16(descs[0], descs[1]);
	ptype1 = _mm_unpacklo_epi16(descs[2], descs[3]);
	vtag0 = _mm_unpackhi_epi16(descs[0], descs[1]);
	vtag1 = _mm_unpackhi_epi16(descs[2], descs[3]);

	ptype0 = _mm_unpacklo_epi32(ptype0, ptype1);
	ptype0 = _mm_and_si128(ptype0, rsstype_msk);
	ptype0 = _mm_shuffle_epi8(rss_flags, ptype0);

	vtag1 = _mm_unpacklo_epi32(vtag0, vtag1);
	vtag1 = _mm_and_si128(vtag1, vlan_csum_msk);

	/* csum bits are in the most significant, to use shuffle we need to
	 * shift them. Change mask to 0xc000 to 0x0003.
	 */
	csum = _mm_srli_epi16(vtag1, 14);

	/* now or the most significant 64 bits containing the checksum
	 * flags with the vlan present flags.
	 */
	csum = _mm_srli_si128(csum, 8);
	vtag1 = _mm_or_si128(csum, vtag1);

	/* convert VP, IPE, L4E to ol_flags */
	vtag0 = _mm_shuffle_epi8(vlan_csum_map_hi, vtag1);
	vtag0 = _mm_slli_epi16(vtag0, sizeof(uint8_t));

	vtag1 = _mm_shuffle_epi8(vlan_csum_map_lo, vtag1);
	vtag1 = _mm_and_si128(vtag1, ol_flags_msk);
	vtag1 = _mm_or_si128(vtag0, vtag1);

	vtag1 = _mm_or_si128(ptype0, vtag1);
	vol.dword = _mm_cvtsi128_si64(vtag1);

	rx_pkts[0]->ol_flags = vol.e[0];
	rx_pkts[1]->ol_flags = vol.e[1];
	rx_pkts[2]->ol_flags = vol.e[2];
	rx_pkts[3]->ol_flags = vol.e[3];
}