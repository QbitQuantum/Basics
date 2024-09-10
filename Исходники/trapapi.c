// authenticate community of rfc1157 message with valid communities in registry
BOOL commauth(RFC1157Message *message)
    {
    static BOOL fFirstTime = TRUE;

    BOOL fFound = FALSE;
    INT  i;

    if (fFirstTime)
        {
        fFirstTime = FALSE;
        vcConfig(&validComms, &validCommsLen);
        }

    if (validCommsLen > 0)
        {
        for(i=0; i < validCommsLen; i++)
            {
            if ((strlen(validComms[i].communityName) == message->community.length) && 
                !strncmp(message->community.stream, validComms[i].communityName, message->community.length))
                {
                fFound = TRUE;
                break;
                }
            } // end for ()
        }
    else
        {
        fFound = TRUE; // no entries means all communities allowed
        } // end if

    if (!fFound)
        {
        SNMPDBG((SNMP_LOG_TRACE, "SNMP: PDU: invalid community filtered.\n"));

        if (enableAuthTraps)
            {
            if (!SnmpSvcGenerateAuthFailTrap(SnmpSvcGetUptime()))
                {
                SNMPDBG((SNMP_LOG_TRACE, "SNMP: PDU: error on SnmpSvcGenerateAuthFailTrap %d.\n",
                          GetLastError()));

                }
            } // end if
        } // end if

    return fFound;

    } // end commauth()