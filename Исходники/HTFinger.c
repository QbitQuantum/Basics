static int response(char *command,
		    char *sitename,
		    HTParentAnchor *anAnchor,
		    HTFormat format_out,
		    HTStream *sink)
{
    int status;
    int length = (int) strlen(command);
    int ch, i;
    char line[BIG], *l, *cmd = NULL;
    char *p = line, *href = NULL;

    if (length == 0)
	return (-1);

    /* Set up buffering.
     */
    HTInitInput(finger_fd);

    /* Send the command.
     */
    CTRACE((tfp, "HTFinger command to be sent: %s", command));
    status = (int) NETWRITE(finger_fd, (char *) command, (unsigned) length);
    if (status < 0) {
	CTRACE((tfp, "HTFinger: Unable to send command. Disconnecting.\n"));
	NETCLOSE(finger_fd);
	finger_fd = -1;
	return status;
    }
    /* if bad status */
    /* Make a hypertext object with an anchor list.
     */
    target = HTML_new(anAnchor, format_out, sink);
    targetClass = *target->isa;	/* Copy routine entry points */

    /* Create the results report.
     */
    CTRACE((tfp, "HTFinger: Reading finger information\n"));
    START(HTML_HTML);
    PUTC('\n');
    START(HTML_HEAD);
    PUTC('\n');
    START(HTML_TITLE);
    PUTS("Finger server on ");
    PUTS(sitename);
    END(HTML_TITLE);
    PUTC('\n');
    END(HTML_HEAD);
    PUTC('\n');
    START(HTML_BODY);
    PUTC('\n');
    START(HTML_H1);
    PUTS("Finger server on ");
    START(HTML_EM);
    PUTS(sitename);
    END(HTML_EM);
    PUTS(": ");
    StrAllocCopy(cmd, command);
    for (i = ((int) strlen(cmd) - 1); i >= 0; i--) {
	if (cmd[i] == LF || cmd[i] == CR) {
	    cmd[i] = '\0';
	} else {
	    break;
	}
    }
    PUTS(cmd);
    FREE(cmd);
    END(HTML_H1);
    PUTC('\n');
    START(HTML_PRE);

    while ((ch = NEXT_CHAR) != EOF) {

	if (interrupted_in_htgetcharacter) {
	    CTRACE((tfp,
		    "HTFinger: Interrupted in HTGetCharacter, apparently.\n"));
	    _HTProgress(CONNECTION_INTERRUPTED);
	    goto end_html;
	}

	if (ch != LF) {
	    *p = (char) ch;	/* Put character in line */
	    if (p < &line[BIG - 1]) {
		p++;
	    }
	} else {
	    *p = '\0';		/* Terminate line */
	    /*
	     * OK we now have a line.
	     * Load it as 'l' and parse it.
	     */
	    p = l = line;
	    while (*l) {
		if (StrNCmp(l, STR_NEWS_URL, LEN_NEWS_URL) &&
		    StrNCmp(l, "snews://", 8) &&
		    StrNCmp(l, "nntp://", 7) &&
		    StrNCmp(l, "snewspost:", 10) &&
		    StrNCmp(l, "snewsreply:", 11) &&
		    StrNCmp(l, "newspost:", 9) &&
		    StrNCmp(l, "newsreply:", 10) &&
		    StrNCmp(l, "ftp://", 6) &&
		    StrNCmp(l, "file:/", 6) &&
		    StrNCmp(l, "finger://", 9) &&
		    StrNCmp(l, "http://", 7) &&
		    StrNCmp(l, "https://", 8) &&
		    StrNCmp(l, "wais://", 7) &&
		    StrNCmp(l, STR_MAILTO_URL, LEN_MAILTO_URL) &&
		    StrNCmp(l, "cso://", 6) &&
		    StrNCmp(l, "gopher://", 9))
		    PUTC(*l++);
		else {
		    StrAllocCopy(href, l);
		    start_anchor(strtok(href, " \r\n\t,>)\""));
		    while (*l && !StrChr(" \r\n\t,>)\"", *l))
			PUTC(*l++);
		    END(HTML_A);
		    FREE(href);
		}
	    }
	    PUTC('\n');
	}
    }
    NETCLOSE(finger_fd);
    finger_fd = -1;

  end_html:
    END(HTML_PRE);
    PUTC('\n');
    END(HTML_BODY);
    PUTC('\n');
    END(HTML_HTML);
    PUTC('\n');
    FREE_TARGET;
    return (0);
}