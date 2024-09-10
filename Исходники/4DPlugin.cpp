void Get_timestring(PA_PluginParameters params)
{
	sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
	PackagePtr pParams = (PackagePtr)params->fParameters;
	
	C_TEXT returnValue;
	
	time_t timestamp = time(NULL);
	char ts[256];	
	
#if VERSIONMAC	
	setenv("TZ",(const char *)"GMT", 1);
#else	
	_wputenv_s(L"TZ",L"GMT"); 
#endif
	
	strftime(ts, 256, "%a, %d %b %y %X %Z",  localtime(&timestamp)); 
	
	returnValue.setUTF8String((const uint8_t*)ts, (uint32_t)strlen(ts));
	returnValue.setReturn(pResult);
}