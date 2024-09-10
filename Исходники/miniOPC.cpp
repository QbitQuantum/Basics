myOPC::myOPC(wchar_t *ServerName):TimeBias(0),PercentDeadband(0.0),Connected(false)
{
	//подключение к серверу
	#ifdef _mDEBUG
	log="Конструктор: \n";
	log="Подключение к OPC серверу "+String(ServerName)+" \n";
	log+="Инициализация COM библиотек\n";
	#endif
	result=CoInitialize(NULL); //подготовка СОМ библиотек к работе
	#ifdef _mDEBUG
	if (result==S_OK||result==S_FALSE)
	{
		log+="OK\n";
	}else
	{
		log+="FAIL\n";
	}
	log+="Получение идентификатора класса сервера по его имени (clsid)\n";
	#endif
	// получение идентификатора класса по имени сервера
	result=CLSIDFromProgID(ServerName,&clsid);
	if (result!=S_OK)
	{
	#ifdef _mDEBUG
		log+="FAIL\n";
	#endif
		return;
	}
	#ifdef _mDEBUG
	else
	{
		log+="OK\n";
	}
	log+="Получение адреса сервера (pIOPCServer)\n";
	#endif
	// получение адреса сервера
	result=CoCreateInstance(clsid,NULL,CLSCTX_LOCAL_SERVER,IID_IOPCServer,(void**)&pIOPCServer);
	if (result!=S_OK)
	{
	#ifdef _mDEBUG
		log+="FAIL\n";
	#endif
		return;
	}
	#ifdef _mDEBUG
	else
	{
		log+="OK\n";
	}
	log+="Соединение с сервером установлено\n\n";
	#endif
	Connected=true;
	Groups.clear();
}