// Search an entry
IPTABLES_ENTRY *SearchIpTables(IPTABLES_STATE *s, char *chain, IP *src_ip, IP *dest_ip, UINT mark)
{
	char ip_str1[64];
	char ip_str2[64];
	char mark_str1[64];
	char mark_str2[64];
	UINT i;
	if (s == NULL || chain == NULL || src_ip == NULL || dest_ip == NULL || mark == 0)
	{
		return NULL;
	}

	IPToStr(ip_str1, sizeof(ip_str1), src_ip);
	IPToStr(ip_str2, sizeof(ip_str2), dest_ip);
	ToStr(mark_str1, mark);
	Format(mark_str2, sizeof(mark_str2), "%x", mark);

	for (i = 0;i < LIST_NUM(s->EntryList);i++)
	{
		IPTABLES_ENTRY *e = LIST_DATA(s->EntryList, i);

		if (StrCmpi(e->Chain, chain) == 0)
		{
			if (InStr(e->ConditionAndArgs, ip_str1) &&
				InStr(e->ConditionAndArgs, ip_str2) &&
				(InStr(e->ConditionAndArgs, mark_str1) || InStr(e->ConditionAndArgs, mark_str2)))
			{
				return e;
			}
		}
	}

	return NULL;
}