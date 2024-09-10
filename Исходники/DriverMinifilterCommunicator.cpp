bool DriverMinifilterCommunicator::StartHiding(const TargetObjectList &targetObjects)
{
	// do nothing if the driver is not installed
	if(!m_isInstalled)
	{
		return false;
	}

	if(targetObjects.empty())
	{
		Logger::Instance().Log(_T("Objects to be hidden are not defined... Not sending information to driver"), WARNING);
		return false;
	}

	// allocate space for all objects to be hidden
	DWORD dwArraySize = sizeof(TARGET_OBJECT) * targetObjects.size();

	// initialize array which will hold all objects for hiding
	PTARGET_OBJECT pTargetObjectArray = (PTARGET_OBJECT) VirtualAlloc(0, dwArraySize, MEM_COMMIT, PAGE_READWRITE);
	if(pTargetObjectArray == NULL)
	{
		Logger::Instance().Log(_T("Failed to allocate memory for array of objects to be hidden"), ERR);
		return false;
	}

	// "linearize" all objects to be hidden to array
	DWORD dwObjIndex = 0;
	TargetObjectList::const_iterator iter;
	for(iter = targetObjects.begin(); iter != targetObjects.end(); ++iter)
	{
		TargetObjectPtr targetObject = *iter;
		pTargetObjectArray[dwObjIndex] = targetObject->LinearizeObject();
		dwObjIndex++;
	}

	// format new message (be cautious when setting the required size)
	ULONG uCommandBlockSize = FIELD_OFFSET(COMMAND_MESSAGE, pData[dwArraySize]);
	PCOMMAND_MESSAGE pCommandMessage = (PCOMMAND_MESSAGE) VirtualAlloc(0, uCommandBlockSize, MEM_COMMIT, PAGE_READWRITE);
	if(pCommandMessage == NULL)
	{
		Logger::Instance().Log(_T("Failed to allocate memory for port command message block"), ERR);
		return false;
	}

	pCommandMessage->Command = DmfsStartHiding;
	memcpy_s(pCommandMessage->pData, uCommandBlockSize - FIELD_OFFSET(COMMAND_MESSAGE, pData), pTargetObjectArray, dwArraySize);

	// send symbols to driver
	DWORD dwBytesReturned = 0;
	if(IS_ERROR(FilterSendMessage(	m_driverPort,					// communication port
									pCommandMessage,				// command message
									uCommandBlockSize,				// size of command message
									NULL,							// no output array
									0,								// no output array size
									&dwBytesReturned				// actual size of the array (in bytes)
								 )))
	{
		Logger::Instance().Log(_T("Error starting hiding engine"), ERR);
		VirtualFree(pTargetObjectArray, 0, MEM_RELEASE);
		return false;
	}

	Logger::Instance().Log(_T("Hiding engine started!"), SUCCESS);
	VirtualFree(pTargetObjectArray, 0, MEM_RELEASE);
	VirtualFree(pCommandMessage, 0, MEM_RELEASE);

	// TEST ONLY!
	Sleep(900000);

	return true;
}