/*
 * Set up the input pointers while copying the mail file into /tmp.
 */
void
setptr(FILE *ibuf, off_t offset)
{
	int c, count;
	char *cp, *cp2;
	struct message this;
	FILE *mestmp;
	int maybe, inhead;
	char linebuf[LINESIZE], pathbuf[PATHSIZE];
	int omsgCount;

	/* Get temporary file. */
	(void)snprintf(pathbuf, sizeof(pathbuf), "%s/mail.XXXXXXXXXX", tmpdir);
	if ((c = mkstemp(pathbuf)) == -1 || (mestmp = Fdopen(c, "r+")) == NULL)
		err(1, "can't open %s", pathbuf);
	(void)rm(pathbuf);

	if (offset == 0) {
		 msgCount = 0;
	} else {
		/* Seek into the file to get to the new messages */
		(void)fseeko(ibuf, offset, SEEK_SET);
		/*
		 * We need to make "offset" a pointer to the end of
		 * the temp file that has the copy of the mail file.
		 * If any messages have been edited, this will be
		 * different from the offset into the mail file.
		 */
		(void)fseeko(otf, (off_t)0, SEEK_END);
		offset = ftello(otf);
	}
	omsgCount = msgCount;
	maybe = 1;
	inhead = 0;
	this.m_flag = MUSED|MNEW;
	this.m_size = 0;
	this.m_lines = 0;
	this.m_block = 0;
	this.m_offset = 0;
	for (;;) {
		if (fgets(linebuf, sizeof(linebuf), ibuf) == NULL) {
			if (append(&this, mestmp))
				errx(1, "temporary file");
			makemessage(mestmp, omsgCount);
			return;
		}
		count = strlen(linebuf);
		/*
		 * Transforms lines ending in <CR><LF> to just <LF>.
		 * This allows mail to be able to read Eudora mailboxes.
		 */
		if (count >= 2 && linebuf[count - 1] == '\n' &&
		    linebuf[count - 2] == '\r') {
			count--;
			linebuf[count - 1] = '\n';
		}

		(void)fwrite(linebuf, sizeof(*linebuf), count, otf);
		if (ferror(otf))
			errx(1, "/tmp");
		if (count)
			linebuf[count - 1] = '\0';
		if (maybe && linebuf[0] == 'F' && ishead(linebuf)) {
			msgCount++;
			if (append(&this, mestmp))
				errx(1, "temporary file");
			this.m_flag = MUSED|MNEW;
			this.m_size = 0;
			this.m_lines = 0;
			this.m_block = blockof(offset);
			this.m_offset = boffsetof(offset);
			inhead = 1;
		} else if (linebuf[0] == 0) {
			inhead = 0;
		} else if (inhead) {
			for (cp = linebuf, cp2 = "status";; cp++) {
				if ((c = *cp2++) == '\0') {
					while (isspace((unsigned char)*cp++))
						;
					if (cp[-1] != ':')
						break;
					while ((c = *cp++) != '\0')
						if (c == 'R')
							this.m_flag |= MREAD;
						else if (c == 'O')
							this.m_flag &= ~MNEW;
					inhead = 0;
					break;
				}
				if (*cp != c && *cp != toupper((unsigned char)c))
					break;
			}
		}
		offset += count;
		this.m_size += count;
		this.m_lines++;
		maybe = linebuf[0] == 0;
	}
}