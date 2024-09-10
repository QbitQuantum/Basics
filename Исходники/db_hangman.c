void
db_hangman(db_expr_t addr, int haddr, db_expr_t count, char *modif)
{
	char	*word;
	size_t	tries;
	size_t	len;
	struct _abc sabc[1];
	int	skill;

	if (modif[0] != 's' || (skill = modif[1] - '0') > 9U)
		skill = 3;
	word = NULL;
	tries = 0;
	for (;;) {

		if (word == NULL) {
			ABC_CLR();

			tries = skill + 1;
			word = db_randomsym(&len);
			if (word == NULL)
				break;

			db_plays++;
		}

		{
			int c;

			db_hang(tries, word, sabc);
			c = cngetc();
			c = TOLOWER(c);

			if (ISLOWALPHA(c) && ABC_ISCLR(c)) {
				char	*p;
				size_t	n;

					/* strchr(word,c) */
				for (n = 0, p = word; *p ; p++)
					if (TOLOWER(*p) == c)
						n++;

				if (n) {
					ABC_SETRIGHT(c);
					len -= n;
				} else {
					ABC_SETWRONG(c);
					tries--;
				}
			}
		}

		if (tries && len)
			continue;

		if (!tries && skill > 2) {
			char	*p = word;
			for (; *p; p++)
				if (ISALPHA(*p))
					ABC_SETRIGHT(TOLOWER(*p));
		}
		if (tries)
			db_guesses++;
		db_hang(tries, word, sabc);
		db_printf("\nScore: %lu/%lu\n", db_plays, db_guesses);
		word = NULL;
		if (tries)
			break;
	}
}