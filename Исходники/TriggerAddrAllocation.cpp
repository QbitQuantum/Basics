int __cdecl main(void)
{
    DWORD  dwError              = ERROR_SUCCESS;
    LPWSTR pwszServerName       = NULL;
    LPWSTR pwszRelationshipName = L"test";

    // This triggers the address allocation
    dwError = DhcpV4FailoverTriggerAddrAllocation(
                        pwszServerName,      // Server IP Address, a value of NULL signifies the current server (where program is executed)
                        pwszRelationshipName // Relationship name
                        );
    if(ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpV4FailoverTriggerAddrAllocation failed with Error = %d\n",dwError);
    }
    return 0;
}