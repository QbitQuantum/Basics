BOOL WINAPI SnmpExtensionQuery(
    IN BYTE                   requestType,
    IN OUT RFC1157VarBindList *variableBindings,
    OUT AsnInteger            *errorStatus,
    OUT AsnInteger            *errorIndex)
    {
    static unsigned long requestCount = 0;  // Supports the trap simulation.
    UINT    I;


    // Iterate through the variable bindings list to resolve individual
    // variable bindings.

    for ( I=0;I < variableBindings->len;I++ )
        {
        *errorStatus = ResolveVarBind( &variableBindings->list[I],
                                       requestType );


        // Test and handle case where Get Next past end of MIB view supported
        // by this Extension Agent occurs.  Special processing is required to 
        // communicate this situation to the Extendible Agent so it can take 
        // appropriate action, possibly querying other Extension Agents.

        if ( *errorStatus == SNMP_ERRORSTATUS_NOSUCHNAME &&
             requestType == MIB_ACTION_GETNEXT )
           {
           *errorStatus = SNMP_ERRORSTATUS_NOERROR;


           // Modify variable binding of such variables so the OID points
           // just outside the MIB view supported by this Extension Agent.
           // The Extendible Agent tests for this, and takes appropriate
           // action.

           SnmpUtilOidFree( &variableBindings->list[I].name );
           SnmpUtilOidCpy( &variableBindings->list[I].name, &MIB_OidPrefix );
           variableBindings->list[I].name.ids[MIB_PREFIX_LEN-1] ++;
           }


        // If an error was indicated, communicate error status and error
        // index to the Extendible Agent.  The Extendible Agent will ensure
        // that the origional variable bindings are returned in the response
        // packet.

        if ( *errorStatus != SNMP_ERRORSTATUS_NOERROR )
           {
	   *errorIndex = I+1;
	   goto Exit;
	   }
        }

Exit:


    // Supports the trap simulation.

    if (++requestCount % 3 == 0 && hSimulateTrap != NULL)
        SetEvent(hSimulateTrap);


    // Indicate that Extension Agent processing was sucessfull.

    return SNMPAPI_NOERROR;

    } // end SnmpExtensionQuery()