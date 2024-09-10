//初始化CGI程序环境变量
void initEnvironmentVariables(HttpTask *task){
	//SERVER_NAME
	SetEnvironmentVariableA("SERVER_NAME", task->hostName.c_str());
	//SERVER_PORT
	SetEnvironmentVariableA("SERVER_PORT", int2str(task->serverPort).c_str());

	HttpRequest *request = &(task->request);
	std::string uri = request->getRequestURI();
	//...解码

	//取得params
	std::string params;
	if (fetchParams(uri, &params)){
		SetEnvironmentVariableA("QUERY_NAME", params.c_str());
	}
	
	//REQUEST_METHOD
	if (request->getRequestMethod() == GET)
		SetEnvironmentVariableA("REQUEST_METHOD", "GET");
	else
	{
		SetEnvironmentVariableA("CONTENT_LENGTH", int2str(task->request.getContentLength()).c_str());
		SetEnvironmentVariableA("REQUEST_METHOD", "POST");
	}
}