void syscallRequestRunNewProcess(const char* executablePath) {
	createNewProcess(executablePath, getCurrentProcess()->executionDirectory);
}