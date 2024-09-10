bool Dynamixel::open_serial(const char *serial_device) {
	serial_fd_ = CreateFileA(serial_device, GENERIC_READ | GENERIC_WRITE,
			0,                          /* no share  */
			NULL,                       /* no security */
			OPEN_EXISTING,
			0,                          /* no threads */
			NULL);                      /* no templates */
	char mode_str[] = "baud=1000000 data=8 parity=n stop=1";
	if(serial_fd_==INVALID_HANDLE_VALUE) return false;
	DCB port_settings;
	memset(&port_settings, 0, sizeof(port_settings));  /* clear the new struct  */
	port_settings.DCBlength = sizeof(port_settings);

	COMMTIMEOUTS Cptimeouts;

	Cptimeouts.ReadIntervalTimeout = MAXDWORD;
	Cptimeouts.ReadTotalTimeoutMultiplier = 0;
	Cptimeouts.ReadTotalTimeoutConstant = 0;
	Cptimeouts.WriteTotalTimeoutMultiplier = 0;
	Cptimeouts.WriteTotalTimeoutConstant = 0;

	if (!BuildCommDCBA(mode_str, &port_settings) || !SetCommState(serial_fd_, &port_settings) || !SetCommTimeouts(serial_fd_, &Cptimeouts)) {
		CloseHandle(serial_fd_);
		return false;
	}
	return true;
}