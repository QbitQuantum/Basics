SNMPAPI_STATUS SNMPSession::processNotification(WPARAM wParam, LPARAM lParam) {
	if(wParam == 0) {
		HSNMP_PDU hPdu;
		HSNMP_CONTEXT hContext;
		HSNMP_ENTITY hDstEntity;
		HSNMP_ENTITY hSrcEntity;
		SNMPAPI_STATUS ret = SnmpRecvMsg(_hSession, &hSrcEntity, &hDstEntity, &hContext, &hPdu);
		SNMPRemoteAgent * pRa = getRemoteAgent(hContext);		
		int requestId = (DWORD)lParam;
		SNMPRequest * pRequest = NULL;
		if(pRa) {
			pRequest = pRa->getRequest(requestId);
		}
		if(ret == SNMPAPI_FAILURE) {
			if(pRequest) {
				pRequest->setResult(SNMP_ERROR_GENERR);
			}
			SnmpFreeVbl(hPdu);
			return SNMPAPI_SUCCESS;
		}	
		smiINT32 lReqId, lType, lErr, lIdx;
		HSNMP_VBL hVbl;
		ret = SnmpGetPduData(hPdu, &lType, &lReqId, &lErr, &lIdx, &hVbl);
		if(ret == SNMPAPI_FAILURE) {
			if(pRequest) {
				pRequest->setResult(SNMP_ERROR_GENERR);
			}
			SnmpFreeVbl(hPdu);
			return SNMPAPI_SUCCESS;
		}
#ifdef SMNP_TRACER
		if(SNMPTRACEAENABLED()) {
			std::stringstream trace;
			trace << "rx " << SNMPManager::pduToStr(hDstEntity, hSrcEntity, hContext, lType, lReqId, lErr, hVbl, false);
			SNMPTRACE(trace.str());
		}
#endif
		if(lType != SNMP_PDU_RESPONSE) {
			pRequest = NULL;
		}
		if(pRequest == NULL && lType != SNMP_PDU_TRAP && lType != SNMP_PDU_INFORM) {
			SnmpFreeVbl(hVbl);
			SnmpFreeVbl(hPdu);
			return SNMPAPI_SUCCESS;
		}

		smiOID dRetName;
		smiVALUE dRetValue;
		int count = SnmpCountVbl(hVbl);
		if(count) {
			char szName[MAXOBJIDSTRSIZE+1];
			szName[0] = szName[MAXOBJIDSTRSIZE] = '\0';
			for(int i=0; i<count; i++) {
				if(SnmpGetVb(hVbl, i+1, &dRetName, &dRetValue) == SNMPAPI_FAILURE) {
					SnmpFreeVbl(hVbl);
					SnmpFreePdu(hPdu);
					if(pRequest) {
						pRequest->setResult(SNMP_ERROR_GENERR);
					}
					return SNMPAPI_SUCCESS;
				}
				if(SnmpOidToStr(&dRetName, sizeof(szName), szName) == SNMPAPI_FAILURE) {
					szName[0] = '\0';
				}
				SNMPObject obj;
				obj.setValue(&dRetValue);
				obj.setOID(szName);
				if(pRequest) {
					pRequest->addToResult(obj);
				} else {
					processTrap(obj);
				}
				SnmpFreeDescriptor(SNMP_SYNTAX_OID, (smiLPOPAQUE)&dRetName);
				if(dRetValue.syntax == SNMP_SYNTAX_OID) {
					SnmpFreeDescriptor(dRetValue.syntax, (smiLPOPAQUE)&dRetValue.value.oid);
				} else if(	dRetValue.syntax == SNMP_SYNTAX_OPAQUE ||
							dRetValue.syntax == SNMP_SYNTAX_OCTETS ||
							dRetValue.syntax == SNMP_SYNTAX_BITS ||
							dRetValue.syntax == SNMP_SYNTAX_IPADDR ||
							dRetValue.syntax == SNMP_SYNTAX_NSAPADDR) {
					SnmpFreeDescriptor(dRetValue.syntax, (smiLPOPAQUE)&dRetValue.value.string);
				}
			}
		}
		SnmpFreeVbl(hVbl);
		SnmpFreePdu(hPdu);
		if(pRequest) {
			pRequest->setResult(lErr, false);
		}
		return SNMPAPI_SUCCESS;
	}
	return SNMPAPI_SUCCESS;
}