MESHINST *
getmeshinst(				/* create mesh instance */
	OBJREC	*o,
	int	flags
)
{
	MESHINST  *ins;

	flags &= IO_LEGAL;
	if ((ins = (MESHINST *)o->os) == NULL) {
		if ((ins = (MESHINST *)malloc(sizeof(MESHINST))) == NULL)
			error(SYSTEM, "out of memory in getmeshinst");
		if (o->oargs.nsargs < 1)
			objerror(o, USER, "bad # of arguments");
		if (fullxf(&ins->x, o->oargs.nsargs-1,
				o->oargs.sarg+1) != o->oargs.nsargs-1)
			objerror(o, USER, "bad transform");
		if (ins->x.f.sca < 0.0) {
			ins->x.f.sca = -ins->x.f.sca;
			ins->x.b.sca = -ins->x.b.sca;
		}
		ins->msh = NULL;
		o->os = (char *)ins;
	}
	if (ins->msh == NULL)
		ins->msh = getmesh(o->oargs.sarg[0], flags);
	else if ((flags &= ~ins->msh->ldflags))
		readmesh(ins->msh,
			getpath(o->oargs.sarg[0], getrlibpath(), R_OK),
				flags);
	return(ins);
}