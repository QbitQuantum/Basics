/*
 * Save all of the undetermined messages at the top of "mbox"
 * Save all untouched messages back in the system mailbox.
 * Remove the system mailbox, if none saved there.
 */
void
quit()
{
	int mcount, p, modify, autohold, anystat, holdbit, nohold;
	FILE *ibuf, *obuf, *fbuf, *rbuf, *readstat, *abuf;
	register struct message *mp;
	register int c;
	extern char tempQuit[], tempResid[];
	struct stat minfo;
	char *mbox;

	/*
	 * If we are read only, we can't do anything,
	 * so just return quickly.
	 */
	if (readonly)
		return;
	/*
	 * If editing (not reading system mail box), then do the work
	 * in edstop()
	 */
	if (edit) {
		edstop();
		return;
	}

	/*
	 * See if there any messages to save in mbox.  If no, we
	 * can save copying mbox to /tmp and back.
	 *
	 * Check also to see if any files need to be preserved.
	 * Delete all untouched messages to keep them out of mbox.
	 * If all the messages are to be preserved, just exit with
	 * a message.
	 */

	fbuf = Fopen(mailname, "r");
	if (fbuf == NULL)
		goto newmail;
	flock(fileno(fbuf), LOCK_EX);
	rbuf = NULL;
	if (fstat(fileno(fbuf), &minfo) >= 0 && minfo.st_size > mailsize) {
		printf("New mail has arrived.\n");
		rbuf = Fopen(tempResid, "w");
		if (rbuf == NULL || fbuf == NULL)
			goto newmail;
#ifdef APPEND
		fseek(fbuf, (long)mailsize, 0);
		while ((c = getc(fbuf)) != EOF)
			(void) putc(c, rbuf);
#else
		p = minfo.st_size - mailsize;
		while (p-- > 0) {
			c = getc(fbuf);
			if (c == EOF)
				goto newmail;
			(void) putc(c, rbuf);
		}
#endif
		Fclose(rbuf);
		if ((rbuf = Fopen(tempResid, "r")) == NULL)
			goto newmail;
		rm(tempResid);
	}

	/*
	 * Adjust the message flags in each message.
	 */

	anystat = 0;
	autohold = value("hold") != NOSTR;
	holdbit = autohold ? MPRESERVE : MBOX;
	nohold = MBOX|MSAVED|MDELETED|MPRESERVE;
	if (value("keepsave") != NOSTR)
		nohold &= ~MSAVED;
	for (mp = &message[0]; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MNEW) {
			mp->m_flag &= ~MNEW;
			mp->m_flag |= MSTATUS;
		}
		if (mp->m_flag & MSTATUS)
			anystat++;
		if ((mp->m_flag & MTOUCH) == 0)
			mp->m_flag |= MPRESERVE;
		if ((mp->m_flag & nohold) == 0)
			mp->m_flag |= holdbit;
	}
	modify = 0;
	if (Tflag != NOSTR) {
		if ((readstat = Fopen(Tflag, "w")) == NULL)
			Tflag = NOSTR;
	}
	for (c = 0, p = 0, mp = &message[0]; mp < &message[msgCount]; mp++) {
		if (mp->m_flag & MBOX)
			c++;
		if (mp->m_flag & MPRESERVE)
			p++;
		if (mp->m_flag & MODIFY)
			modify++;
		if (Tflag != NOSTR && (mp->m_flag & (MREAD|MDELETED)) != 0) {
			char *id;

			if ((id = hfield("article-id", mp)) != NOSTR)
				fprintf(readstat, "%s\n", id);
		}
	}
	if (Tflag != NOSTR)
		Fclose(readstat);
	if (p == msgCount && !modify && !anystat) {
		printf("Held %d message%s in %s\n",
			p, p == 1 ? "" : "s", mailname);
		Fclose(fbuf);
		return;
	}
	if (c == 0) {
		if (p != 0) {
			writeback(rbuf);
			Fclose(fbuf);
			return;
		}
		goto cream;
	}

	/*
	 * Create another temporary file and copy user's mbox file
	 * darin.  If there is no mbox, copy nothing.
	 * If he has specified "append" don't copy his mailbox,
	 * just copy saveable entries at the end.
	 */

	mbox = expand("&");
	mcount = c;
	if (value("append") == NOSTR) {
		if ((obuf = Fopen(tempQuit, "w")) == NULL) {
			perror(tempQuit);
			Fclose(fbuf);
			return;
		}
		if ((ibuf = Fopen(tempQuit, "r")) == NULL) {
			perror(tempQuit);
			rm(tempQuit);
			Fclose(obuf);
			Fclose(fbuf);
			return;
		}
		rm(tempQuit);
		if ((abuf = Fopen(mbox, "r")) != NULL) {
			while ((c = getc(abuf)) != EOF)
				(void) putc(c, obuf);
			Fclose(abuf);
		}
		if (ferror(obuf)) {
			perror(tempQuit);
			Fclose(ibuf);
			Fclose(obuf);
			Fclose(fbuf);
			return;
		}
		Fclose(obuf);
		close(creat(mbox, 0600));
		if ((obuf = Fopen(mbox, "r+")) == NULL) {
			perror(mbox);
			Fclose(ibuf);
			Fclose(fbuf);
			return;
		}
	}
	if (value("append") != NOSTR) {
		if ((obuf = Fopen(mbox, "a")) == NULL) {
			perror(mbox);
			Fclose(fbuf);
			return;
		}
		fchmod(fileno(obuf), 0600);
	}
	for (mp = &message[0]; mp < &message[msgCount]; mp++)
		if (mp->m_flag & MBOX)
			if (send(mp, obuf, saveignore, NOSTR) < 0) {
				perror(mbox);
				Fclose(ibuf);
				Fclose(obuf);
				Fclose(fbuf);
				return;
			}

	/*
	 * Copy the user's old mbox contents back
	 * to the end of the stuff we just saved.
	 * If we are appending, this is unnecessary.
	 */

	if (value("append") == NOSTR) {
		rewind(ibuf);
		c = getc(ibuf);
		while (c != EOF) {
			(void) putc(c, obuf);
			if (ferror(obuf))
				break;
			c = getc(ibuf);
		}
		Fclose(ibuf);
	}
	fflush(obuf);
	trunc(obuf);
	if (ferror(obuf)) {
		perror(mbox);
		Fclose(obuf);
		Fclose(fbuf);
		return;
	}
	Fclose(obuf);
	if (mcount == 1)
		printf("Saved 1 message in mbox\n");
	else
		printf("Saved %d messages in mbox\n", mcount);

	/*
	 * Now we are ready to copy back preserved files to
	 * the system mailbox, if any were requested.
	 */

	if (p != 0) {
		writeback(rbuf);
		Fclose(fbuf);
		return;
	}

	/*
	 * Finally, remove his /usr/mail file.
	 * If new mail has arrived, copy it back.
	 */

cream:
	if (rbuf != NULL) {
		abuf = Fopen(mailname, "r+");
		if (abuf == NULL)
			goto newmail;
		while ((c = getc(rbuf)) != EOF)
			(void) putc(c, abuf);
		Fclose(rbuf);
		trunc(abuf);
		Fclose(abuf);
		alter(mailname);
		Fclose(fbuf);
		return;
	}
	demail();
	Fclose(fbuf);
	return;

newmail:
	printf("Thou hast new mail.\n");
	if (fbuf != NULL)
		Fclose(fbuf);
}