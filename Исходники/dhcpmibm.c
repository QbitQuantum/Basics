BOOL SnmpExtensionTrap(
    OUT AsnObjectIdentifier *enterprise,
    OUT AsnInteger          *genericTrap,
    OUT AsnInteger          *specificTrap,
    OUT AsnTimeticks        *timeStamp,
    OUT RFC1157VarBindList  *variableBindings)
    {
    // The body of this routine is an extremely simple example/simulation of
    // the trap functionality.  A real implementation will be more complex.


    // The following define data inserted into the trap below.  The Lan Manager
    // bytesAvailAlert from the Lan Manager Alerts-2 MIB is generated with an
    // empty variable bindings list.

    static UINT OidList[]  = { 1, 3, 6, 1, 4, 1, 311, 2 };
    static UINT OidListLen = 8;


    // The following variable is used for the simulation, it allows a single
    // trap to be generated and then causes FALSE to be returned indicating
    // no more traps.

    static whichTime = 0;


    // The following if/else support the simulation.

    if (whichTime == 0)
        {
        whichTime = 1;    // Supports the simulation.


        // Communicate the trap data to the Extendible Agent.

        enterprise->idLength = OidListLen;
        enterprise->ids = (UINT *)SnmpUtilMemAlloc(sizeof(UINT) * OidListLen);
        memcpy(enterprise->ids, OidList, sizeof(UINT) * OidListLen);

        *genericTrap      = SNMP_GENERICTRAP_ENTERSPECIFIC;

        *specificTrap     = 1;                    // the bytesAvailAlert trap

        *timeStamp        = GetCurrentTime() - dwTimeZero;

        variableBindings->list = NULL;
        variableBindings->len  = 0;


        // Indicate that valid trap data exists in the parameters.

        return TRUE;
        }
    else
        {
        whichTime = 0;    // Supports the simulation.


        // Indicate that no more traps are available and parameters do not
        // refer to any valid data.

        return FALSE;
        }

    } // end SnmpExtensionTrap()