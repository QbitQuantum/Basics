int sudoku(int mode)
{
	clear_window();
	int level = 1;
	/* we get a random number from 0 to 9 as a char value */
	char n[2] = {randomnumber(), '\0'};
	char path[256] = "/etc/sudoku/sudoku_";
	if (mode == LOAD_SUDOKU) {
		printf("Sudoku File Path: ");
		gets_s(path, 256);
	}
	else {
		if (mode == 0 || mode == 2) {
			strcat(path, "easy");
		}
		if (mode == 1 || mode == 3) {
			strcat(path, "difficult");
		}
		strcat(path, n);
	}
	int numbers[16];
	int numbers_def[16];
	/* get sudoku */
	for (int i = 0; i < 16; i++) {
		numbers_def[i] = make_sudoku(i, path);
		if (numbers_def[i] < 0 || numbers_def[i] > 4) {
			clear_window();
			printf("Error: El archivo '%s' es erroneo o corrupto\n", path);
			printf("Pulsa una tecla para continuar.\n");
			getchar();
			return -1;
		}
	}
	for (int i = 0; i < 16; i++) {
		numbers[i] = numbers_def[i];
	}
	int sudoku4x4[4][4];
	int subregions[4][4];
	char option = 'r';
	while (option != 'c' && option != 'C') {
		print_sudoku(numbers);
		for (int i = 0; i < 16; i++) {
			if (numbers[i] == 0) {
				printf("Introduce el valor a la X%d: ", i+1);
				numbers[i] = getnum();
				if (numbers[i] > 4 || numbers[i] == 0) {
					numbers[i] = 1;
				}
				/* if you press return key */
				if (numbers[i] == -1) {
					/* put numbers[i] and numbers[i-1] equal to 0
					 * if not you can't rewrite it 
					 */
					numbers[i] = 0;
					i--;
					if (numbers[i] != numbers_def[i] && i > 0) {
						numbers[i] = 0;
						i--;
					}
				}
				printf("%c\n", numbers[i]);
				print_sudoku(numbers);
			}
		}
		for (int i = 0, k = 0, p=0; k < 4; i++) {
			sudoku4x4[k][i] = numbers[p];
			if ((i+1) % 4 == 0) {
				k++;
				i = -1;
			}
			p++;
		}
		for(int i = 0, k = 0; i < 4; i++) {
			int action = 0;
			for(int j = 0; j < 4; j++) {
				subregions[i][j] = numbers[k];
				if ((k+1) % 2 == 0) {
					if ((k+1) == 8) {
						k = 5;
						action = 0;
					}
					if (action == 0) {
						k += 3;
						action++;
					}
					else {
						k -= 3;
						action--;
					}
				}
				else {
					k++;
				}
			}
		}
		int gamestate = WIN;
		/* check rows and columns */
		for (int i = 0, k = 0; k < 4; i++) {
			for (int x = 0; x < 4; x++) {
				if (sudoku4x4[k][i] == sudoku4x4[k][x] && i != x) {
					gamestate = LOST;
				}
			}
			if ((i+1) % 4 == 0) {
				k++;
				i = -1;
			}
		}
		for (int i = 0, k = 0; i < 4; k++) {
			for (int x = 0; x < 4; x++) {
				if (sudoku4x4[k][i] == sudoku4x4[x][i] && k != x) {
					gamestate = LOST;
				}
			}
			if ((k+1) % 4 == 0) {
				i++;
				k = -1;
			}
		}
		/* check subregions */
		for (int i = 0, k = 0; k < 4; i++) {
			for (int x = 0; x < 4; x++) {
				if (subregions[k][i] == subregions[k][x] && i != x) {
					gamestate = LOST;
				}
			}
			if (i+1 == 4) {
				k++;
				i = -1;
			}
		}
		if (gamestate == WIN && mode < 2) {
			printf("Nivel %d COMPLETADO\n", level);
			do {
				printf("[N]ivel %d o [C]errar\n", ++level);
				option = getchar();
			} while (option != 'n' && option != 'N' && option != 'c' && option != 'C');
			n[0] = randomnumber();
		}
		if (gamestate == LOST && mode < 2) {
			printf("Nivel %d NO COMPLETADO\n", level);
			do {
				printf("[R]eintentar o [C]errar\n");
				option = getchar();
			} while (option != 'r' && option != 'R' && option != 'c' && option != 'C');
		}
		if (mode == LOAD_SUDOKU) {
			if (gamestate == WIN) {
				printf("Sudoku COMPLETADO\n");
			}
			else {
				printf("Sudoku NO COMPLETADO\n");
			}
			printf("[R]eintentar o [C]errar\n");
			option = getchar();
		}
		if (option == 'r' || option == 'R' || option == 'n' || option == 'N') {
			for (int i = 0; i < 16; i++) {
				numbers[i] = make_sudoku(i, path);
			}
		}
		/* multiplayer mode */
		if (mode == COMPETITION_EASY && gamestate == WIN) {
			return 1;
		}
		if (mode == COMPETITION_DIFF && gamestate == WIN) {
			return 3;
		}
		if (mode == COMPETITION_EASY || mode == COMPETITION_DIFF) {
			if (gamestate == LOST) {
				return 0;
			}
		}
	}

	return 0;
}