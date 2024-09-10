void VulkanBase::setupConsole(std::string title) {
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	SetConsoleTitle(TEXT(title.c_str()));
	if (enableValidation)
		std::cout << "Validation enabled\n";
}