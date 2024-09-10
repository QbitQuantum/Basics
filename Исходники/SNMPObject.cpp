void SNMPObject::setOID(std::string oid) {	
	if(_bInit) {
		SnmpFreeDescriptor(SNMP_SYNTAX_OCTETS, (smiLPOPAQUE)&_oid);
		_bInit = false;
	}
	if(oid != "") {
		if(SnmpStrToOid(oid.c_str(), &_oid) == SNMPAPI_FAILURE) {
			SNMP_THROW_ERROR("Could not convert OID from string representation", SnmpGetLastError(NULL), SNMP_ERROR);
		}
		_bInit = true;
	}
}