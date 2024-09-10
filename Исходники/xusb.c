int main(int argc, char** argv)
{
	bool show_help = false;
	bool debug_mode = false;
	const struct libusb_version* version;
	int j, r;
	size_t i, arglen;
	unsigned tmp_vid, tmp_pid;
	uint16_t endian_test = 0xBE00;

	// Default to generic, expecting VID:PID
	VID = 0;
	PID = 0;
	test_mode = USE_GENERIC;

	if (((uint8_t*)&endian_test)[0] == 0xBE) {
		printf("Despite their natural superiority for end users, big endian\n"
			"CPUs are not supported with this program, sorry.\n");
		return 0;
	}

	if (argc >= 2) {
		for (j = 1; j<argc; j++) {
			arglen = strlen(argv[j]);
			if ( ((argv[j][0] == '-') || (argv[j][0] == '/'))
			  && (arglen >= 2) ) {
				switch(argv[j][1]) {
				case 'd':
					debug_mode = true;
					break;
				case 'b':
					strcat(binary_name, "raw.bin");
					if (j+1 < argc) {
						strncpy(binary_name, argv[j+1], 64);
						j++;
					}
					binary_dump = true;
					break;
				case 'g':
					break;
				case 'j':
					// OLIMEX ARM-USB-TINY JTAG, 2 channel composite device - 2 interfaces
					if (!VID && !PID) {
						VID = 0x15BA;
						PID = 0x0004;
					}
					break;
				case 'k':
					// Generic 2 GB USB Key (SCSI Transparent/Bulk Only) - 1 interface
					if (!VID && !PID) {
						VID = 0x0204;
						PID = 0x6025;
					}
					break;
				// The following tests will force VID:PID if already provided
				case 'p':
					// Sony PS3 Controller - 1 interface
					VID = 0x054C;
					PID = 0x0268;
					test_mode = USE_PS3;
					break;
				case 'x':
					// Microsoft XBox Controller Type S - 1 interface
					VID = 0x045E;
					PID = 0x0289;
					test_mode = USE_XBOX;
					break;
				default:
					show_help = true;
					break;
				}
			} else {
				for (i=0; i<arglen; i++) {
					if (argv[j][i] == ':')
						break;
				}
				if (i != arglen) {
					if (sscanf_s(argv[j], "%x:%x" , &tmp_vid, &tmp_pid) != 2) {
						printf("   Please specify VID & PID as \"vid:pid\" in hexadecimal format\n");
						return 1;
					}
					VID = (uint16_t)tmp_vid;
					PID = (uint16_t)tmp_pid;
				} else {
					show_help = true;
				}
			}
		}
	}

	if ((show_help) || (argc == 1) || (argc > 7)) {
		printf("usage: %s [-d] [-b [file]] [-h] [-i] [-j] [-k] [-x] [vid:pid]\n", argv[0]);
		printf("   -h: display usage\n");
		printf("   -d: enable debug output (if library was compiled with debug enabled)\n");
		printf("   -b: dump Mass Storage first block to binary file\n");
		printf("   -g: short generic test (default)\n");
		printf("   -k: test generic Mass Storage USB device (using WinUSB)\n");
		printf("   -j: test FTDI based JTAG device (using WinUSB)\n");
		printf("   -p: test Sony PS3 SixAxis controller (using WinUSB)\n");
		printf("   -x: test Microsoft XBox Controller Type S (using WinUSB)\n");
		return 0;
	}

	version = libusb_get_version();
	printf("Using libusbx v%d.%d.%d.%d\n\n", version->major, version->minor, version->micro, version->nano);
	r = libusb_init(NULL);
	if (r < 0)
		return r;

	// Info = 3, Debug = 4
	libusb_set_debug(NULL, debug_mode?4:3);

	test_device(VID, PID);

	libusb_exit(NULL);

	return 0;
}