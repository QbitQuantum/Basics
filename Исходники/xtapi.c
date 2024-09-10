int xtapi_shutdown()
{
	LONG retval;
	
	if (!TapiObj.hObj) return 0;

//	Close any device that may be open at this point!

//	shutdown TAPI
	retval = lineShutdown(TapiObj.hObj);
	if (retval!=0)	return xtapi_err(retval);

	TapiObj.hObj = NULL;
	TapiObj.num_devs = 0;
	TapiObj.hWnd = NULL;	

	return 0;
}