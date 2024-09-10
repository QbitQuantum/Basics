/***********************************************************************
 *              GetComputerNameExW         (KERNEL32.@)
 */
BOOL WINAPI GetComputerNameExW( COMPUTER_NAME_FORMAT type, LPWSTR name, LPDWORD size )
{
    char buf[256];
    int len = sizeof(buf) - 1, ret;

    TRACE("%d, %p, %p\n", type, name, size);
    switch( type )
    {
    case ComputerNameNetBIOS:
    case ComputerNamePhysicalNetBIOS:
        ret = GetComputerNameW (name, size);
        if (!ret && GetLastError() == ERROR_BUFFER_OVERFLOW)
            SetLastError( ERROR_MORE_DATA );
        return ret;
    case ComputerNameDnsHostname:
    case ComputerNamePhysicalDnsHostname:
        ret = dns_hostname (buf, &len);
        break;
    case ComputerNameDnsDomain:
    case ComputerNamePhysicalDnsDomain:
        ret = dns_domainname (buf, &len);
        break;
    case ComputerNameDnsFullyQualified:
    case ComputerNamePhysicalDnsFullyQualified:
        ret = dns_fqdn (buf, &len);
        break;
    default:
        SetLastError (ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    if ( ret )
    {
        unsigned int lenW;

        TRACE ("-> %s (%d)\n", debugstr_a (buf), len);

        lenW = MultiByteToWideChar( CP_ACP, 0, buf, len, NULL, 0 );
        if ( *size < lenW + 1 )
        {
            *size = lenW + 1;
            SetLastError( ERROR_MORE_DATA );
            ret = FALSE;
        }
        else
        {
            MultiByteToWideChar( CP_ACP, 0, buf, len, name, lenW );
            name[lenW] = 0;
            *size = lenW;
            ret = TRUE;
        }
    }

    return ret;
}