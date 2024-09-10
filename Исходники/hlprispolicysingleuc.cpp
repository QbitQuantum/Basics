int __cdecl main(void)
{
    LPDHCP_POLICY pPolicy    = NULL;          // Variable to hold the DHCP Policy structure
    LPWSTR        pwszServer = NULL;          //Server IP Address, NULL signifies current server (where the program is executed)
    DWORD         dwScope    = 0xa000000;     // Subnet Address (10.0.0.0)
    DWORD         dwError    = ERROR_SUCCESS; // Variable to hold error code
    LPWSTR        pwszName   = L"testPolicy"; // Policy Name
    BOOL          bIsUCBased = FALSE;
    dwError = DhcpV4GetPolicy(
                    pwszServer,     // Server IP Address, NULL signifies the current server (where the program is executed)
                    (dwScope == 0), // fGlobalPolicy, TRUE means a global policy, for a global policy SubnetAddress is 0.
                    dwScope,        // Subnet address, if it is a global policy, its value is 0
                    pwszName,       // Name of the policy
                    &pPolicy        // Policy structure obtained from the server
                    );
    if(ERROR_SUCCESS != dwError)
    {
        //DhcpV4GetPolicy returned error.
        wprintf(L"DhcpV4GetPolicy failed with error %d\n",dwError);
        goto cleanup;
    }
    // DhcpHlprIsV4PolicySingleUC returns true or false.
    // True means the policy contains single user class based conditions.
    // False means the policy in question doesnt contain just one user class based condition
    bIsUCBased = DhcpHlprIsV4PolicySingleUC(pPolicy);
    if(bIsUCBased)
        wprintf(L"Policy contains single user class based condition\n");
    else
        wprintf(L"Policy does not contain just one user class based condition\n");
    FreeDhcpPolicyMemory(pPolicy);
cleanup:
    return 0;
}