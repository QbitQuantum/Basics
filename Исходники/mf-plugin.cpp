extern "C" bool obs_module_load(void)
{
	CoInitializeEx(0, COINIT_MULTITHREADED);
	MFStartup(MF_VERSION, MFSTARTUP_FULL);

	RegisterMFAACEncoder();
	RegisterMFH264Encoders();

	return true;
}