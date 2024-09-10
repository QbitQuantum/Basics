BOOLEAN NPUnicodeStringToChar(PUNICODE_STRING UniName, char Name[])
{
    ANSI_STRING	AnsiName;			
    NTSTATUS	ntstatus;
    char*		nameptr;			
    
    __try {	    		   		    		
		ntstatus = RtlUnicodeStringToAnsiString(&AnsiName, UniName, TRUE);		
						
		if (AnsiName.Length < 260) {
			nameptr = (PCHAR)AnsiName.Buffer;
			//Convert into upper case and copy to buffer
			//strcpy(Name, _strupr(nameptr));						    	    
			memcpy(Name, _strupr(nameptr),AnsiName.Length);				
			DbgPrint("NPUnicodeStringToChar : %s\n", Name);	
		}		  	
		RtlFreeAnsiString(&AnsiName);		 
	} 
	__except(EXCEPTION_EXECUTE_HANDLER) {
		DbgPrint("NPUnicodeStringToChar EXCEPTION_EXECUTE_HANDLER\n");	
		return FALSE;
	}
    return TRUE;
}      