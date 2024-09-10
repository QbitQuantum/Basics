std::map<std::string, std::string> DroneController::configuration(const double timeout)
{
	const double connectStart = seconds();
	while(isNotTalking() && seconds() - connectStart < timeout) msleep(100);
	if(isNotTalking()) return std::map<std::string, std::string>();
	
	Socket s = Socket::tcp();
	
	if(!s.setReusable(true)) return std::map<std::string, std::string>();
	if(!s.connect(m_configAddress)) return std::map<std::string, std::string>();
	if(!s.setBlocking(false)) return std::map<std::string, std::string>();
	
	control(5);
	control(4);
	
	char buffer[65536];
	buffer[0] = 0;
	const double start = seconds();
	
	ssize_t size = 0;
	do {
		size = s.recv(buffer, sizeof(buffer));
		msleep(100);
	} while(size < 0 && seconds() - start < timeout);
	
	s.close();
	
	if(size < 0) return std::map<std::string, std::string>();
	
	// std::cout << buffer << std::endl;
	
	std::map<std::string, std::string> ret;
	
	// We convert all delimeters to '\0', then walk through with basic C
	// string functions
	for(size_t i = 0; i < size; ++i) {
		if(buffer[i] == '\n') buffer[i] = 0;
		if(buffer[i] == '=') buffer[i - 1] = 0;
	}
	
	const char *walker = buffer;
	while(walker - buffer < size) {
		const char *const key = walker;
		const char *const value = walker + strlen(key) + 3;
		if(strlen(key) >= 1 && strlen(value) >= 1) ret[key] = value;
		walker = value + strlen(value) + 1;
	}
	
	return ret;
}