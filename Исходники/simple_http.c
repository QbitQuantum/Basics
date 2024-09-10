/*
	Retrieve IE user agent
	return hardcoded UA if it fails
*/
char *get_default_ua(){
	char *ua;	
	DWORD ualength = 512;
	int res = 0;

	ua = malloc(512);
	RtlZeroMemory(ua, 512);
	if (ua == NULL){
		return NULL;
	}
	RtlZeroMemory(ua, 512);
	/*	If AV picks up, reading reg could be a possible alternative:
		https://diablohorn.wordpress.com/2010/08/14/internetqueryoption-internet_option_user_agent-replacement/
	*/
	res = ObtainUserAgentString(0, ua, &ualength);
	if (res != NOERROR){
		strcpy_s(ua, 512, SH_DEFAULT_UA);
	}

	return ua;
}