int get_spell(int *sn, cptr p, cptr prompt, int *bn, bool known)
{
	int		i, num = 0;
	bool		flag, redraw;
	char		choice;
	event_type	ke;
	char		out_val[160];
	int			book = (*bn);
	int			book_over = 0;
	int			book_start = book;

	/* HACK -- spellcasting mode -- spell already selected */
	if (spellcasting_spell > -1)
	{
		(*sn) = spellcasting_spell;
		spellcasting = FALSE;
		spellcasting_spell = -1;
		return (TRUE);
	}

	/* Assume no spells available */
	(*sn) = -2;

	/* Check for available spells */
	num = count_spells_in_book(book, &book_over);

	/* No "okay" spells */
	if (!num) return (FALSE);

	/* Assume cancelled */
	(*sn) = -1;

	/* Nothing chosen yet */
	flag = FALSE;

	/* No redraw yet */
	redraw = FALSE;

	/* Show the list */
	if (auto_showlist)
	{
		/* Show list */
		redraw = TRUE;

		/* Save the screen */
		Term_save();

		/* Display a list of spells */
		print_spells(book);
	}

	/* Build a prompt (accept all spells) */
	strnfmt(out_val, 78, "(%s %c-%c, *=List, ESC=exit) %s",
		p, I2A(0), I2A(num - 1), prompt);

	/* Get a spell from the user */
	while (!flag && get_com_ex(out_val, &choice, &ke))
	{
		/* Hack -- mouse */
		if (choice == '\xff' && ke.index == 1)
		{
			choice = 'a' + ke.mousey - 2;
		}

		/* Enter by name */
		if (choice == '@' || choice == '"')
		{
			int _sn, _bn;
			if (choice == '"') prompt_quote_hack = TRUE;
			/* XXX Lookup item by name */
			if (get_spell_by_name(&_bn, &_sn, TRUE, FALSE, FALSE))
			{
				book = _bn;
				i = _sn;
				flag = TRUE;
			}
			else
			{
				bell();
			}
			continue;
		}

		/* Flip page */
		if (choice == '/')
		{
			int book_new = book; 
			int tmp = 0;
			
			/* End of list */
			if (!(num = count_spells_in_book(book + book_over, &tmp)))
			{
				/* Set 0 */ 
				book_new = book_start;
				tmp = 0;
				num = count_spells_in_book(book_new, &tmp);
				book_over = tmp;
			}
			/* Next book available */
			else
			{
				/* Advance */
				book_new = book + book_over;
				book_over = tmp;
			}
			/* Notice flip! */
			if (book_new != book)
			{
				/* Set */
				book = book_new;
				
				/* Re-Build a prompt (accept all spells) */
				strnfmt(out_val, 78, "(%s %c-%c, *=List, ESC=exit) %s",
					p, I2A(0), I2A(num - 1), prompt);

				/* Must redraw list */
				if (redraw)
				{
					/* Restore the screen */
					Term_load();
					Term_save();
	
					/* Display a list of spells */
					print_spells(book);
				}
			}
			/* Ask again */
			continue;
		}
		/* Request redraw */
		if ((choice == ' ') || (choice == '*') || (choice == '?'))
		{
			/* Show the list */
			if (!redraw)
			{
				/* Show list */
				redraw = TRUE;

				/* Save the screen */
				Term_save();

				/* Display a list of spells */
				print_spells(book);
			}

			/* Hide the list */
			else
			{
				/* Hide list */
				redraw = FALSE;

				/* Restore the screen */
				Term_load();

				/* The screen is OK now */
				section_icky_row = 0;
				section_icky_col = 0;

				/* Flush any events */
				Flush_queue();
			}

			/* Ask again */
			continue;
		}

		/* hack for CAPITAL prayers (heal other) */
		if (isupper(choice))
		{
			i = (choice - 'A');
			if (i >= num) i = -1;
			else if (!(spell_flag[(book * SPELLS_PER_BOOK + i)] & PY_SPELL_PROJECT)) i = -1;
			if (i != -1)
				i += SPELL_PROJECTED;
		}
		/* lowercase */
		else if (islower(choice))
		{
			i = A2I(choice);
			if (i >= num) i = -1;
		}
		/* not a letter */
		else i = -1;

		/* Totally Illegal */
		if (i < 0)
		{
			bell();
			continue;
		}

		/* Stop the loop */
		flag = TRUE;
	}

	/* Restore the screen */
	if (redraw)
	{
		Term_load();

		/* The screen is OK now */
		section_icky_row = 0;
		section_icky_col = 0;

		/* Flush any events */
		Flush_queue();
	}


	/* Abort if needed */
	if (!flag) return (FALSE);

	/* Save the choice */
	(*sn) = i;
	(*bn) = book;

	/* Success */
	return (TRUE);
}