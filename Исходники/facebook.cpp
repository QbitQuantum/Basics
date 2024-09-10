int UpStatusFb(string paramId, string paramMessage, string paramToken)
{
	HINTERNET hopen, hconnect, hrequest;
	string accesstoken = paramToken;
	int n = accesstoken.size();
	string version = "/v2.1";
	string id = paramId;
	string edge ="/comments";
	char chUrlRequset [400];
	string urlRequest = version+"/"+id+edge+"?"+accesstoken;
	String2Char(urlRequest,chUrlRequset);

	char headers[]="Content-Type: application/x-www-form-urlencoded";
	char formdata[300];
	String2Char("message="+paramMessage,formdata);
	

	hopen = InternetOpenA("HTTPGET",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	hconnect = InternetConnectA(hopen,GRAPH_FB,INTERNET_DEFAULT_HTTPS_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
	hrequest= HttpOpenRequestA(hconnect,"POST",chUrlRequset,"HTTP/1.1",NULL, NULL,INTERNET_FLAG_SECURE , 0);
	if(HttpSendRequestA(hrequest,headers,strlen(headers),formdata,strlen(formdata))) {
		//printf("Success\n");
	}
	InternetCloseHandle(hrequest);
	InternetCloseHandle(hconnect);
	InternetCloseHandle(hopen);
	return 1;
	

}