SNMPRemoteAgent::SNMPRemoteAgent(std::string name, std::string community, unsigned int port, SNMPSession * pSession) {
	_name = name;
	_port = port;
	_community = community;
	_bInit = false;
	_mySession = false;
	_pSession = pSession;
	_hEntity = SNMPAPI_FAILURE;
	_hContext = SNMPAPI_FAILURE;
	if(_pSession == NULL) {
		try {
			_pSession = new SNMPSession();
		} catch(SNMPException * pe) {
			SNMP_RETHROW_ERROR("Could not create WinSNMP session", pe, SNMPAPI_OTHER_ERROR, SNMP_ERROR);
		}
		_mySession = true;
	}
	HSNMP_SESSION hSession = _pSession->getHandle();
	if(hSession == SNMPAPI_FAILURE) {
		if(_mySession && _pSession != NULL) {
			delete _pSession;
		}
		_pSession = NULL;		
		SNMP_THROW_ERROR("Invalid session", SnmpGetLastError(NULL), SNMP_ERROR);
	}
	_hEntity = SnmpStrToEntity(hSession, _name.c_str());
	if (_hEntity == SNMPAPI_FAILURE) {
		LPHOSTENT lpHostent = gethostbyname(_name.c_str());
		IN_ADDR host;
		if(!lpHostent) {
			if(_mySession && _pSession != NULL) {
				delete _pSession;
			}
			_pSession = NULL;
			SNMP_THROW_ERROR("Could not get host by name", SNMPAPI_OTHER_ERROR, SNMP_ERROR);
		}
		memmove (&host, lpHostent->h_addr, sizeof(IN_ADDR));
		_hEntity = SnmpStrToEntity(hSession, inet_ntoa(host));
		if (_hEntity == SNMPAPI_FAILURE) {
			if(_mySession && _pSession != NULL) {
				delete _pSession;
			}
			_pSession = NULL;
			SNMP_THROW_ERROR("Could not convert remote agent address to entity", SnmpGetLastError(hSession), SNMP_ERROR);
		}
	}
	if(port != 0) {
		if(SnmpSetPort(_hEntity, port) != SNMPAPI_SUCCESS) {
			SnmpFreeEntity(_hEntity);
			_hEntity = SNMPAPI_FAILURE;
			if(_mySession && _pSession != NULL) {
				delete _pSession;
			}
			_pSession = NULL;
			SNMP_THROW_ERROR("Could not set remote agent port", SnmpGetLastError(hSession), SNMP_ERROR);
		}
	}
	smiOCTETS dCtx;
	dCtx.len = (smiUINT32)strlen(community.c_str());
	dCtx.ptr = (smiLPBYTE)community.c_str();
	_hContext = SnmpStrToContext(hSession, &dCtx);
	if (_hContext == SNMPAPI_FAILURE)  {
		SnmpFreeEntity(_hEntity);
		_hEntity = SNMPAPI_FAILURE;
		if(_mySession && _pSession != NULL) {
			delete _pSession;
		}
		_pSession = NULL;
		SNMP_THROW_ERROR("Could not convert community name to context", SnmpGetLastError(hSession), SNMP_ERROR);
	}
	_pSession->registerRemoteAgent(this);
	_bInit = true;
}