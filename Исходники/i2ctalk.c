int main(int argc, const char * argv[])
{
	const char * hex = "0123456789abcdef";

	self = basename((char*)argv[0]);

	for (int ai = 1; ai < argc; ai++) {
		const char * src = argv[ai];
		display_mode[ai] = NULL;

		if (!strcmp(argv[ai], "--loop")) {
			bus = 4;
			msg[0].addr = 0x55;
			msg_count = 1;

			while (1) {
				process();
				sleep(1);
			}
		}
		while (*src) {
			char c = *src++;
			switch (c) {
				case '=': {
					if (process() > 0)
						display();
					bus = 0;
					while (isdigit(*src))
						bus = (bus * 10) + (*src++ - '0');
				}	break;
				case '@': {
					if (process() > 0)
						display();

					address = 0;
					while (isxdigit(*src))
						address = (address << 4) | (int)(strchr(hex, tolower(*src++)) - hex);
				//	printf("Set address to 0x%2x\n", address);
				}	break;
				case 'w': {
					msg[msg_count].addr = address;
					msg[msg_count].flags = 0;
					msg[msg_count].len = 0;
					msg[msg_count].buf = write_ptr;
					while (isxdigit(src[0]) && isxdigit(src[1])) {
						uint8_t byte = ((strchr(hex, tolower(src[0])) - hex) << 4) |
								(int)(strchr(hex, tolower(src[1])) - hex);
						src += 2;
						*write_ptr++ = byte;
						msg[msg_count].len++;
					}
					if (msg[msg_count].len) {
					//	printf("Write %d bytes : ", msg[msg_count].len);
					//	for (int i = 0; i < msg[msg_count].len; i++)
					//		printf("%02x", msg[msg_count].buf[i]);
					//	printf("\n");
						msg_count++;
					} else {
						fprintf(stderr, "%s: Warning '%s' won't write anything\n", self, argv[ai]);
					}
				}	break;
				case 'r': {
					msg[msg_count].addr = address;
					msg[msg_count].flags = I2C_M_RD;
					msg[msg_count].len = 0;
					msg[msg_count].buf = write_ptr;
					display_mode[msg_count] = src; // keep it around for display

					int count = 0;
					while (*src) {
						switch (*src) {
							case '0' ... '9' :
								count = (count*10) + (*src++ - '0');
								break;
							case 'b':
								count = count ? count : 1;
								msg[msg_count].len += count;
								write_ptr += count;
								count = 0;
								src++;
								break;
							case 's':
								count = count ? count * 2 : 2;
								msg[msg_count].len += count;
								write_ptr += count;
								count = 0;
								src++;
								break;
							case 't':	// temperature
								count = 2;
								msg[msg_count].len += count;
								write_ptr += count;
								count = 0;
								src++;
								break;
							case 'l':
								count = count ? count * 4 : 4;
								msg[msg_count].len += count;
								write_ptr += count;
								count = 0;
								src++;
								break;
							case 'g':		// gyro from MotionPlus
								count = 6;
								msg[msg_count].len += count;
								write_ptr += count;
								count = 0;
								src++;
								break;
							case 'c':		// compass module
								count = 5;
								msg[msg_count].len += count;
								write_ptr += count;
								count = 0;
								src++;
								break;
							case 'a':		// accelerometer
								count = 6;
								msg[msg_count].len += count;
								write_ptr += count;
								count = 0;
								src++;
								break;
							case ' ':
								break;
							default:
								printf("Unknown format '%c' for reading\n", c);
								exit(1);
						}
					}
					if (msg[msg_count].len) {
					//	printf("Reading %d bytes\n", msg[msg_count].len);
						msg_count++;
					} else {
						display_mode[msg_count] = NULL;
						fprintf(stderr, "%s: Warning '%s' won't read anything\n", self, argv[ai]);
					}
				}	break;
				case ' ':
					break;
				default:
					fprintf(stderr, "%s: ERROR Unknown command character '%c'\n", self, c);
					exit(1);
			}
		}
	}
	if (process() > 0)
		display();
}