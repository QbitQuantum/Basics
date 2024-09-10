int
main(int argc, register char** argv)
{
	register int	n;
	register char*	s;
	char*		args;
	char*		codes;
	char**		av;
	char**		ap;
	int		i;
	int		count;
	int		len;
	int		traverse;
	int		size;
	Dir_t*		firstdir;
	Dir_t*		lastdir;
	Exnode_t*	x;
	Exnode_t*	y;
	Ftw_t		ftw;
	Finddisc_t	disc;

	setlocale(LC_ALL, "");
	error_info.id = "tw";
	av = argv + 1;
	args = 0;
	codes = 0;
	count = 0;
	size = 0;
	traverse = 1;
	firstdir = lastdir = newof(0, Dir_t, 1, 0);
	firstdir->name = ".";
	state.action = LIST;
	state.cmdflags = CMD_EXIT|CMD_IGNORE|CMD_IMPLICIT|CMD_NEWLINE;
	state.errexit = EXIT_QUIT;
	state.ftwflags = ftwflags()|FTW_DELAY;
	state.select = ALL;
	state.separator = '\n';
	memset(&disc, 0, sizeof(disc));
	for (;;)
	{
		switch (optget(argv, usage))
		{
		case 'a':
			args = opt_info.arg;
			state.cmdflags |= CMD_POST;
			continue;
		case 'c':
			if ((count = opt_info.num) < 0)
				error(3, "argument count must be >= 0");
			continue;
		case 'd':
			lastdir = lastdir->next = newof(0, Dir_t, 1, 0);
			lastdir->name = opt_info.arg;
			continue;
		case 'e':
			compile(opt_info.arg, 0);
			continue;
		case 'f':
			state.pattern = opt_info.arg;
			continue;
		case 'i':
			state.ignore = 1;
			continue;
		case 'l':
			state.localfs = 1;
			continue;
		case 'm':
			state.intermediate = 1;
			continue;
		case 'n':
			traverse = 0;
			continue;
		case 'p':
			state.ftwflags |= FTW_TWICE;
			continue;
		case 'q':
			state.cmdflags |= CMD_QUERY;
			continue;
		case 'r':
			state.ftwflags |= FTW_RECURSIVE;
			continue;
		case 's':
			if ((size = opt_info.num) < 0)
				error(3, "command size must be >= 0");
			continue;
		case 't':
			state.cmdflags |= CMD_TRACE;
			continue;
		case 'x':
			state.errexit = opt_info.arg ? opt_info.num : EXIT_QUIT;
			continue;
		case 'z':
			if (s = sfgetr(sfstdin, '\n', 1))
			{
				if (!(s = strdup(s)))
					error(ERROR_SYSTEM|3, "out of space");
				n = state.snapshot.format.delim = *s++;
				state.snapshot.format.path = s;
				if (!(s = strchr(s, n)))
				{
				osnap:
					error(3, "invalid snapshot on standard input");
				}
				*s++ = 0;
				if (!streq(state.snapshot.format.path, SNAPSHOT_ID))
					goto osnap;
				state.snapshot.format.path = s;
				if (!(s = strchr(s, n)))
					goto osnap;
				*s++ = 0;
				state.snapshot.format.easy = s;
				if (!(s = strchr(s, n)))
					goto osnap;
				*s++ = 0;
				if (*(state.snapshot.format.hard = s))
				{
					if (!(s = strchr(s, n)))
						goto osnap;
					*s = 0;
				}
				else
					state.snapshot.format.hard = 0;
				state.snapshot.sp = sfstdin;
				state.snapshot.prev = sfgetr(sfstdin, '\n', 0);
			}
			else
			{
				state.snapshot.format.path = SNAPSHOT_PATH;
				state.snapshot.format.easy = SNAPSHOT_EASY;
				state.snapshot.format.hard = SNAPSHOT_HARD;
				state.snapshot.format.delim = SNAPSHOT_DELIM[0];
			}
			if (!(state.snapshot.tmp = sfstropen()))
				error(ERROR_SYSTEM|3, "out of space");
			compile("sort:name;", 0);
			continue;
		case 'C':
			state.ftwflags |= FTW_NOSEEDOTDIR;
			continue;
		case 'D':
			error_info.trace = -opt_info.num;
			continue;
		case 'E':
			compile(opt_info.arg, 1);
			continue;
		case 'F':
			codes = opt_info.arg;
			continue;
		case 'G':
			disc.flags |= FIND_GENERATE;
			if (streq(opt_info.arg, "old"))
				disc.flags |= FIND_OLD;
			else if (streq(opt_info.arg, "gnu") || streq(opt_info.arg, "locate"))
				disc.flags |= FIND_GNU;
			else if (streq(opt_info.arg, "type"))
				disc.flags |= FIND_TYPE;
			else if (streq(opt_info.arg, "?"))
			{
				error(2, "formats are { default|dir type old gnu|locate }");
				return 0;
			}
			else if (!streq(opt_info.arg, "-") && !streq(opt_info.arg, "default") && !streq(opt_info.arg, "dir"))
				error(3, "%s: invalid find codes format -- { default|dir type old gnu|locate } expected", opt_info.arg);
			continue;
		case 'H':
			state.ftwflags |= FTW_META|FTW_PHYSICAL;
			continue;
		case 'I':
			state.icase = 1;
			continue;
		case 'L':
			state.ftwflags &= ~(FTW_META|FTW_PHYSICAL|FTW_SEEDOTDIR);
			continue;
		case 'P':
			state.ftwflags &= ~FTW_META;
			state.ftwflags |= FTW_PHYSICAL;
			continue;
		case 'S':
			state.separator = *opt_info.arg;
			continue;
		case 'X':
			state.ftwflags |= FTW_MOUNT;
			continue;
		case '?':
			error(ERROR_USAGE|4, "%s", opt_info.arg);
			continue;
		case ':':
			error(2, "%s", opt_info.arg);
			continue;
		}
		break;
	}
	argv += opt_info.index;
	argc -= opt_info.index;
	if (error_info.errors)
		error(ERROR_USAGE|4, "%s", optusage(NiL));

	/*
	 * do it
	 */

	if (state.snapshot.tmp)
		sfprintf(sfstdout, "%c%s%c%s%c%s%c%s%c\n",
			state.snapshot.format.delim, SNAPSHOT_ID,
			state.snapshot.format.delim, state.snapshot.format.path,
			state.snapshot.format.delim, state.snapshot.format.easy,
			state.snapshot.format.delim, state.snapshot.format.hard ? state.snapshot.format.hard : "",
			state.snapshot.format.delim);
	if (x = exexpr(state.program, "begin", NiL, 0))
		eval(x, NiL);
	if ((x = exexpr(state.program, "select", NiL, INTEGER)) || (x = exexpr(state.program, NiL, NiL, INTEGER)))
		state.select = x;
	if (!(state.ftwflags & FTW_PHYSICAL))
		state.ftwflags &= ~FTW_DELAY;
	memset(&ftw, 0, sizeof(ftw));
	ftw.path = ftw.name = "";
	if (traverse)
	{
		if (x = exexpr(state.program, "action", NiL, 0))
			state.action = x;
		if (x = exexpr(state.program, "sort", NiL, 0))
		{
			state.sortkey = x;
			y = 0;
			for (;;)
			{
				switch (x->op)
				{
				case ',':
					y = x->data.operand.right;
					/*FALLTHROUGH*/
				case '!':
				case '~':
				case S2B:
				case X2I:
					x = x->data.operand.left;
					continue;
				case ID:
					if (!(x = y))
						break;
					y = 0;
					continue;
				default:
					error(3, "invalid sort identifier (op 0x%02x)", x->op);
					break;
				}
				break;
			}
			state.sort = order;
		}
		if (*argv && (*argv)[0] == '-' && (*argv)[1] == 0)
		{
			state.ftwflags |= FTW_LIST;
			argv++;
			argc--;
		}
		if (*argv || args || count || !(state.cmdflags & CMD_IMPLICIT))
		{
			Cmddisc_t	disc;

			CMDDISC(&disc, state.cmdflags, errorf);
			state.cmd = cmdopen(argv, count, size, args, &disc);
			state.ftwflags |= FTW_DOT;
		}
		else
			state.cmdflags &= ~CMD_IMPLICIT;
		if (codes && (disc.flags & FIND_GENERATE))
		{
			char*	p;
			Dir_t*	dp;
			char	pwd[PATH_MAX];
			char	tmp[PATH_MAX];

			disc.version = FIND_VERSION;
			if (state.cmdflags & CMD_TRACE)
				disc.flags |= FIND_TYPE;
			if (state.cmdflags & CMD_QUERY)
				disc.flags |= FIND_OLD;
			disc.errorf = errorf;
			if (!(state.find = findopen(codes, NiL, NiL, &disc)))
				exit(2);
			if (disc.flags & FIND_TYPE)
			{
				state.act = ACT_CODETYPE;
				compile("_tw_init:mime;", 0);
				state.magicdisc.flags |= MAGIC_MIME;
			}
			else
				state.act = ACT_CODE;
			state.icase = 1;
			state.pattern = 0;
			state.sort = order;
			if (!state.program)
				compile("1", 0);
			if (!(state.sortkey = newof(0, Exnode_t, 1, 0)) || !(state.sortkey->data.variable.symbol = (Exid_t*)dtmatch(state.program->symbols, "name")))
				error(ERROR_SYSTEM|3, "out of space");
			state.sortkey->op = ID;
			s = p = 0;
			for (dp = (firstdir == lastdir) ? firstdir : firstdir->next; dp; dp = dp->next)
			{
				if (*(s = dp->name) == '/')
					sfsprintf(tmp, sizeof(tmp), "%s", s);
				else if (!p && !(p = getcwd(pwd, sizeof(pwd))))
					error(ERROR_SYSTEM|3, "cannot determine pwd path");
				else
					sfsprintf(tmp, sizeof(tmp), "%s/%s", p, s);
				pathcanon(tmp, sizeof(tmp), PATH_PHYSICAL);
				if (!(dp->name = strdup(tmp)))
					error(ERROR_SYSTEM|3, "out of space [PATH_PHYSICAL]");
			}
		}
		else if (state.snapshot.tmp)
			state.act = ACT_SNAPSHOT;
		else if (state.cmdflags & CMD_IMPLICIT)
			state.act = ACT_CMDARG;
		else if (state.action == LIST)
			state.act = ACT_LIST;
		else if (state.action)
			state.act = ACT_EVAL;
		if (state.intermediate)
		{
			state.actII = state.act;
			state.act = ACT_INTERMEDIATE;
		}
		if (state.pattern)
		{
			disc.version = FIND_VERSION;
			if (state.icase)
				disc.flags |= FIND_ICASE;
			disc.errorf = errorf;
			disc.dirs = ap = av;
			if (firstdir != lastdir)
				firstdir = firstdir->next;
			do {*ap++ = firstdir->name;} while (firstdir = firstdir->next);
			*ap = 0;
			if (!(state.find = findopen(codes, state.pattern, NiL, &disc)))
				exit(1);
			state.ftwflags |= FTW_TOP;
			n = state.select == ALL ? state.act : ACT_EVAL;
			while (s = findread(state.find))
			{
				switch (n)
				{
				case ACT_CMDARG:
					if ((i = cmdarg(state.cmd, s, strlen(s))) >= state.errexit)
						exit(i);
					break;
				case ACT_LIST:
					sfputr(sfstdout, s, '\n');
					break;
				default:
					ftwalk(s, tw, state.ftwflags, NiL);
					break;
				}
			}
		}
		else if (state.ftwflags & FTW_LIST)
		{
			sfopen(sfstdin, NiL, "rt");
			n = state.select == ALL && state.act == ACT_CMDARG;
			for (;;)
			{
				if (s = sfgetr(sfstdin, state.separator, 1))
					len = sfvalue(sfstdin) - 1;
				else if (state.separator != '\n')
				{
					state.separator = '\n';
					continue;
				}
				else if (s = sfgetr(sfstdin, state.separator, -1))
					len = sfvalue(sfstdin);
				else
					break;
				if (!n)
					ftwalk(s, tw, state.ftwflags, NiL);
				else if ((i = cmdarg(state.cmd, s, len)) >= state.errexit)
					exit(i);
			}
			if (sferror(sfstdin))
				error(ERROR_SYSTEM|2, "input read error");
		}
		else if (firstdir == lastdir)
			ftwalk(firstdir->name, tw, state.ftwflags, state.sort);
		else
		{
			ap = av;
			while (firstdir = firstdir->next)
				*ap++ = firstdir->name;
			*ap = 0;
			ftwalk((char*)av, tw, state.ftwflags|FTW_MULTIPLE, state.sort);
		}
		if (state.cmd && (i = cmdflush(state.cmd)) >= state.errexit)
			exit(i);
		if (state.find && (findclose(state.find) || state.finderror))
			exit(2);
	}
	else if (state.select)
		error_info.errors = eval(state.select, &ftw) == 0;
	if (x = exexpr(state.program, "end", NiL, 0))
		eval(x, &ftw);
	if (sfsync(sfstdout))
		error(ERROR_SYSTEM|2, "write error");
	exit(error_info.errors != 0);
}