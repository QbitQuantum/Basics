/**
 * Set device IP address
 * @param ip New IP address
 * @return -1 if it failed, 0 on success
 */
static int ti_set_ip_cygwin(struct tif *ti, struct in_addr *ip)
{
	struct tip_cygwin *priv = ti_priv(ti);
	ULONG ctx, inst;
	IP_ADAPTER_INFO ai[16];
	DWORD len = sizeof(ai);
	PIP_ADAPTER_INFO p;
	PIP_ADDR_STRING ips;

	if (GetAdaptersInfo(ai, &len) != ERROR_SUCCESS)
		return -1;

	p = ai;
	while (p) {
		if (strcmp(priv->tc_guid, p->AdapterName) != 0) {
			p = p->Next;
			continue;
		}

		/* delete ips */
		ips = &p->IpAddressList;
		while (ips) {
			DeleteIPAddress(ips->Context);
			ips = ips->Next;
		}

		/* add ip */
		if (AddIPAddress(ip->s_addr, htonl(0xffffff00),
			 p->Index, &ctx, &inst) != NO_ERROR)
			return -1;

		break;
	}

	return 0;
}