void PCSC::GetATR(){
	*ReturnValue = SCardGetAttrib(
					Context, 
					SCARD_ATTR_ATR_STRING,
					(LPBYTE)&BuffATR, 
					&SizeATR);          
	Status(); 

}