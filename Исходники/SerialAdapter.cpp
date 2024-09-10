bool SerialAdapter::Init()
{
	f_init=true;
	f_loop=false;
	f_start=false;

	Logger::Println("[SerialPort]	Initialize");

	string mySection="Serial";
	string str = ApplicationProperty::ReadSetupString(mySection.c_str(),"ComName","COM3");
	int fps = ApplicationProperty::ReadSetupInt(mySection.c_str(),"Fps",60);
	strcpy_s(comName,"COM3");
	ncomcfg=sizeof(comcfg);

	hPort = CreateFile(
		comName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if(hPort == INVALID_HANDLE_VALUE){
		Logger::Println("[SerialPort]	Error : CreateFile Fail");
		goto error;
	}

	if(!SetupComm(hPort,1024,1024)){
		Logger::Println("[SerialPort]	Error : SetupComm Fail");
		goto error;
	}

	if(!PurgeComm(hPort,PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR)){
		Logger::Println("[SerialPort]	Error : PurgeComm Fail");
		goto error;
	}

	GetCommConfig(hPort,&comcfg,&ncomcfg);
	if(!SetCommConfig(hPort, &comcfg,ncomcfg))
	{
		Logger::Println("[SerialPort]	Error : SetCommState Fail");
		goto error;
	}
	
	COMMTIMEOUTS timeout;
	SetupTimeout(&timeout);
	if(!SetCommTimeouts(hPort, &timeout)){
		Logger::Println("[SerialPort]	Error : SetCommTimeouts Fail");
		goto error;
	}

	unsigned int id;
	myHandle=(HANDLE)_beginthreadex(NULL,0,SerialAdapter::Launch,this,0,&id);
	if(myHandle==NULL){
		Logger::Println("[SerialPort]	Error : Thread Error");
		goto error;
	}
	return true;

error:
	f_init=false;
	return false;
}