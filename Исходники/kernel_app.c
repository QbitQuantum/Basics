/* 
 * Read  and write all the ports specified in hex on the command line. 
 * The program uses the faster ioperm[set port IO permissions]/iopl[change IO privilege level] calls on x86. 
 * The program acts as inb/inw/inl according  to its own name.
 */
int port_io(int argc, char **argv)
{
    unsigned int i, n, port, size, error = 0;
	unsigned int val, opt;
    
    prgname = argv[0];
    switch (prgname[strlen(prgname)-1]) {
        case 'w': 
			size = 2; 
			break;
			
        case 'l': 
			size = 4; 
			break;
			
        case 'b': 
			
		case 'p': 
			
		default:
	    	size = 1;
    }
	
    setuid(0); 

	printf("Please choose the option: 1 - read, 2 - write: ");
	scanf("%d",&opt);

	if (opt == 1) {
	    for (i = 1; i < argc; i++) {
	        if ( sscanf(argv[i], "%x%n", &port, &n) < 1 || n != strlen(argv[i]) ) {
		    	fprintf(stderr, "%s: argument \"%s\" is not a hex number\n", argv[0], argv[i]);
				error++; 
				continue;
			}
			
			if (port & (size-1)) {
			    fprintf(stderr, "%s: argument \"%s\" is not properly aligned\n", argv[0], argv[i]);
			    error++; 
				continue;
			}
			
			error += read_one(port, size);
		}
	} else if (opt == 2) {
		for (i = 1; i < argc-1; i++) {
	        if ( sscanf(argv[i], "%x%n", &port, &n) < 1 || n != strlen(argv[i]) ) {
		    	fprintf(stderr, "%s: argument \"%s\" is not a hex number\n", argv[0], argv[i]);
		    	error++; 
				continue;
			}
			
			if (port & (size-1)) {
		    	fprintf(stderr, "%s: argument \"%s\" is not properly aligned\n", argv[0], argv[i]);
		    	error++; 
				continue;
			}
			
	        if ( sscanf(argv[i+1], "%x%n", &val, &n) < 1 || n != strlen(argv[i+1]) ) {
		    	fprintf(stderr, "%s: argument \"%s\" is not a hex number\n", argv[0], argv[i+1]);
		    	error++; 
				continue;
			}
			
			if (size < 4 && val > (size == 1 ? 0xff : 0xffff)) {
			    fprintf(stderr, "%s: argument \"%s\" out of range\n", argv[0], argv[i+1]);
			    error++; 
				continue;
			}
			
			error += write_one(port, val, size);
	    }
	}
	
    return (error ? 1 : 0);
}