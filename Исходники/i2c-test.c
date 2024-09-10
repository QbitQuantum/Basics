int main(int argc, char** argv)
{
	unsigned char addr;
	unsigned char data[5];
	
	char device_name[20];
	
	int opt;
	int bus = 0;
	int n = 0;
	char mode = 'b';
	int num;
	char format = 'x';

	uint8_t array_byte[128];

	const char *fmt_byte;
	const char *fmt_short;
	const char *fmt_long;
	
	char *base_name;

	while ((opt = getopt(argc, argv, "d:f:m:r:wh")) != -1) {
		switch (opt) {
			case 'f':
				format = optarg[0];
				break;
			case 'd':
				bus = atoi(optarg);
				break;
			case 'm':
				mode = optarg[0];
				break;
			case 'r':
				n = atoi(optarg);
				break;			
			case 'h':
			default:
				base_name = basename(argv[0]);

				fprintf(stderr, "Usage: %s [-d I2CBUS] [[-r N] [-m MODE] [-f FORMAT]] ADDRESS [VAL1 VAL2 ...]\n"
						"       %s 0x20 0x00\n"
						"       %s 0x20 -r 1 -m s -f d\n"
						"  I2CBUS is an integer\n"
						"  N      is an integer the number of element to be read\n"
						"  MODE   is b|s|l   - byte|short|long\n"
						"  FORMAT is x|d|u   - hex|signed|unsigned\n",
                    			base_name, base_name, base_name);
				return -1;
		}
	}
	//fprintf(stderr, "bus=%d; mode=%c; n=%d; optind=%d\n", bus, mode, n, optind);

	if ( format == 'x' ) {
		fmt_byte = "0x%02X";
		fmt_short = "0x%04X";
		fmt_long = "0x%08lX";
	}
	else if ( format == 'd' ) {
		fmt_byte = "%d";
		fmt_short = "%d";
		fmt_long = "%ld";	
	}
	else {
		fmt_byte = "%u";
		fmt_short = "%u";
		fmt_long = "%lu";
	}

	if ( mode == 's' ) {
		n *= 2;
	}
	else if ( mode == 'l' ) {
		n *= 4;
	}
	else if ( mode == 'c' ) {
	}
	
	if ( optind >= argc ) {
        fprintf(stderr, "Expected ADDRESS\n");
        return -1;
    	}	
	addr = _atoi(argv[optind++]);
	//fprintf(stderr, "addr=0x%02X\n", addr);

	num = 0;
	for (;optind < argc; optind++) {
		if ( num >= 128 )
			break;
		array_byte[num++] = (uint8_t)_atoi(argv[optind]);
	}	
	//fprintf(stderr, "num=%d\n", num);	

	sprintf(device_name, "/dev/i2c-%u", bus);
	fd = open(device_name,O_RDWR);
	if ( fd < 0 ) {
		fprintf(stderr, "Couldn't open %s!\n", device_name);
		return -2;
	}
	
	setaddr(addr);

	if ( num ) {
		if ( write(fd, array_byte, num) < 0 ) {
			fprintf(stderr, "Unable to write!\n");
			close(fd);
			return -2;
		}
	}
	
	if ( n ) {
		int i;

		n = n < 128 ? n : 128;
		read(fd, array_byte, n);
		
		if ( mode == 'c' ) {
			for ( i = 0; i < n; i++ ) {
				char c;
				
				c = array_byte[i];
				printf("%c", iscntrl(c) ? '.' : c);
			}
		
		}
		else if ( mode == 's' ) {
			union {
				uint16_t u16;
				uint8_t arr[2];
			} w;
			
			for ( i = 0; i < n; i += 2 ) {
				w.arr[0] = array_byte[i];
				w.arr[1] = array_byte[i + 1];
				
				if ( i != 0 )
					printf(" ");

				if ( format == 'd' )
					printf(fmt_short, (int16_t)le16toh(w.u16));
				else
					printf(fmt_short, (uint16_t)le16toh(w.u16));
			}
		}
		else if ( mode == 'l' ) {
			union {
				uint32_t u32;
				uint8_t arr[4];
			} w;
			
			for ( i = 0; i < n; i += 4 ) {
				w.arr[0] = array_byte[i];
				w.arr[1] = array_byte[i + 1];
				w.arr[2] = array_byte[i + 2];
				w.arr[3] = array_byte[i + 3];
				
				if ( i != 0 )
					printf(" ");

				if ( format == 'd' )
					printf(fmt_long, (int32_t)le32toh(w.u32));
				else
					printf(fmt_long, (uint32_t)le32toh(w.u32));
			}
	
		}		
		else {
			for ( i = 0; i < n; i++ ) {				
				if ( i != 0 )
					printf(" ");

				if ( format == 'd' )
					printf(fmt_byte, (int8_t)array_byte[i]);
				else				
					printf(fmt_byte, array_byte[i]);
			}
		}
		printf("\n");
	}
	
	close(fd);
	return 0;
}