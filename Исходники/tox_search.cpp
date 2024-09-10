ToxHexAddress ResolveToxAddressFromDns(const char *dnsQuery)
{
	ToxHexAddress address = ToxHexAddress::Empty();

	DNS_RECORDA *record = NULL;
	DNS_STATUS status = DnsQuery_A(dnsQuery, DNS_TYPE_TEXT, DNS_QUERY_STANDARD, NULL, (PDNS_RECORD*)&record, NULL);
	while (status == ERROR_SUCCESS && record)
	{
		DNS_TXT_DATAA *txt = &record->Data.Txt;
		if (record->wType == DNS_TYPE_TEXT && txt->dwStringCount)
		{
			address = ResolveToxAddressFromDnsRecordV1(txt->pStringArray[0]);
			break;
		}
		record = record->pNext;
	}
	DnsRecordListFree((PDNS_RECORD*)record, DnsFreeRecordList);

	return address;
}