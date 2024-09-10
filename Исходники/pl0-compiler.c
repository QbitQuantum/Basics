int main(int argc, char **argv) {
	FILE *input_file = NULL;
	int l_flag = 0, a_flag = 0, v_flag = 0; // output flags

	if(argc > 1) {
		int i;
		for(i = 1; i < argc; i++) {
			// last arg must be the input_file
			if((i+1) == argc) {
				input_file = fopen(argv[i], "r");
				if(!input_file) {
					printf("File %s not found.\n", argv[1]);
					exit(EXIT_FAILURE);
				}
			} else {
				if(argv[i][0] == '-') {
					int j;
					for(j = 1; j < strlen(argv[i]); j++) {
						if(argv[i][j] == 'l') l_flag = 1;
						else if(argv[i][j] == 'a') a_flag = 1;
						else if(argv[i][j] == 'v') v_flag = 1;
						else {
							printf("Unknown option: %s\n", argv[i]);
							exit(EXIT_FAILURE);
						}
					}
				}
			}
		}
	} else {
		printf("Usage: pl0-compiler [-l] [-a] [-v] /path/to/input_file\n");
		exit(EXIT_FAILURE);
	}

	FILE *lexeme_file = tmpfile();

	pl0_lex(input_file, lexeme_file, l_flag);
	fclose(input_file);

	rewind(lexeme_file);

	int error_code = pl0_parse(lexeme_file, a_flag);
	fclose(lexeme_file);

	if(error_code == 0) {
		FILE *code_file = tmpfile();
		print_code(code_file);
		rewind(code_file);

		if(v_flag) {
			printf("Running in PM/0\n");
			printf("===============\n\n");
		}

		error_code = pm0(code_file, v_flag);

		if(v_flag) {
			printf("\n===============\n\n");
		}
		if(!error_code) {
			if(v_flag) {
				printf("Finished without error.\n");
			}
		} else {
			printf("Error number %d.\n", error_code);
		}

		fclose(code_file);
	} else {
		printf("Error number %d, %s\n", error_code, get_parse_error(error_code));
	}

	return EXIT_SUCCESS;
}