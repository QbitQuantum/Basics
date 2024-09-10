int open_com(DeviceType device, HANDLE *p_result)
{
	const char *dcb_string = "baud=9600 parity=N data=8 stop=1";
	int port_number = 1;
	HANDLE com_port = INVALID_HANDLE_VALUE;
	char port_name[] = {
		'\\',
		'\\',
		'.',
		'\\',
		'C',
		'O',
		'M',
		'0',
		0
	};
	DCB port_dcb = {sizeof(DCB)};
	COMMTIMEOUTS port_timeouts = {MAXDWORD, MAXDWORD, 1000, 0, 0 };
	switch (device) {
	case CALIBRATOR:
		port_number = 1;
		break;
	case VOLTM_VER:
		port_number++;
	case VOLTM_REF:
		port_number++;
		dcb_string = "baud=9600 parity=N data=8 stop=2";
		break;
	default:
		fprintf (stderr, "Unexpected device code %d\n", device);
		exit(1);
	}
	port_name[countof(port_name) - 2] += port_number;
	printf("name=%s\n", port_name);
	com_port = CreateFileA(
		port_name,
		GENERIC_READ | GENERIC_WRITE,
		7,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (com_port == INVALID_HANDLE_VALUE) return ERROR_CODE;
	printf("h=%p\n", com_port);
	if (!BuildCommDCBA(dcb_string, &port_dcb)) return ERROR_CODE;
	if (!SetCommState(com_port, &port_dcb)) return ERROR_CODE;
	if (!SetCommTimeouts(com_port, &port_timeouts)) return ERROR_CODE;
	if (!SetupComm(com_port, 1024, 1024)) return ERROR_CODE;
	*p_result = com_port;
	return 0;
}