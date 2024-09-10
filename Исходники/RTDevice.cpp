/* Reset
	Reset device 
	
	Output:
		if successful:	TRUE
		if unsuccessful:	FALSE

*/
BOOLEAN RTDevice::Reset()
{	if(fpReset == NULL) return FALSE;
	return fpReset(Handle); 
}