inline HddDriveType HddDevice::GetHddType(astring &strDevice)
{
	return (HddDriveType)(m_Info.driveType(strDevice.c_str()));
}