static void brip_print(const void *ip, const struct xt_entry_match *match,
		       int numeric)
{
	struct ebt_ip_info *info = (struct ebt_ip_info *)match->data;
	struct in_addr *addrp, *maskp;

	if (info->bitmask & EBT_IP_SOURCE) {
		printf("--ip-src ");
		if (info->invflags & EBT_IP_SOURCE)
			printf("! ");
		addrp = (struct in_addr *)&info->saddr;
		maskp = (struct in_addr *)&info->smsk;
		printf("%s%s ", xtables_ipaddr_to_numeric(addrp),
		       xtables_ipmask_to_numeric(maskp));
	}
	if (info->bitmask & EBT_IP_DEST) {
		printf("--ip-dst ");
		if (info->invflags & EBT_IP_DEST)
			printf("! ");
		addrp = (struct in_addr *)&info->daddr;
		maskp = (struct in_addr *)&info->dmsk;
		printf("%s%s ", xtables_ipaddr_to_numeric(addrp),
		       xtables_ipmask_to_numeric(maskp));
	}
	if (info->bitmask & EBT_IP_TOS) {
		printf("--ip-tos ");
		if (info->invflags & EBT_IP_TOS)
			printf("! ");
		printf("0x%02X ", info->tos);
	}
	if (info->bitmask & EBT_IP_PROTO) {
		struct protoent *pe;

		printf("--ip-proto ");
		if (info->invflags & EBT_IP_PROTO)
			printf("! ");
		pe = getprotobynumber(info->protocol);
		if (pe == NULL) {
			printf("%d ", info->protocol);
		} else {
			printf("%s ", pe->p_name);
		}
	}
	if (info->bitmask & EBT_IP_SPORT) {
		printf("--ip-sport ");
		if (info->invflags & EBT_IP_SPORT)
			printf("! ");
		print_port_range(info->sport);
	}
	if (info->bitmask & EBT_IP_DPORT) {
		printf("--ip-dport ");
		if (info->invflags & EBT_IP_DPORT)
			printf("! ");
		print_port_range(info->dport);
	}
}