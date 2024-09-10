void SMNetworkAdapterSettings::_FingSetupInfo(HDEVINFO* devInfo, SP_DEVINFO_DATA* devInfoData) const
{
	SM_ASSERT( !_hardwareId.IsEmpty() );

	SMString hwID(_hardwareId);
	hwID.MakeUpper();

	*devInfo = ::SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
	if( INVALID_HANDLE_VALUE == *devInfo )
		throw SMRuntimeException(::GetLastError());

	::ZeroMemory(devInfoData, sizeof(SP_DEVINFO_DATA));
	devInfoData->cbSize = sizeof(SP_DEVINFO_DATA);

	PTSTR buf = NULL;
	DWORD bufSize = 0;
	DWORD reqSize = 0;

	for(int i=0; SetupDiEnumDeviceInfo(*devInfo,i, devInfoData); i++)
	{
		if ( !SetupDiGetDeviceInstanceId(*devInfo, devInfoData, buf, bufSize, &reqSize) )
		{
			if ( bufSize < reqSize )
			{
				if ( NULL != buf )
				{
					delete[] buf;
					buf = NULL;
					bufSize = 0;
				}
				buf = new TCHAR[reqSize];
				if ( NULL == buf )
				{
					SM_LOG(1, E_FAIL, SMString("Insufficient memory : ") + _com_error(GetLastError()).ErrorMessage());
					break;
				}
				bufSize = reqSize;
				if ( !SetupDiGetDeviceInstanceId(*devInfo, devInfoData, buf, bufSize, &reqSize) )
					throw SMRuntimeException(::GetLastError());
			}
			else
			{
				SM_LOG(1, E_FAIL, SMString("SetupDiGetDeviceInstanceId(): ") + _com_error(GetLastError()).ErrorMessage());
				break;
			}
		}

		SMString szBuf = buf;
		szBuf.MakeUpper();

		if ( szBuf.Find(hwID.DataW()) != -1 )
			return;
	}
}