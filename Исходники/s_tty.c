int
tty_setup()
{
	WINDOW *tt_win, *newwin();
	char message[80], *str, *get_str();
	int num, i, j, ret_code;
	void disp_tty(), create_modem(), del_modem(), error_win();
	void del_tty();

	tt_win = newwin(23, 80, 0, 0);

	horizontal(tt_win, 0, 0, 34);
	mvwattrstr(tt_win, 0, 35, A_BOLD, "TTY Setup");
	horizontal(tt_win, 0, 45, 34);
	mvwaddstr(tt_win, 2, 22, "TTY name");
	mvwaddstr(tt_win, 2, 37, "Modem name");
	mvwaddstr(tt_win, 2, 51, "Init speed");
					/* display the current TTY list */
	disp_tty(tt_win);
					/* prompt for options */
	mvwaddstr(tt_win, 15, 20, "A) Add a TTY entry");
	mvwaddstr(tt_win, 16, 20, "D) Delete a TTY entry");
	horizontal(tt_win, 19, 0, 80);
	mvwattrstr(tt_win, 20, 0, A_BOLD, "OPTION ==> ");
	mvwaddstr(tt_win, 20, 58, "Press <ESC> to return");
	wmove(tt_win, 20, 12);
	touchwin(tt_win);
	wrefresh(tt_win);
					/* get the option */
	ret_code = 0;
	while ((str = get_str(tt_win, 2, "01234356789AaDd", "")) != NULL) {
		switch(*str) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				i = atoi(str);
					/* if beyond t_entries */
				if (i > modem->t_entries) {
					beep();
					break;
				}

					/* change the entry  */
				if (tty_prompt(tt_win, i-1)) {

					/* requires modem update? */
					create_modem(modem->tname[i-1]);
					del_modem();
					ret_code++;
				}
				break;
			case 'a':
			case 'A':	/* add an entry */
				if (modem->t_entries == NUM_TTY) {
					sprintf(message, "\"%s\"", modem->m_path);
					error_win(0, "No empty TTY slots in modem/TTY database", message);
					break;
				}
					/* prompt for info */
				j = modem->t_entries;
				if (tty_prompt(tt_win, j)) {

					/* add modem entry? */
					modem->t_entries++;
					create_modem(modem->tname[j]);
					ret_code++;
				}
				break;
			case 'd':
			case 'D':	/* delete an entry */
				mvwaddstr(tt_win, 21, 0, "Entry number to delete: ");
				wrefresh(tt_win);
				while ((num = get_num(tt_win, 4)) != -1) {
					/* valid range */
					if (!num || num>modem->t_entries) {
						beep();
						mvwaddstr(tt_win, 21, 24, "   ");
						wmove(tt_win, 21, 24);
						wrefresh(tt_win);
						continue;
					}
					del_tty(num-1);
					del_modem();

					/* show the new list */
					disp_tty(tt_win);
					ret_code++;
					break;
				}
				break;
			default:
				beep();
				break;
		}
		mvwaddstr(tt_win, 20, 12, "  ");
		clear_line(tt_win, 21, 0, FALSE);
		clear_line(tt_win, 22, 0, FALSE);
		wmove(tt_win, 20, 12);
		wrefresh(tt_win);
	}
	delwin(tt_win);
	return(ret_code);
}