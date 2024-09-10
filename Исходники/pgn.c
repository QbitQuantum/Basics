/**
pgn_open():
pgn_open opens a .pgn file and reads all games into the internal database.
The number of games found is returned.
Created 091407; last modified 091607
**/
int pgn_open(char *file_name)
{
	char buffer[BUFSIZ];
	char *c;
	char *b;
	int games;
	long last_offset;
	PGN_GAME *game;
	PGN_STATE state;

	/* Try opening the file. */
	if (pgn_file != NULL)
		fclose(pgn_file);
	pgn_file = fopen(file_name, "rt");
	if (pgn_file == NULL)
	{
		print("%s: file not found.\n", file_name);
		return -1;
	}
	/* First, quickly find the number of games. */
	state = NEUTRAL;
	games = 0;
	while (fgets(buffer, BUFSIZ, pgn_file) != NULL)
	{
		switch (state)
		{
			case NEUTRAL:
				/* Stupid macros need an int cast... sigh */
				if (isspace((int)buffer[0]))
					continue;
				state = HEADERS;
			case HEADERS:
				if (buffer[0] == '[')
					continue;
				state = MOVES;
			case MOVES:
				if (strstr(buffer, "1-0") || strstr(buffer, "0-1") ||
					strstr(buffer, "1/2-1/2") || strstr(buffer, "*"))
				{
					games++;
					state = NEUTRAL;
				}
		}
	}
	/* Initialize the database. */
	if (pgn_database.game != NULL)
		free(pgn_database.game);
	pgn_database.game_count = games;
	pgn_database.game = calloc(games, sizeof(PGN_GAME));
	print("%i games loaded.\n", games);
	/* Read in all of the games. */
	state = NEUTRAL;
	rewind(pgn_file);
	last_offset = 0;
	game = &pgn_database.game[0];
	while (fgets(buffer, BUFSIZ, pgn_file))
	{
		switch (state)
		{
			case NEUTRAL:
				/* Stupid macros need an int cast... sigh */
				if (isspace((int)buffer[0]))
					continue;
				game->offset = last_offset;
				state = HEADERS;
			case HEADERS:
				if (buffer[0] == '[')
				{
					c = strtok(buffer, "\"");
					if (c == NULL)
						continue;
					c = strtok(buffer + strlen(c) + 1, "\"");
					if (c == NULL)
						continue;
					b = strtok(buffer + 1, " =\"");
					if (!strcmp(b, "Event"))
						strcpy(game->tag.event, c);
					if (!strcmp(b, "Site"))
						strcpy(game->tag.site, c);
					if (!strcmp(b, "Date"))
						strcpy(game->tag.date, c);
					if (!strcmp(b, "Round"))
						strcpy(game->tag.round, c);
					if (!strcmp(b, "White"))
						strcpy(game->tag.white, c);
					if (!strcmp(b, "Black"))
						strcpy(game->tag.black, c);
					if (!strcmp(b, "Result"))
						strcpy(game->tag.result, c);
					if (!strcmp(b, "FEN"))
					{
						strcpy(game->tag.fen, c);
						initialize_board(c);
					}
					continue;
				}
				state = MOVES;
			case MOVES:
				if (strstr(buffer, "1-0") || strstr(buffer, "0-1") ||
					strstr(buffer, "1/2-1/2") || strstr(buffer, "*"))
				{
					game++;
					state = NEUTRAL;
				}
		}
		last_offset = ftell(pgn_file);
	}
	return games;
}