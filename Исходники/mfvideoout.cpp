MfVideoOut::~MfVideoOut()
{
	MFShutdown();

	CoUninitialize();
}