int __cdecl main(void)
{
    LPWSTR                        pwszServer           = NULL;         // Server IP Address, a value of NULL signifies the current server (where program is executed)
    LPWSTR                        pwszRelationshipName = L"test";      // Relationship name
    LPDHCP_FAILOVER_RELATIONSHIP  pRelationship        = NULL;         // Relationship structure
    DWORD                         dwError              = ERROR_SUCCESS;// Variable to hold error code
    DWORD                         dwFlags              = 0;            // Flags to reflect which all fields are getting modified

    dwError = DhcpV4FailoverGetRelationship(
        pwszServer,           // Server IP Address
        pwszRelationshipName, // Relationship name
        &pRelationship        // Relationship structure (LPDHCP_FAILOVER_RELATIONSHIP)
        );
    if( ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpV4FailoverGetRelationship failed with Error = %d\n",dwError);
        goto cleanup;
    }

    pRelationship->Mode=HotStandby;  // Failover mode
    pRelationship->Mclt=0xe20;       // 3616 seconds
    pRelationship->SafePeriod=0x300; // 768 seconds
    pRelationship->Percentage=0x46;  //70 %
    
    dwFlags |= MODE | SAFEPERIOD | MCLT | PERCENTAGE; // mode, safeperiod, mclt and percentage field needs to be modified
    dwError = DhcpV4FailoverSetRelationship(
                        pwszServer,    // Server IP Address
                        dwFlags,       // Flags to reflect which all fields are getting modified
                        pRelationship  // Relationship structure from which values to be modified will be picked
                        );
    if( ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpV4FailoverSetRelationship failed with Error = %d\n",dwError);
    }
    FreeRelationshipMemory(pRelationship);
cleanup:
    return 0;
}