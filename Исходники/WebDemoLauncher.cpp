void launchBrowser(std::string url) {
	std::string command;
	command += "start " + url;
	system(command.c_str());
}