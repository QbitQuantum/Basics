int __cdecl main(void)
{
    LPDHCP_POLICY       pPolicy                    = NULL;                 // Policy structure
    DWORD               dwError                    = ERROR_SUCCESS;        // It stores the error code
    DWORD               dwExprIdx                  = 0;                    // Expression Index
    DWORD               dwOptionId                 = OPTION_USER_CLASS;    // Option ID for UserClass
    DWORD               dwSubOptionId              = 0;                    // Sub Option ID for UserClass
    DWORD               dwConditionIdx             = 0;                    // Condition index which will be returned from DhcpHlprAddV4PolicyCondition
    DWORD               dwBytesLength              = 0;                    // Number of bytes of user data in pUserClassCondValueInBytes
    LPBYTE              pUserClassCondValueInBytes = NULL;                 // Bytes containing condition value (user class based in the current example)
    DHCP_IP_ADDRESS     dwSubnet                   = 0xa000000;            // Subnet Address (10.0.0.0)
    LPWSTR              pwszName                   = L"testPolicy";        //Name of the policy to be created
    LPWSTR              pwszDescription            = L"PolicyDescription"; // Description of the policy to be created
    char*               szUserClassConditionValue  = {"RRAS.Microsoft"};   // Default Routing and Remote Access Class
    DHCP_POL_LOGIC_OPER policyOperator             = DhcpLogicalOr;        // Root operator for the conditions and expressions
    DHCP_POL_ATTR_TYPE  policyAttrType             = DhcpAttrOption;       // Policy attribute type
    DHCP_POL_COMPARATOR conditionOper              = DhcpCompEqual;        // Condition operator
    DHCP_IP_RANGE       range                      = {0};                  // Variable to hold range values
    DWORD               dwStartAddress             = 0xa00000a;            //(10.0.0.10) Start Address of the range
    DWORD               dwEndAddress               = 0xa000032;            //(10.0.0.50) End Address of the range

    range.StartAddress = dwStartAddress;
    range.EndAddress   = dwEndAddress;


    // Invokes helper API to create/fill policy structure.
    dwError=DhcpHlprCreateV4Policy(
        pwszName,        // Policy Name
        (dwSubnet == 0), // fGloabalPolicy, if scope is zero, this means it is a global policy else it is for a specific scope
        dwSubnet,        // Scope
        0,               // Processing order
        policyOperator,  // Logical operator, possible values are: DhcpLogicalOr, DhcpLogicalAnd
        pwszDescription, // Policy description
        TRUE,            // Policy active or not
        &pPolicy         // This is the actual structure that holds the policy
    );

    if(ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpHlprCreateV4Policy failed with Error = %d\n", dwError);
        goto cleanup;
    }

    // Fill in pUserClassCondValueInBytes and dwBytesLength
    dwBytesLength = (DWORD)strlen(szUserClassConditionValue);
    pUserClassCondValueInBytes = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesLength);
    if(NULL == pUserClassCondValueInBytes)
    {
        wprintf(L"Not Enough memory, HeapAllocFailed !!\n");
        goto cleanup;
    }
    // Copies the bytes for condition values from pUserClassCondValueInBytes
    memcpy(pUserClassCondValueInBytes, szUserClassConditionValue, dwBytesLength);

    // Invokes helper API to create/fill the structure for adding conditions for the policy.
    // The condition in this case is "user class" equals "Default Routing and Remote Access Class"
    dwError = DhcpHlprAddV4PolicyCondition(
        pPolicy,                    // Policy where conditions need to be added
        dwExprIdx,                  // Parent expression index
        policyAttrType,             // Policy attribute type, possible values can be: DhcpAttrHWAddr, DhcpAttrOption and DhcpAttrSubOption
        dwOptionId,                 // Option ID
        dwSubOptionId,              // Sub Option ID
        NULL,                       // Vendor Name
        conditionOper,              // Policy comparator operator
        pUserClassCondValueInBytes, // Condition values in bytes
        dwBytesLength,              // Number of bytes in the condition value
        &dwConditionIdx             // Condition index
    );
    if(ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpHlprAddV4PolicyCondition failed with Error = %d\n", dwError);
        goto cleanup;
    }
    // Helper class for adding policy ip range is invoked from below.
    dwError = DhcpHlprAddV4PolicyRange(pPolicy,&range);
    if(ERROR_SUCCESS != dwError)
    {
        wprintf(L"DhcpHlprAddV4PolicyRange failed with Error = %d\n",dwError);
    }
cleanup:

    // Frees the variable holding the condition values in bytes
    if(NULL != pUserClassCondValueInBytes)
    {
        HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pUserClassCondValueInBytes);
        pUserClassCondValueInBytes = NULL;
    }

    // Frees the variable holding the policy.
    if(NULL != pPolicy)
    {
        DhcpHlprFreeV4Policy(pPolicy);
    }

    return 0;
}