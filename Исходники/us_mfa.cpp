void us_mfa::handle_ipv6(int dev, uint8_t *buf, uint16_t len) {
	ip6_hdr *hdr = (ip6_hdr *)buf;

	if (len < sizeof(ip6_hdr))
		return;

	if (hdr->ip6_hlim <= 1)
		return;

	if (!IN6_IS_ADDR_MULTICAST(&hdr->ip6_dst))
		return;

	if (IN6_IS_ADDR_MULTICAST(&hdr->ip6_src) ||
		IN6_IS_ADDR_UNSPECIFIED(&hdr->ip6_src) ||
		IN6_IS_ADDR_LINKLOCAL(&hdr->ip6_src))
		return;

	/*
	 * Silently drop packets with scope reserved, interface-local or link-local.

	 * RFC 4291, Section 2.7.
	 * Nodes must not originate a packet to a multicast address whose scope
	 * field contains the reserved value 0; if such a packet is received, it
	 * must be silently dropped.
	 */
	if ((hdr->ip6_dst.s6_addr[1] & 0xc) == 0)
		return;

	/* Do we have a Hop by Hop header? */
	if (hdr->ip6_nxt == 0) {
		int spaceLeft = (((const ip6_ext *)(hdr + 1))->ip6e_len + 1) * 8;

		if (len < (sizeof(ip6_hdr) + spaceLeft))
			return;

		const uint8_t *ptr = buf + sizeof(ip6_hdr) + 2;

		while (spaceLeft > 0) {
			if (ptr[0] == 0) {
				/* Pad1 */
				spaceLeft--;
			} else {
				spaceLeft -= ptr[1] + 2;
				if (spaceLeft < 0) {
					/* Badly encoded HbH, discard packet */
					return;
				}

				if (ptr[0] != 1) {
					/* not PadN, check top-order 2 bits */

					switch (ptr[0] >> 6) {
					case 0:
						// skip option
						break;

					case 1:
						// discard packet
						return;

					case 2:
					case 3:
						// We handle 2 same as 3 as all of our destinations are
						// multicast

						// XXX send icmp parameter problem, code 2 to the source

						return;
					}
				}
			}
		}
	}