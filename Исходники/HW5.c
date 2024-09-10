// Main method of HW5, mostly taking user input and running the correct prog
int main(int argc, char *argv[]) {

	// Look for correct command line arguments
	if(argc <= 1) {
		usage();
		return 0;
	} else {
		if(strcmp(argv[1], "tablecheck") == 0) {
			// Tablecheck prog should be run
			FILE* tablefile = NULL;
			for(int i=2; i<argc; i++) {
				if(strncmp(argv[i], "-t=", 3) == 0) {
					tablefile = fopen(argv[i]+3, "r");
					if(tablefile == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[i]+3);
						return 0;
					}
				}
			}
			if(tablefile) {
				tablecheck(tablefile);
				fclose(tablefile);
			} else {
				usage("tablecheck");
			}
		}
		else if(strcmp(argv[1], "encrypt") == 0) {
			// Encrypt prog should be run
			char *key = NULL;
			FILE* tablefile = NULL;
			for(int i=2; i<argc; i++) {
				if(strncmp(argv[i], "-k=", 3) == 0) {
					key = argv[i]+3;
				}
				else if(strncmp(argv[i], "-t=", 3) == 0) {
					tablefile = fopen(argv[i]+3, "r");
					if(tablefile == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[i]+3);
						return 0;
					}
				}
			}
			if(key && tablefile) {
				if(argv[argc-1][0] != '-') {
					// Take input from file
					FILE* fin = NULL;
					fin = fopen(argv[argc-1], "r");
					if(fin == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[argc-1]);
						return 0;
					}
					encrypt(key, tablefile, fin);
					fclose(fin);
				} else {
					// Take input from cmd line
					encrypt(key, tablefile, stdin);
				}
				fclose(tablefile);
			} else {
				usage("encrypt");
			}
		}
		else if(strcmp(argv[1], "decrypt") == 0) {
			// Decrypt prog should be run
			char *key = NULL;
			FILE* tablefile = NULL;
			for(int i=2; i<argc; i++) {
				if(strncmp(argv[i], "-k=", 3) == 0) {
					key = argv[i]+3;
				}
				else if(strncmp(argv[i], "-t=", 3) == 0) {
					tablefile = fopen(argv[i]+3, "r");
					if(tablefile == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[i]+3);
						return 0;
					}
				}
			}
			if(key && tablefile) {
				if(argv[argc-1][0] != '-') {
					// Take input from file
					FILE* fin = NULL;
					fin = fopen(argv[argc-1], "r");
					if(fin == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[argc-1]);
						return 0;
					}
					decrypt(key, tablefile, fin);
					fclose(fin);
				} else {
					// Take input from cmd line
					decrypt(key, tablefile, stdin);
				}
				fclose(tablefile);
			} else {
				usage("decrypt");
			}
		}
		else if(strcmp(argv[1], "encrypt3") == 0) {
			// Encrypt3 prog should be run
			char *key3 = NULL;
			FILE* tablefile = NULL;
			for(int i=2; i<argc; i++) {
				if(strncmp(argv[i], "-k=", 3) == 0) {
					key3 = argv[i]+3;
				}
				else if(strncmp(argv[i], "-t=", 3) == 0) {
					tablefile = fopen(argv[i]+3, "r");
					if(tablefile == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[i]+3);
						return 0;
					}
				}
			}
			if(key3 && tablefile) {
				if(argv[argc-1][0] != '-') {
					// Take input from file
					FILE* fin = NULL;
					fin = fopen(argv[argc-1], "r");
					if(fin == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[argc-1]);
						return 0;
					}
					encrypt3(key3, tablefile, fin);
					fclose(fin);
				} else {
					// Take input from cmd line
					encrypt3(key3, tablefile, stdin);
				}
				fclose(tablefile);
			} else {
				usage("encrypt3");
			}
		}
		else if(strcmp(argv[1], "decrypt3") == 0) {
			// Decrypt3 prog should be run
			char *key3 = NULL;
			FILE* tablefile = NULL;
			for(int i=2; i<argc; i++) {
				if(strncmp(argv[i], "-k=", 3) == 0) {
					key3 = argv[i]+3;
				}
				else if(strncmp(argv[i], "-t=", 3) == 0) {
					tablefile = fopen(argv[i]+3, "r");
					if(tablefile == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[i]+3);
						return 0;
					}
				}
			}
			if(key3 && tablefile) {
				if(argv[argc-1][0] != '-') {
					// Take input from file
					FILE* fin = NULL;
					fin = fopen(argv[argc-1], "r");
					if(fin == NULL) {
						fprintf(stderr, "ERROR: invalid file '%s' for reading.\n", argv[argc-1]);
						return 0;
					}
					decrypt3(key3, tablefile, fin);
					fclose(fin);
				} else {
					// Take input from cmd line
					decrypt3(key3, tablefile, stdin);
				}
				fclose(tablefile);
			} else {
				usage("decrypt3");
			}
		}
		else {
			// Failed input
			usage();
		}
	}
	
	return 0;
}