int main(int argc, char ** argv)
{
    char * outname = "aout.rdf";
    int  moduleloaded = 0;

    options.verbose = 0;
    options.align = 16;
    options.warnUnresolved = 0;
    options.strip = 0;
    
    argc --, argv ++;
    if (argc == 0) usage();
    while (argc && **argv == '-' && argv[0][1] != 'l')
    {
	switch(argv[0][1]) {
	case 'r':
	    printf("ldrdf (linker for RDF files) version " LDRDF_VERSION "\n");
	    printf( _RDOFF_H "\n");
	    exit(0);
	case 'v':
	    if (argv[0][2] == '=') {
		options.verbose = argv[0][3] - '0';
		if (options.verbose < 0 || options.verbose > 9) {
		    fprintf(stderr, "ldrdf: verbosity level must be a number"
			    " between 0 and 9\n");
		    exit(1);
		}
	    }
	    else
		options.verbose++;
	    break;
	case 'a':
	    options.align = atoi(argv[1]);
	    if (options.align <= 0) {
		fprintf(stderr, 
			"ldrdf: -a expects a positive number argument\n");
		exit(1);
	    }
	    argv++, argc--;
	    break;
	case 's':
	    options.strip = 1;
	    break;
	case 'x':
	    options.warnUnresolved = 1;
	    break;
	case 'o':
	    outname = argv[1];
	    argv++, argc--;
	    break;
	default:
	    usage();
	}
	argv++, argc--;
    }

    if (options.verbose > 4) {
	printf("ldrdf invoked with options:\n");
	printf("    section alignment: %d bytes\n", options.align);
	printf("    output name: `%s'\n", outname);
	if (options.strip)
	    printf("    strip symbols\n");
	if (options.warnUnresolved)
	    printf("    warn about unresolved symbols\n");
	printf("\n");
    }

    symtab = symtabNew();
    initsegments();

    if (!symtab) {
	fprintf(stderr, "ldrdf: out of memory\n");
	exit(1);
    }

    while (argc)
    {
	if (!strncmp(*argv, "-l", 2)) /* library */
	    add_library(*argv + 2);
	else {
	    loadmodule(*argv);
	    moduleloaded = 1;
	}
	argv++, argc--;
    }

    if (! moduleloaded) {
	printf("ldrdf: nothing to do. ldrdf -h for usage\n");
	return 0;
    }

    
    search_libraries();

    if (options.verbose > 2)
    {
	printf ("symbol table:\n");
	symtabDump(symtab, stdout);
    }

    write_output(outname);

    if (errorcount > 0)
	exit(1);

    return 0;
}