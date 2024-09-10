int l2_packet_send(struct l2_packet_data *l2, const u8 *dst_addr, u16 proto,
		   const u8 *buf, size_t len)
{
	BOOL res;
	DWORD written;
	struct l2_ethhdr *eth;
#ifndef _WIN32_WCE
	OVERLAPPED overlapped;
#endif /* _WIN32_WCE */
	OVERLAPPED *o;

	if (l2 == NULL)
		return -1;

#ifdef _WIN32_WCE
	o = NULL;
#else /* _WIN32_WCE */
	os_memset(&overlapped, 0, sizeof(overlapped));
	o = &overlapped;
#endif /* _WIN32_WCE */

	if (l2->l2_hdr) {
		res = WriteFile(driver_ndis_get_ndisuio_handle(), buf, len,
				&written, o);
	} else {
		size_t mlen = sizeof(*eth) + len;
		eth = os_malloc(mlen);
		if (eth == NULL)
			return -1;

		os_memcpy(eth->h_dest, dst_addr, ETH_ALEN);
		os_memcpy(eth->h_source, l2->own_addr, ETH_ALEN);
		eth->h_proto = htons(proto);
		os_memcpy(eth + 1, buf, len);
		res = WriteFile(driver_ndis_get_ndisuio_handle(), eth, mlen,
				&written, o);
		os_free(eth);
	}

	if (!res) {
		DWORD err = GetLastError();
#ifndef _WIN32_WCE
		if (err == ERROR_IO_PENDING) {
			wpa_printf(MSG_DEBUG, "L2(NDISUIO): Wait for pending "
				   "write to complete");
			res = GetOverlappedResult(
				driver_ndis_get_ndisuio_handle(), &overlapped,
				&written, TRUE);
			if (!res) {
				wpa_printf(MSG_DEBUG, "L2(NDISUIO): "
					   "GetOverlappedResult failed: %d",
					   (int) GetLastError());
				return -1;
			}
			return 0;
		}
#endif /* _WIN32_WCE */
		wpa_printf(MSG_DEBUG, "L2(NDISUIO): WriteFile failed: %d",
			   (int) GetLastError());
		return -1;
	}

	return 0;
}