void vbltoql(RFC1157VarBindList *vbl, SnmpMgmtQueryList *ql, UINT *errorStatus, UINT *errorIndex)
    {
    UINT v;  // index into view list
    UINT vb; // index into varbind list

    INT  nDiff;
    
    BOOL fAnyOk;
    BOOL fFoundOk = FALSE;

    SNMPDBG((SNMP_LOG_TRACE, "SNMP: PDU: processing %s request containing %d variable(s).\n",
        (ql->type == ASN_RFC1157_GETREQUEST)
            ? "get"
            : (ql->type == ASN_RFC1157_SETREQUEST)
                ? "set"
                : (ql->type == ASN_RFC1157_GETNEXTREQUEST)
                    ? "getnext"
                    : "unknown", vbl->len));

    // check to see if getnext is being requested
    fAnyOk = (ql->type == ASN_RFC1157_GETNEXTREQUEST);

    // initialize status return values
    *errorStatus = SNMP_ERRORSTATUS_NOERROR;
    *errorIndex  = 0;

    // process variable bindings
    for (vb=0; vb < vbl->len; vb++)
        {
        // process supported views
        for (v=0; v < vlLen; v++)
            {
            // compare request
            nDiff = SnmpUtilOidNCmp(
                        &vbl->list[vb].name,
                        &extAgents[vl[v]].supportedView,
                        extAgents[vl[v]].supportedView.idLength
                        );

            // analyze results based on request type
            fFoundOk = (!nDiff || (fAnyOk && (nDiff < 0)));

            // save
            if (fFoundOk)
                {
                // insert into query
                addql(ql, vbl, vb, v);
                break;
                }
            }

        // not found
        if (!fFoundOk)
            {
            SNMPDBG((SNMP_LOG_TRACE, "SNMP: PDU: %s not in supported view(s).\n", SnmpUtilOidToA(&vbl->list[vb].name)));
            *errorStatus = SNMP_ERRORSTATUS_NOSUCHNAME;
            *errorIndex  = vb+1;
            break;
            }
        }

    } // end vbltoql()