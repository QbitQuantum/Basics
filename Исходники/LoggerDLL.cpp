static LogDef* _TlsInit()
{
	LogDef* p = new LogDef[1];  
	p->_endPtr = p->_startPtr = p->_pageNbr = 0;
	p->_pageLimit = p->_pageSize = 0 ;
	p->_loggerBase = 0;

	if (! TlsSetValue(tlsIDX, p)) 
        RaiseException(UNABLE_TLS_SET_VALUE,0,0,NULL);
	return p;
}