CSingleInstance::CSingleInstance(const string& strMutexName)
{
	// be sure to use a name that is unique for this application otherwise
	// two apps may think they are the same if they are using same name for
	// 3rd parm to CreateMutex
	SECURITY_ATTRIBUTES SA; 
	SECURITY_DESCRIPTOR SD;
	SECURITY_ATTRIBUTES *pSA = InitSecurityAttribute(SA, SD);
	//   Create   a   Semaphore   with   a   name   of   application   exename   
	m_hMutex = CreateSemaphoreA(pSA, 1, 1, strMutexName.c_str());
	m_dwLastError = ::GetLastError(); //save for use later...
}