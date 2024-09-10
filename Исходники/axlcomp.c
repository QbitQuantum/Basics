void
compFintFaultHandler(int signo)
{
        osDisplayMessage(comsgString(ALDOR_E_SigSegv));
	comsgFPrintf(osStdout, ALDOR_E_SigSegv);

	LongJmp(compFintJmpBuf, 1);
}