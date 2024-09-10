void ElSystem(const string &aCommand)
{
	#ifdef PRINT_EL_SYSTEM
		cout << "ElSystem: [" << aCommand << "]" << endl;
	#endif

	#ifdef EXECUTE_EL_SYSTEM
		int result = System(aCommand + " >/dev/null 2>&1");
		if (result != 0) ELISE_ERROR_EXIT("command [" << aCommand << "] failed (" << result << ")");
	#endif
}