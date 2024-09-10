/*
 *  research_mon
 *  -KMW-
 */
bool research_mon(void)
{
	int i, n, r_idx;
	char sym, query;
	char buf[128];

	s16b oldkills;
	byte oldwake;
	bool oldcheat;

	bool notpicked;

	bool recall = FALSE;

	u16b why = 0;

	monster_race *r2_ptr;

	u16b	*who;

#ifdef JP
	/* XTRA HACK WHATSEARCH */
	bool    all = FALSE;
	bool    uniq = FALSE;
	bool    norm = FALSE;
	char temp[80] = "";

	/* XTRA HACK REMEMBER_IDX */
	static int old_sym = '\0';
	static int old_i = 0;
#endif
	oldcheat = cheat_know;


	/* Save the screen */
	screen_save();

	/* Get a character, or abort */
#ifdef JP
if (!get_com("モンスターの文字を入力して下さい(記号 or ^A全,^Uユ,^N非ユ,^M名前):", &sym)) 
#else
	if (!get_com("Enter character of monster: ", &sym))
#endif

	{
		/* Restore */
		screen_load();

		return (FALSE);
	}

	/* Allocate the "who" array */
	C_MAKE(who, max_r_idx, u16b);

	/* Find that character info, and describe it */
	for (i = 0; ident_info[i]; ++i)
	{
		if (sym == ident_info[i][0]) break;
	}

#ifdef JP
		/* XTRA HACK WHATSEARCH */
	if (sym == KTRL('A'))
	{
		all = TRUE;
		strcpy(buf, "全モンスターのリスト");
	}
	else if (sym == KTRL('U'))
	{
		all = uniq = TRUE;
		strcpy(buf, "ユニーク・モンスターのリスト");
	}
	else if (sym == KTRL('N'))
	{
		all = norm = TRUE;
		strcpy(buf, "ユニーク外モンスターのリスト");
	}
	else if (sym == KTRL('M'))
	{
		all = TRUE;
		if (!get_string("名前(英語の場合小文字で可)", temp, 70))
		{
		     all = FALSE;
		     temp[0] = 0;
		}
		sprintf(buf, "名前:%sにマッチ",temp);
	}

	else if (ident_info[i])
	{
		sprintf(buf, "%c - %s.", sym, ident_info[i] + 2);
	}
#else
	if (ident_info[i])
	{
		sprintf(buf, "%c - %s.", sym, ident_info[i] + 2);
	}
#endif
	else
	{
#ifdef JP
	  sprintf(buf, "%c - %s", sym, "無効な文字");
#else
		sprintf(buf, "%c - %s.", sym, "Unknown Symbol");
#endif

	}

	/* Display the result */
	prt(buf, 16, 10);


	/* Collect matching monsters */
	for (n = 0, i = 1; i < max_r_idx; i++)
	{
		monster_race *r_ptr = &r_info[i];

		cheat_know = TRUE;

#ifdef JP
		/* XTRA HACK WHATSEARCH */
		/* Require non-unique monsters if needed */
		if (norm && (r_ptr->flags1 & (RF1_UNIQUE))) continue;

		/* Require unique monsters if needed */
		if (uniq && !(r_ptr->flags1 & (RF1_UNIQUE))) continue;

		/* 名前検索 */
		if (temp[0]){
		    char temp2[80];
		    int xx;

		    for (xx=0; temp[xx] && xx<80; xx++){
		      if (iskanji(temp[xx])) { xx++; continue; }
		      if (isupper(temp[xx])) temp[xx]=tolower(temp[xx]);
		    }

		    strcpy(temp2, r_name+r_ptr->E_name);

		    for (xx=0; temp2[xx] && xx<80; xx++)
		      if (isupper(temp2[xx])) temp2[xx]=tolower(temp2[xx]);

		    if (my_strstr(temp2, temp) || my_strstr(r_name + r_ptr->name, temp) ) who[n++]=i;
		}

		else if (all || (r_ptr->d_char == sym)) who[n++] = i;
#else
		/* Collect "appropriate" monsters */
		if (r_ptr->d_char == sym) who[n++] = i;
#endif
	}

	/* Nothing to recall */
	if (!n)
	{
		cheat_know = oldcheat;

		/* Free the "who" array */
		C_KILL(who, max_r_idx, u16b);

		/* Restore */
		screen_load();

		return (FALSE);
	}

	/* Sort by level */
	why = 2;
	query = 'y';

	/* Sort if needed */
	if (why)
	{
		/* Select the sort method */
		ang_sort_comp = ang_sort_comp_hook;
		ang_sort_swap = ang_sort_swap_hook;

		/* Sort the array */
		ang_sort(who, &why, n);
	}


	/* Start at the end */
#ifdef JP
	/* XTRA HACK REMEMBER_IDX */
	if (old_sym == sym && old_i < n) i = old_i;
	else i = n - 1;
#else
	i = n - 1;
#endif

	notpicked = TRUE;

	/* Scan the monster memory */
	while (notpicked)
	{
		/* Extract a race */
		r_idx = who[i];

		/* Save this monster ID */
		p_ptr->monster_race_idx = r_idx;

		/* Hack -- Handle stuff */
		handle_stuff();

		/* Hack -- Begin the prompt */
		roff_top(r_idx);

		/* Hack -- Complete the prompt */
#ifdef JP
Term_addstr(-1, TERM_WHITE, " ['r'思い出, ' 'で続行, ESC]");
#else
		Term_addstr(-1, TERM_WHITE, " [(r)ecall, ESC, space to continue]");
#endif


		/* Interact */
		while (1)
		{
			/* Recall */
			if (recall)
			{
				/* Recall on screen */
				r2_ptr = &r_info[r_idx];

				oldkills = r2_ptr->r_tkills;
				oldwake = r2_ptr->r_wake;
				screen_roff(who[i], 1);
				r2_ptr->r_tkills = oldkills;
				r2_ptr->r_wake = oldwake;
				cheat_know = oldcheat;
				notpicked = FALSE;
#ifdef JP
				/* XTRA HACK REMEMBER_IDX */
				old_sym = sym;
				old_i = i;
#endif
			}

			/* Command */
			query = inkey();

			/* Normal commands */
			if (query != 'r') break;

			/* Toggle recall */
			recall = !recall;
		}

		/* Stop scanning */
		if (query == ESCAPE) break;

		/* Move to "prev" monster */
		if (query == '-')
		{
			if (++i == n)
			{
				i = 0;
				if (!expand_list) break;
			}
		}

		/* Move to "next" monster */
		else
		{
			if (i-- == 0)
			{
				i = n - 1;
				if (!expand_list) break;
			}
		}
	}


	/* Re-display the identity */
	/* prt(buf, 5, 5);*/

	cheat_know = oldcheat;

	/* Free the "who" array */
	C_KILL(who, max_r_idx, u16b);

	/* Restore */
	screen_load();

	return (!notpicked);
}