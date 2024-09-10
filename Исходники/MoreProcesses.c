/******************************************************************************
	Returns the Process Information for the process specified by pPSN.
	
	pPSN				input:	The process's Serial Number
	pPIR				output:	The process's Information.
	
	RESULT CODES
	____________
	noErr			   0	No error
	paramErr		 �	Process serial number is invalid (or pPSN or pPIR is nil)
	____________
*/
pascal OSStatus MoreProcGetProcessInformation(const ProcessSerialNumber *pPSN,ProcessInfoRec *pPIR)
{
	if (!MoreAssert (pPIR))
		return paramErr;

	pPIR->processInfoLength	= sizeof (*pPIR);
	pPIR->processName		= nil;
#ifndef __LP64__
	pPIR->processAppSpec	= nil;
#endif

	if (pPSN)
		return GetProcessInformation (pPSN,pPIR);
	else
	{
		ProcessSerialNumber psn = { kNoProcess,kCurrentProcess };
		return GetProcessInformation (&psn,pPIR);
	}
}