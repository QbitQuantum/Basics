/* Parse the rcfile, once it has been opened successfully at rcstream,
 * and close it afterwards.  If syntax_only is TRUE, only allow the file
 * to contain color syntax commands: syntax, color, and icolor. */
void parse_rcfile(FILE *rcstream
#ifdef ENABLE_COLOR
	, bool syntax_only
#endif
	)
{
    char *buf = NULL;
    ssize_t len;
    size_t n = 0;

    while ((len = getline(&buf, &n, rcstream)) > 0) {
	char *ptr, *keyword, *option;
	int set = 0;
	size_t i;

	/* Ignore the newline. */
	if (buf[len - 1] == '\n')
	    buf[len - 1] = '\0';

	lineno++;
	ptr = buf;
	while (isblank(*ptr))
	    ptr++;

	/* If we have a blank line or a comment, skip to the next
	 * line. */
	if (*ptr == '\0' || *ptr == '#')
	    continue;

	/* Otherwise, skip to the next space. */
	keyword = ptr;
	ptr = parse_next_word(ptr);

	/* Try to parse the keyword. */
	if (strcasecmp(keyword, "set") == 0) {
#ifdef ENABLE_COLOR
	    if (syntax_only)
		rcfile_error(
			N_("Command \"%s\" not allowed in included file"),
			keyword);
	    else
#endif
		set = 1;
	} else if (strcasecmp(keyword, "unset") == 0) {
#ifdef ENABLE_COLOR
	    if (syntax_only)
		rcfile_error(
			N_("Command \"%s\" not allowed in included file"),
			keyword);
	    else
#endif
		set = -1;
	}
#ifdef ENABLE_COLOR
	else if (strcasecmp(keyword, "include") == 0) {
	    if (syntax_only)
		rcfile_error(
			N_("Command \"%s\" not allowed in included file"),
			keyword);
	    else
		parse_include(ptr);
	} else if (strcasecmp(keyword, "syntax") == 0) {
	    if (endsyntax != NULL && endcolor == NULL)
		rcfile_error(N_("Syntax \"%s\" has no color commands"),
			endsyntax->desc);
	    parse_syntax(ptr);
	}
	else if (strcasecmp(keyword, "magic") == 0) {
 	    parse_magictype(ptr);
	} else if (strcasecmp(keyword, "header") == 0)
	    parse_headers(ptr);
	else if (strcasecmp(keyword, "color") == 0)
	    parse_colors(ptr, FALSE);
	else if (strcasecmp(keyword, "icolor") == 0)
	    parse_colors(ptr, TRUE);
	else if (strcasecmp(keyword, "bind") == 0)
	    parse_keybinding(ptr);
	else if (strcasecmp(keyword, "unbind") == 0)
	    parse_unbinding(ptr);
#endif /* ENABLE_COLOR */
	else
	    rcfile_error(N_("Command \"%s\" not understood"), keyword);

	if (set == 0)
	    continue;

	if (*ptr == '\0') {
	    rcfile_error(N_("Missing flag"));
	    continue;
	}

	option = ptr;
	ptr = parse_next_word(ptr);

	for (i = 0; rcopts[i].name != NULL; i++) {
	    if (strcasecmp(option, rcopts[i].name) == 0) {
#ifdef DEBUG
		fprintf(stderr, "parse_rcfile(): name = \"%s\"\n", rcopts[i].name);
#endif
		if (set == 1) {
		    if (rcopts[i].flag != 0)
			/* This option has a flag, so it doesn't take an
			 * argument. */
			SET(rcopts[i].flag);
		    else {
			/* This option doesn't have a flag, so it takes
			 * an argument. */
			if (*ptr == '\0') {
			    rcfile_error(
				N_("Option \"%s\" requires an argument"),
				rcopts[i].name);
			    break;
			}
			option = ptr;
			if (*option == '"')
			    option++;
			ptr = parse_argument(ptr);

			option = mallocstrcpy(NULL, option);
#ifdef DEBUG
			fprintf(stderr, "option = \"%s\"\n", option);
#endif

			/* Make sure option is a valid multibyte
			 * string. */
			if (!is_valid_mbstring(option)) {
			    rcfile_error(
				N_("Option is not a valid multibyte string"));
			    break;
			}

#ifndef DISABLE_OPERATINGDIR
			if (strcasecmp(rcopts[i].name, "operatingdir") == 0)
			    operating_dir = option;
			else
#endif
#ifndef DISABLE_WRAPJUSTIFY
			if (strcasecmp(rcopts[i].name, "fill") == 0) {
			    if (!parse_num(option, &wrap_at)) {
				rcfile_error(
					N_("Requested fill size \"%s\" is invalid"),
					option);
				wrap_at = -CHARS_FROM_EOL;
			    } else
				free(option);
			} else
#endif
#ifndef NANO_TINY
			if (strcasecmp(rcopts[i].name,
				"matchbrackets") == 0) {
			    matchbrackets = option;
			    if (has_blank_mbchars(matchbrackets)) {
				rcfile_error(
					N_("Non-blank characters required"));
				free(matchbrackets);
				matchbrackets = NULL;
			    }
			} else if (strcasecmp(rcopts[i].name,
				"whitespace") == 0) {
			    whitespace = option;
			    if (mbstrlen(whitespace) != 2 ||
				strlenpt(whitespace) != 2) {
				rcfile_error(
					N_("Two single-column characters required"));
				free(whitespace);
				whitespace = NULL;
			    } else {
				whitespace_len[0] =
					parse_mbchar(whitespace, NULL,
					NULL);
				whitespace_len[1] =
					parse_mbchar(whitespace +
					whitespace_len[0], NULL, NULL);
			    }
			} else
#endif
#ifndef DISABLE_JUSTIFY
			if (strcasecmp(rcopts[i].name, "punct") == 0) {
			    punct = option;
			    if (has_blank_mbchars(punct)) {
				rcfile_error(
					N_("Non-blank characters required"));
				free(punct);
				punct = NULL;
			    }
			} else if (strcasecmp(rcopts[i].name,
				"brackets") == 0) {
			    brackets = option;
			    if (has_blank_mbchars(brackets)) {
				rcfile_error(
					N_("Non-blank characters required"));
				free(brackets);
				brackets = NULL;
			    }
			} else if (strcasecmp(rcopts[i].name,
				"quotestr") == 0)
			    quotestr = option;
			else
#endif
#ifndef NANO_TINY
			if (strcasecmp(rcopts[i].name,
				"backupdir") == 0)
			    backup_dir = option;
			else
#endif
#ifndef DISABLE_SPELLER
			if (strcasecmp(rcopts[i].name, "speller") == 0)
			    alt_speller = option;
			else
#endif
			if (strcasecmp(rcopts[i].name,
				"tabsize") == 0) {
			    if (!parse_num(option, &tabsize) ||
				tabsize <= 0) {
				rcfile_error(
					N_("Requested tab size \"%s\" is invalid"),
					option);
				tabsize = -1;
			    } else
				free(option);
			} else
			    assert(FALSE);
		    }
#ifdef DEBUG
		    fprintf(stderr, "flag = %ld\n", rcopts[i].flag);
#endif
		} else if (rcopts[i].flag != 0)
		    UNSET(rcopts[i].flag);
		else
		    rcfile_error(N_("Cannot unset flag \"%s\""),
			rcopts[i].name);
		/* Looks like we still need this specific hack for undo */
		if (strcasecmp(rcopts[i].name, "undo") == 0)
		    shortcut_init(0);
		break;
	    }
	}
	if (rcopts[i].name == NULL)
	    rcfile_error(N_("Unknown flag \"%s\""), option);
    }

#ifdef ENABLE_COLOR
    if (endsyntax != NULL && endcolor == NULL)
	rcfile_error(N_("Syntax \"%s\" has no color commands"),
		endsyntax->desc);
#endif

    free(buf);
    fclose(rcstream);
    lineno = 0;

    check_vitals_mapped();
    return;
}