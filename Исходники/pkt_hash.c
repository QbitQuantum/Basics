uint8_t isTCP(unsigned char *buf)
{
	TRACE_PKTHASH_FUNC_START();
	uint8_t rc = 0;
	struct ethhdr *ethh = (struct ethhdr *)buf;

	switch (NTOHS(ethh->h_proto)) {
	case ETH_P_IP:
		rc = decode_ip_n_hash((struct iphdr *)(ethh + 1));
		break;
	case ETH_P_IPV6:
		rc = decode_ipv6_n_hash((struct ipv6hdr *)(ethh + 1));
		break;
	case ETH_P_8021Q:
		rc = decode_vlan_n_hash(ethh);
		break;
	default:
		break;
	}	
	TRACE_PKTHASH_FUNC_END();
	return rc;
}