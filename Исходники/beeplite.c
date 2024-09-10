static int
makelite(struct distress *dist, char *pm)
{
    struct player *sender;
    struct player *j;
    struct planet *l;
    char    c;
    W_Color lcol;

    sender = &players[dist->sender];

    if (!(*pm)) {
	return (0);
    }
    /* first step is to substitute variables */
    while (*pm) {
	if (*pm == '/') {
	    pm++;

	    if (!pm)
		continue;

	    if (F_beeplite_flags & LITE_COLOR) {
		/* color lite -JR */
		switch (toupper(*(pm + 1))) {
		case 'G':
		    lcol = W_Green;
		    break;
		case 'Y':
		    lcol = W_Yellow;
		    break;
		case 'R':
		    lcol = W_Red;
		    break;
		case 'C':
		    lcol = W_Cyan;
		    break;
		case 'E':
		    lcol = W_Grey;
		    break;
		case 'W':
		default:
		    lcol = W_White;
		    break;
		}
	    } else
		lcol = W_White;

	    switch (c = *(pm++)) {

	    case 'P':		/* push player id into buf */
	    case 'G':		/* push friendly player id into buf */
	    case 'H':		/* push enemy target player id into buf */

	    case 'p':		/* push player id into buf */
	    case 'g':		/* push friendly player id into buf */
	    case 'h':		/* push enemy target player id into buf */

		switch (c) {
		case 'p':
		    j = &players[dist->tclose_j];
		    break;
		case 'g':
		    j = &players[dist->tclose_fr];
		    break;
		case 'h':
		    j = &players[dist->tclose_en];
		    break;
		case 'P':
		    j = &players[dist->close_j];
		    break;
		case 'G':
		    j = &players[dist->close_fr];
		    break;
		default:
		    j = &players[dist->close_en];
		    break;
		}
		liteplayer(j, lcol);
		break;

	    case 'B':		/* highlites planet nearest sender */
	    case 'b':
		l = &planets[dist->close_pl];
		liteplanet(l, lcol);
		break;
	    case 'L':		/* highlites planet nearest pointer */
	    case 'l':
		l = &planets[dist->tclose_pl];
		liteplanet(l, lcol);
		break;
	    case 'U':		/* highlites enemy nearest pointer */
	    case 'u':
		j = &players[dist->tclose_en];
		liteplayer(j, lcol);
		break;
	    case 'c':		/* highlites sender */
	    case 'I':
	    case 'i':
		liteplayer(sender, lcol);
		break;
	    case 'M':		/* highlites me */
	    case 'm':
		liteplayer(me, lcol);
		break;
	    case '0':
		if (F_beeplite_flags & LITE_SOUNDS)
		    W_Beep();
		break;
	    default:
/* try to continue
** bad macro character is skipped entirely,
** the message will be parsed without whatever argument has occurred. - jn
*/
		warning("Bad Macro character in distress!");
		fprintf(stderr, "Unrecognizable special character in "
		                "distress pass 1: %c\n", *(pm - 1));
		break;
	    }
	} else {
	    pm++;
	}

    }


    return (1);
}