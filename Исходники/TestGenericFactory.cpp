int main(int argc, char** argv)
{
	try
	{
#ifdef WIN32
		DllMain(0, DLL_PROCESS_ATTACH, 0);
#endif

		IClassFactory* pFact = 0;
		CheckHr(DllGetClassObject(CLSID_TestGenericFactory, IID_IClassFactory, (void**)&pFact));

		IUnknown* pTest = 0;
		CheckHr(pFact->CreateInstance(0, IID_IUnknown, (void**)&pTest));

		pFact->Release();
		pTest->Release();

#ifdef WIN32
		return DllMain(0, DLL_PROCESS_DETACH, 0) ? 0 : 1;
#else
		return 0;
#endif
	}
	catch (Throwable& thr)
	{
		std::cerr << "Failed HRESULT: " << thr.Error() << "\n";
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	catch (...)
	{
		std::cerr << "Unknown Exception:\n";
	}

	return 2;
}