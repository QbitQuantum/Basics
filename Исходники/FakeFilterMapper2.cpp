LONG WINAPI Mine_RegOpenKeyExA(HKEY a0, LPCSTR a1, DWORD a2, REGSAM a3, PHKEY a4)
{
	TRACE_SVP( "Mine_RegOpenKeyExA  %s %u ",  a1, a2);
	if( a1 ){
		if( _strcmpi(a1, "Software\\CoreCodec\\CoreAVC Pro") == 0){
			TRACE_SVP( "CoreAVC");
			*a4 = FAKEHKEY+1;
			 return ERROR_SUCCESS;
		}
        if( _strcmpi(a1, "Software\\CoreCodec\\CoreAVC Pro 2.x") == 0){
            TRACE_SVP( "CoreAVC 2");
            *a4 = FAKEHKEY+3;
            return ERROR_SUCCESS;
        }
		
		else if( _strcmpi(a1, "CLSID\\{083863F1-70DE-11D0-BD40-00A0C911CE86}\\Instance\\{09571A4B-F1FE-4C60-9760-DE6D310C7C31}") == 0) {
					*a4 = FAKEHKEY+2;
					 return ERROR_SUCCESS;
		}
		
		
	}
	

	if(CFilterMapper2::m_pFilterMapper2 && (a3&(KEY_SET_VALUE|KEY_CREATE_SUB_KEY))) {TRACE_SVP("Mine_RegOpenKeyExA %s" , a1);*a4 = FAKEHKEY; return ERROR_SUCCESS;}
	LONG ret = Real_RegOpenKeyExA(a0, a1, a2, a3, a4);

	//TRACE_SVP( "Mine_RegOpenKeyExA %s %u %u",  a1, a2, *a4);
	return ret;
}