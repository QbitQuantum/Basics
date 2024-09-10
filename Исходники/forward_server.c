static int read_config_file(serial_control_t *ctrl)
{
	char mode[10], baudrate[20], bits[10], parity[10], stop[10];

	if (read_conf_value("MODE", mode, tty_config) != 0) {
		error_printf("serial_config: get MODE failed\n");
		return EXIT_FAILURE;
	}

	if (read_conf_value("BAUDRATE", baudrate, tty_config) != 0) {
		error_printf("serial_config: get BAUDRATE failed\n");
		return EXIT_FAILURE;
	}

	if (read_conf_value("DATA_BITS", bits, tty_config) != 0) {
		error_printf("serial_config: get DATA_BITS failed\n");
		return EXIT_FAILURE;
	}

	if (read_conf_value("PARITY", parity, tty_config) != 0) {
		error_printf("serial_config: get PARITY failed\n");
		return EXIT_FAILURE;
	}

	if (read_conf_value("STOP_BITS", stop, tty_config) != 0) {
		error_printf("serial_config: get STOP_BITS failed\n");
		return EXIT_FAILURE;
	}

	if ((strcmp(mode, "RAW") == 0)||(strcmp(mode, "raw") == 0)) {
		ctrl->mode = RAW_MODE;
	} else {
		ctrl->mode = NORMAL_MODE;
	}
	
	ctrl->speed = STRTOL(baudrate);
	ctrl->bits = STRTOL(bits);
	ctrl->parity = STRTOL(parity);
	ctrl->stop = STRTOL(stop);

	debug_printf("read_config_file ->  %s\n",  tty_config);
	debug_printf("----------------------------------\n");
	debug_printf("serial_config: MODE=%s\n", mode);
	debug_printf("serial_config: BAUDRATE=%d\n", ctrl->speed);
	debug_printf("serial_config: DATA_BITS=%d\n", ctrl->bits);
	debug_printf("serial_config: PARITY=%s\n", parity);
	debug_printf("serial_config: STOP_BITS=%d\n", ctrl->stop);
	debug_printf("----------------------------------\n");

	return EXIT_SUCCESS;
}