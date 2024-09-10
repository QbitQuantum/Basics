static void eraser(unsigned char c, struct tty_struct *tty)
{
	enum { ERASE, WERASE, KILL } kill_type;
	int head, seen_alnums, cnt;
	unsigned long flags;

	if (tty->read_head == tty->canon_head) {
		/* opost('\a', tty); */		/* what do you think? */
		return;
	}
	if (c == ERASE_CHAR(tty))
		kill_type = ERASE;
	else if (c == WERASE_CHAR(tty))
		kill_type = WERASE;
	else {
		if (!L_ECHO(tty)) {
			spin_lock_irqsave(&tty->read_lock, flags);
			tty->read_cnt -= ((tty->read_head - tty->canon_head) &
					  (N_TTY_BUF_SIZE - 1));
			tty->read_head = tty->canon_head;
			spin_unlock_irqrestore(&tty->read_lock, flags);
			return;
		}
		if (!L_ECHOK(tty) || !L_ECHOKE(tty) || !L_ECHOE(tty)) {
			spin_lock_irqsave(&tty->read_lock, flags);
			tty->read_cnt -= ((tty->read_head - tty->canon_head) &
					  (N_TTY_BUF_SIZE - 1));
			tty->read_head = tty->canon_head;
			spin_unlock_irqrestore(&tty->read_lock, flags);
			finish_erasing(tty);
			echo_char(KILL_CHAR(tty), tty);
			/* Add a newline if ECHOK is on and ECHOKE is off. */
			if (L_ECHOK(tty))
				opost('\n', tty);
			return;
		}
		kill_type = KILL;
	}

	seen_alnums = 0;
	while (tty->read_head != tty->canon_head) {
		head = tty->read_head;

		/* erase a single possibly multibyte character */
		do {
			head = (head - 1) & (N_TTY_BUF_SIZE-1);
			c = tty->read_buf[head];
		} while (is_continuation(c, tty) && head != tty->canon_head);

		/* do not partially erase */
		if (is_continuation(c, tty))
			break;

		if (kill_type == WERASE) {
			/* Equivalent to BSD's ALTWERASE. */
			if (isalnum(c) || c == '_')
				seen_alnums++;
			else if (seen_alnums)
				break;
		}
		cnt = (tty->read_head - head) & (N_TTY_BUF_SIZE-1);
		spin_lock_irqsave(&tty->read_lock, flags);
		tty->read_head = head;
		tty->read_cnt -= cnt;
		spin_unlock_irqrestore(&tty->read_lock, flags);
		if (L_ECHO(tty)) {
			if (L_ECHOPRT(tty)) {
				if (!tty->erasing) {
					put_char('\\', tty);
					tty->column++;
					tty->erasing = 1;
				}
				/* if cnt > 1, output a multi-byte character */
				echo_char(c, tty);
				while (--cnt > 0) {
					head = (head+1) & (N_TTY_BUF_SIZE-1);
					put_char(tty->read_buf[head], tty);
				}
			} else if (kill_type == ERASE && !L_ECHOE(tty)) {
				echo_char(ERASE_CHAR(tty), tty);
			} else if (c == '\t') {
				unsigned int col = tty->canon_column;
				unsigned long tail = tty->canon_head;

				/* Find the column of the last char. */
				while (tail != tty->read_head) {
					c = tty->read_buf[tail];
					if (c == '\t')
						col = (col | 7) + 1;
					else if (iscntrl(c)) {
						if (L_ECHOCTL(tty))
							col += 2;
					} else if (!is_continuation(c, tty))
						col++;
					tail = (tail+1) & (N_TTY_BUF_SIZE-1);
				}

				/* should never happen */
				if (tty->column > 0x80000000)
					tty->column = 0; 

				/* Now backup to that column. */
				while (tty->column > col) {
					/* Can't use opost here. */
					put_char('\b', tty);
					if (tty->column > 0)
						tty->column--;
				}
			} else {
				if (iscntrl(c) && L_ECHOCTL(tty)) {
					put_char('\b', tty);
					put_char(' ', tty);
					put_char('\b', tty);
					if (tty->column > 0)
						tty->column--;
				}
				if (!iscntrl(c) || L_ECHOCTL(tty)) {
					put_char('\b', tty);
					put_char(' ', tty);
					put_char('\b', tty);
					if (tty->column > 0)
						tty->column--;
				}
			}
		}
		if (kill_type == ERASE)
			break;
	}
	if (tty->read_head == tty->canon_head)
		finish_erasing(tty);
}