int __cdecl main(void)
{
    LPDHCP_FAILOVER_RELATIONSHIP pRelationShip        = NULL;          // Failover relationship
    LPWSTR                       pwszServer           = NULL;          // Server IP Address
    LPWSTR                       pwszRelationshipName = L"test";       // Relationship name to be fetched
    DWORD                        dwError              = ERROR_SUCCESS; // Variable to hold error code
    dwError = DhcpV4FailoverGetRelationship(
                        pwszServer,           // Server IP Address, if NULL, reflects the current server (where the program is executed)
                        pwszRelationshipName, // Relationship name
                        &pRelationShip        // Failover relationship
                        );
    if( ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpV4FailoverGetRelationship failed with Error = %d\n",dwError);
    }
    FreeRelationshipMemory(pRelationShip);
    return 0;
}