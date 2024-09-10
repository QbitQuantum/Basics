/**
* CreateGuid generates a global unique identifier. It calls the
* Win32 API function for doing this.
*/
OpcUa_Guid* OPCUA_DLLCALL OpcUa_P_Guid_Create(OpcUa_Guid* Guid)
{
#ifndef _GUID_CREATE_NOT_AVAILABLE
    if(UuidCreate((UUID*)Guid) != RPC_S_OK)
    {
        /* Error */
        Guid = OpcUa_Null;
        return OpcUa_Null;
    }

    /* Good */
    return Guid;
#else
    unsigned int *data = (unsigned int*)Guid;
    int chunks = 16 / sizeof(unsigned int);
    static const int intbits = sizeof(int)*8;
    static int randbits = 0;
    if (!randbits)
    {
        OpcUa_DateTime now;
        int max = RAND_MAX;
        do { ++randbits; } while ((max=max>>1));
        now = OpcUa_P_DateTime_UtcNow();
        srand(now.dwLowDateTime^now.dwHighDateTime);
        rand(); /* Skip first */
    }