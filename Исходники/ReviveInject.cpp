int OpenProcessAndInject(wchar_t *processId) {
	HANDLE hProcess = (HANDLE)wcstol(processId, nullptr, 0);
	if (hProcess == NULL)
	{
		printf("Failed to get process handle\n");
		return -1;
	}

	if (!InjectOpenVR(hProcess) ||
		!InjectLibRevive(hProcess)) {
		return -1;
	}

	printf("Injected dlls succesfully\n");
	return 0;
}