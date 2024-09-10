/******************************************************************************
 * DnsQuery_A           [DNSAPI.@]
 *
 */
DNS_STATUS WINAPI DnsQuery_A( PCSTR name, WORD type, DWORD options, PVOID servers,
                              PDNS_RECORDA *result, PVOID *reserved )
{
    WCHAR *nameW;
    DNS_RECORDW *resultW;
    DNS_STATUS status;

    TRACE( "(%s,%s,0x%08x,%p,%p,%p)\n", debugstr_a(name), dns_type_to_str( type ),
           options, servers, result, reserved );

    if (!name || !result)
        return ERROR_INVALID_PARAMETER;

    nameW = dns_strdup_aw( name );
    if (!nameW) return ERROR_NOT_ENOUGH_MEMORY;

    status = DnsQuery_W( nameW, type, options, servers, &resultW, reserved ); 

    if (status == ERROR_SUCCESS)
    {
        *result = (DNS_RECORDA *)DnsRecordSetCopyEx(
             (DNS_RECORD *)resultW, DnsCharSetUnicode, DnsCharSetAnsi );

        if (!*result) status = ERROR_NOT_ENOUGH_MEMORY;
        DnsRecordListFree( (DNS_RECORD *)resultW, DnsFreeRecordList );
    }

    dns_free( nameW );
    return status;
}