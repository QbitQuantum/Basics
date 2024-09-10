extern "C" int main(int argc, char* argv[]){
	if(argc < 2){
		std::cout << "No exe specified!\n\n";
		std::cout << "Usage: winheaptrack <exe path> [target working dir]\n\n"
		             "       The first argument specifies the exe to launch.\n"
		             "       The second optional argument specifies the working directory\n"
		             "       of the exe to launch (this defaults to directory of exe.)\n";
			 
		return -1;
	}
	char *injectionTarget = argv[1];
	std::string injectionTargetWorkingDirectory;

	if(argc > 2)
		injectionTargetWorkingDirectory = argv[2];
	else
		injectionTargetWorkingDirectory = getDirectoryOfFile(injectionTarget);


	bool win64 = false;
	#ifdef _WIN64
		win64 = true;
	#endif
	// Select correct dll name depending on whether x64 or win32 version launched.
	std::string winheaptrackInjectDllName;
	if(win64)
		winheaptrackInjectDllName = "winheaptrack_inject_x64.dll";
	else
		winheaptrackInjectDllName = "winheaptrack_inject_Win32.dll";

	// Assume that the injection payload dll is in the same directory as the exe.
	std::string exePath(argv[0]);
	std::string dllPath = getDirectoryOfFile(exePath) + "\\" + winheaptrackInjectDllName;

	// Start our new process with a suspended main thread.
	std::cout << "Starting process with heap profiling enabled..." << std::endl;
	std::cout << "Target exe path: " << injectionTarget << std::endl;
	std::cout << "Working directory: " << injectionTargetWorkingDirectory << std::endl;
	std::cout << "Dll to inject: " << dllPath << std::endl;

	DWORD flags = CREATE_SUSPENDED;
	PROCESS_INFORMATION pi;
	STARTUPINFOA si;
    GetStartupInfoA(&si);
	if(CreateProcessA(NULL, injectionTarget, NULL, NULL, 0, flags, NULL, 
		             (LPSTR)injectionTargetWorkingDirectory.c_str(), &si, &pi) == 0){
		std::cerr << "Error creating process " << injectionTarget << " with working directory " << injectionTargetWorkingDirectory << std::endl;
		return -1;
	}
		
	// Inject our dll.
	// This method returns only when injection thread returns.
	try{
		if(!LoadLibraryInjection(pi.hProcess, dllPath.c_str())){
			throw std::runtime_error("LoadLibrary failed!");
		}
	}catch(const std::exception &e){
		std::cerr << "\n";
		std::cerr << "Error while injecting process: " << e.what() << "\n\n";
		std::cerr << "Check that the hook dll (" << dllPath << " is in the correct location.\n\n";
		std::cerr << "Are you trying to inject a " << (win64 ? " 32 bit " : " 64 bit ") << " application using the "
			<<  (win64 ? " 64 bit " : " 32 bit ") << " injector?\n\n";

		// TODO: figure out how to terminate thread. This does not always work.
		TerminateProcess(pi.hProcess, 0);
		return -1;
	}
	
	// Once the injection thread has returned it is safe to resume the main thread.
	ResumeThread(pi.hThread);

	// Wait for the target application to exit. 
	// This doesn't matter to much, but makes winheaptrack nicer to use in test scripts.
	// (Like the ProfileTestApplication project.)
	WaitForSingleObject(pi.hProcess, INFINITE);
	return 0;
}