HV *NewHash(PERL_CALL_SINGLE) 
{ 
	HV *hash = newHV(); 
	
	if(!hash) 
		RaiseException(STATUS_NO_MEMORY, 0, 0, NULL); 
	
	return hash; 
}