int main(int argc, char* argv[]) {
	int i = 0;
	int opt = 0;
	int action = 0;
	unsigned long long ecid = 0;
	int mode = -1;
	char* argument = NULL;
	irecv_error_t error = 0;

	char* buffer = NULL;
	uint64_t buffer_length = 0;

	if (argc == 1) {
		print_usage(argc, argv);
		return 0;
	}

	while ((opt = getopt(argc, argv, "i:vhrsmnc:f:e:k::")) > 0) {
		switch (opt) {
			case 'i':
				if (optarg) {
					char* tail = NULL;
					ecid = strtoull(optarg, &tail, 16);
					if (tail && (tail[0] != '\0')) {
						ecid = 0;
					}
					if (ecid == 0) {
						fprintf(stderr, "ERROR: Could not parse ECID from argument '%s'\n", optarg);
						return -1;
					}
				}
				break;

			case 'v':
				verbose += 1;
				break;

			case 'h':
				print_usage(argc, argv);
				return 0;

			case 'm':
				action = kShowMode;
				break;

			case 'n':
				action = kRebootToNormalMode;
				break;

			case 'r':
				action = kResetDevice;
				break;

			case 's':
				action = kStartShell;
				break;

			case 'f':
				action = kSendFile;
				argument = optarg;
				break;

			case 'c':
				action = kSendCommand;
				argument = optarg;
				break;

			case 'k':
				action = kSendExploit;
				argument = optarg;
				break;

			case 'e':
				action = kSendScript;
				argument = optarg;
				break;

			default:
				fprintf(stderr, "Unknown argument\n");
				return -1;
		}
	}

	if (verbose)
		irecv_set_debug_level(verbose);

	irecv_init();
	irecv_client_t client = NULL;
	for (i = 0; i <= 5; i++) {
		debug("Attempting to connect... \n");

		if (irecv_open_with_ecid(&client, ecid) != IRECV_E_SUCCESS)
			sleep(1);
		else
			break;

		if (i == 5) {
			return -1;
		}
	}

	irecv_device_t device = NULL;
	irecv_devices_get_device_by_client(client, &device);
	if (device)
		debug("Connected to %s, model %s, cpid 0x%04x, bdid 0x%02x\n", device->product_type, device->hardware_model, device->chip_id, device->board_id);

	switch (action) {
		case kResetDevice:
			irecv_reset(client);
			break;

		case kSendFile:
			irecv_event_subscribe(client, IRECV_PROGRESS, &progress_cb, NULL);
			error = irecv_send_file(client, argument, 1);
			debug("%s\n", irecv_strerror(error));
			break;

		case kSendCommand:
			error = irecv_send_command(client, argument);
			debug("%s\n", irecv_strerror(error));
			break;

		case kSendExploit:
			if (argument != NULL) {
				irecv_event_subscribe(client, IRECV_PROGRESS, &progress_cb, NULL);
				error = irecv_send_file(client, argument, 0);
				if (error != IRECV_E_SUCCESS) {
					debug("%s\n", irecv_strerror(error));
					break;
				}
			}
			error = irecv_trigger_limera1n_exploit(client);
			debug("%s\n", irecv_strerror(error));
			break;

		case kStartShell:
			init_shell(client);
			break;

		case kSendScript:
			buffer_read_from_filename(argument, &buffer, &buffer_length);
			if (buffer) {
				buffer[buffer_length] = '\0';

				error = irecv_execute_script(client, buffer);
				if(error != IRECV_E_SUCCESS) {
					debug("%s\n", irecv_strerror(error));
				}

				free(buffer);
			} else {
				fprintf(stderr, "Could not read file '%s'\n", argument);
			}
			break;

		case kShowMode:
			irecv_get_mode(client, &mode);
			printf("%s Mode\n", mode_to_str(mode));
			break;

		case kRebootToNormalMode:
			error = irecv_setenv(client, "auto-boot", "true");
			if (error != IRECV_E_SUCCESS) {
				debug("%s\n", irecv_strerror(error));
				break;
			}

			error = irecv_saveenv(client);
			if (error != IRECV_E_SUCCESS) {
				debug("%s\n", irecv_strerror(error));
				break;
			}

			error = irecv_reboot(client);
			if (error != IRECV_E_SUCCESS) {
				debug("%s\n", irecv_strerror(error));
			} else {
				debug("%s\n", irecv_strerror(error));
			}
			break;
		default:
			fprintf(stderr, "Unknown action\n");
			break;
	}

	irecv_close(client);

	return 0;
}