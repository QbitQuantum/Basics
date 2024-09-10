int
doglobal(			/* execute a global command */
	PRIMITIVE  *g
)
{
	FILE  *fp = NULL;

	switch (g->com) {

	case PEOF:
		return(0);

	case PPAUS:
		break;

	case PINCL:
		if (g->args == NULL)
		    error(USER, "missing include file name in include");
		if (g->arg0 == 2 || (fp = fopen(g->args, "r")) == NULL) {
		    if (g->arg0 != 0)
			fp = mfopen(g->args, "r");
		    else {
			sprintf(errmsg, "cannot open user include file \"%s\"",
					g->args);
			error(USER, errmsg);
		    }
		}
		plot(fp);
		fclose(fp);
		break;

	case PDRAW:
		fflush(stdout);
		break;

	case PEOP:
		endpage();
		newpage = TRUE;
		break;

	case PSET:
		set(g->arg0, g->args);
		break;

	case PUNSET:
		unset(g->arg0);
		break;

	case PRESET:
		reset(g->arg0);
		break;

	case POPEN:
		segopen(g->args);
		break;

	case PCLOSE:
		segclose();
		break;

	default:
		sprintf(errmsg, "unknown command '%c' in doglobal", g->com);
		error(WARNING, errmsg);
		break;
	}

	return(1);
}