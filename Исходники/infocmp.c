static void
analyze_string(const char *name, const char *cap, TERMTYPE *tp)
{
    char buf2[MAX_TERMINFO_LENGTH];
    const char *sp;
    const assoc *ap;
    int tp_lines = tp->Numbers[2];

    if (cap == ABSENT_STRING || cap == CANCELLED_STRING)
	return;
    (void) printf("%s: ", name);

    for (sp = cap; *sp; sp++) {
	int i;
	int csi;
	size_t len = 0;
	size_t next;
	const char *expansion = 0;
	char buf3[MAX_TERMINFO_LENGTH];

	/* first, check other capabilities in this entry */
	for (i = 0; i < STRCOUNT; i++) {
	    char *cp = tp->Strings[i];

	    /* don't use soft-key capabilities */
	    if (strnames[i][0] == 'k' && strnames[i][0] == 'f')
		continue;

	    if (cp != ABSENT_STRING && cp != CANCELLED_STRING && cp[0] && cp
		!= cap) {
		len = strlen(cp);
		(void) strncpy(buf2, sp, len);
		buf2[len] = '\0';

		if (_nc_capcmp(cp, buf2))
		    continue;

#define ISRS(s)	(!strncmp((s), "is", 2) || !strncmp((s), "rs", 2))
		/*
		 * Theoretically we just passed the test for translation
		 * (equality once the padding is stripped).  However, there
		 * are a few more hoops that need to be jumped so that
		 * identical pairs of initialization and reset strings
		 * don't just refer to each other.
		 */
		if (ISRS(name) || ISRS(strnames[i]))
		    if (cap < cp)
			continue;
#undef ISRS

		expansion = strnames[i];
		break;
	    }
	}

	/* now check the standard capabilities */
	if (!expansion) {
	    csi = skip_csi(sp);
	    for (ap = std_caps; ap->from; ap++) {
		size_t adj = (size_t) (csi ? 2 : 0);

		len = strlen(ap->from);
		if (csi && skip_csi(ap->from) != csi)
		    continue;
		if (len > adj
		    && strncmp(ap->from + adj, sp + csi, len - adj) == 0) {
		    expansion = ap->to;
		    len -= adj;
		    len += (size_t) csi;
		    break;
		}
	    }
	}

	/* now check for standard-mode sequences */
	if (!expansion
	    && (csi = skip_csi(sp)) != 0
	    && (len = strspn(sp + csi, "0123456789;"))
	    && (len < sizeof(buf3))
	    && (next = (size_t) csi + len)
	    && ((sp[next] == 'h') || (sp[next] == 'l'))) {

	    (void) strcpy(buf2, (sp[next] == 'h') ? "ECMA+" : "ECMA-");
	    (void) strncpy(buf3, sp + csi, len);
	    buf3[len] = '\0';
	    len += (size_t) csi + 1;

	    expansion = lookup_params(std_modes, buf2, buf3);
	}

	/* now check for private-mode sequences */
	if (!expansion
	    && (csi = skip_csi(sp)) != 0
	    && sp[csi] == '?'
	    && (len = strspn(sp + csi + 1, "0123456789;"))
	    && (len < sizeof(buf3))
	    && (next = (size_t) csi + 1 + len)
	    && ((sp[next] == 'h') || (sp[next] == 'l'))) {

	    (void) strcpy(buf2, (sp[next] == 'h') ? "DEC+" : "DEC-");
	    (void) strncpy(buf3, sp + csi + 1, len);
	    buf3[len] = '\0';
	    len += (size_t) csi + 2;

	    expansion = lookup_params(private_modes, buf2, buf3);
	}

	/* now check for ECMA highlight sequences */
	if (!expansion
	    && (csi = skip_csi(sp)) != 0
	    && (len = strspn(sp + csi, "0123456789;")) != 0
	    && (len < sizeof(buf3))
	    && (next = (size_t) csi + len)
	    && sp[next] == 'm') {

	    (void) strcpy(buf2, "SGR:");
	    (void) strncpy(buf3, sp + csi, len);
	    buf3[len] = '\0';
	    len += (size_t) csi + 1;

	    expansion = lookup_params(ecma_highlights, buf2, buf3);
	}

	if (!expansion
	    && (csi = skip_csi(sp)) != 0
	    && sp[csi] == 'm') {
	    len = (size_t) csi + 1;
	    (void) strcpy(buf2, "SGR:");
	    strcat(buf2, ecma_highlights[0].to);
	    expansion = buf2;
	}

	/* now check for scroll region reset */
	if (!expansion
	    && (csi = skip_csi(sp)) != 0) {
	    if (sp[csi] == 'r') {
		expansion = "RSR";
		len = 1;
	    } else {
		(void) sprintf(buf2, "1;%dr", tp_lines);
		len = strlen(buf2);
		if (strncmp(buf2, sp + csi, len) == 0)
		    expansion = "RSR";
	    }
	    len += (size_t) csi;
	}

	/* now check for home-down */
	if (!expansion
	    && (csi = skip_csi(sp)) != 0) {
	    (void) sprintf(buf2, "%d;1H", tp_lines);
	    len = strlen(buf2);
	    if (strncmp(buf2, sp + csi, len) == 0) {
		expansion = "LL";
	    } else {
		(void) sprintf(buf2, "%dH", tp_lines);
		len = strlen(buf2);
		if (strncmp(buf2, sp + csi, len) == 0) {
		    expansion = "LL";
		}
	    }
	    len += (size_t) csi;
	}

	/* now look at the expansion we got, if any */
	if (expansion) {
	    printf("{%s}", expansion);
	    sp += len - 1;
	} else {
	    /* couldn't match anything */
	    buf2[0] = *sp;
	    buf2[1] = '\0';
	    fputs(TIC_EXPAND(buf2), stdout);
	}
    }
    putchar('\n');
}