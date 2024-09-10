int gpio_led_main(int argc, char *argv[])
{
	if (argc < 2) {
#ifdef CONFIG_ARCH_BOARD_PX4FMU_V1
		errx(1, "usage: gpio_led {start|stop} [-p <1|2|a1|a2|r1|r2>]\n"
		     "\t-p\tUse pin:\n"
		     "\t\t1\tPX4FMU GPIO_EXT1 (default)\n"
		     "\t\t2\tPX4FMU GPIO_EXT2\n"
		     "\t\ta1\tPX4IO ACC1\n"
		     "\t\ta2\tPX4IO ACC2\n"
		     "\t\tr1\tPX4IO RELAY1\n"
		     "\t\tr2\tPX4IO RELAY2"
		    );
#endif
#ifdef CONFIG_ARCH_BOARD_PX4FMU_V2
		errx(1, "usage: gpio_led {start|stop} [-p <n>]\n"
		     "\t-p <n>\tUse specified AUX OUT pin number (default: 1)"
		    );
#endif

	} else {

		if (!strcmp(argv[1], "start")) {
			if (gpio_led_started) {
				errx(1, "already running");
			}

			bool use_io = false;

			/* by default use GPIO_EXT_1 on FMUv1 and GPIO_SERVO_1 on FMUv2 */
			int pin = 1;

			/* pin name to display */
#ifdef CONFIG_ARCH_BOARD_PX4FMU_V1
			char *pin_name = "PX4FMU GPIO_EXT1";
#endif
#ifdef CONFIG_ARCH_BOARD_PX4FMU_V2
			char pin_name[] = "AUX OUT 1";
#endif

			if (argc > 2) {
				if (!strcmp(argv[2], "-p")) {
#ifdef CONFIG_ARCH_BOARD_PX4FMU_V1

					if (!strcmp(argv[3], "1")) {
						use_io = false;
						pin = GPIO_EXT_1;
						pin_name = "PX4FMU GPIO_EXT1";

					} else if (!strcmp(argv[3], "2")) {
						use_io = false;
						pin = GPIO_EXT_2;
						pin_name = "PX4FMU GPIO_EXT2";

					} else if (!strcmp(argv[3], "a1")) {
						use_io = true;
						pin = PX4IO_P_SETUP_RELAYS_ACC1;
						pin_name = "PX4IO ACC1";

					} else if (!strcmp(argv[3], "a2")) {
						use_io = true;
						pin = PX4IO_P_SETUP_RELAYS_ACC2;
						pin_name = "PX4IO ACC2";

					} else if (!strcmp(argv[3], "r1")) {
						use_io = true;
						pin = PX4IO_P_SETUP_RELAYS_POWER1;
						pin_name = "PX4IO RELAY1";

					} else if (!strcmp(argv[3], "r2")) {
						use_io = true;
						pin = PX4IO_P_SETUP_RELAYS_POWER2;
						pin_name = "PX4IO RELAY2";

					} else {
						errx(1, "unsupported pin: %s", argv[3]);
					}

#endif
#ifdef CONFIG_ARCH_BOARD_PX4FMU_V2
					unsigned int n = strtoul(argv[3], NULL, 10);

					if (n >= 1 && n <= 6) {
						use_io = false;
						pin = 1 << (n - 1);
						snprintf(pin_name, sizeof(pin_name), "AUX OUT %d", n);

					} else {
						errx(1, "unsupported pin: %s", argv[3]);
					}

#endif
				}
			}

			memset(&gpio_led_data, 0, sizeof(gpio_led_data));
			gpio_led_data.use_io = use_io;
			gpio_led_data.pin = pin;
			int ret = work_queue(LPWORK, &gpio_led_data.work, gpio_led_start, &gpio_led_data, 0);

			if (ret != 0) {
				errx(1, "failed to queue work: %d", ret);

			} else {
				gpio_led_started = true;
				warnx("start, using pin: %s", pin_name);
				exit(0);
			}
		} else if (!strcmp(argv[1], "stop")) {
			if (gpio_led_started) {
				gpio_led_started = false;
				warnx("stop");
				exit(0);
			} else {
				errx(1, "not running");
			}

		} else {
			errx(1, "unrecognized command '%s', only supporting 'start' or 'stop'", argv[1]);
		}
	}
}