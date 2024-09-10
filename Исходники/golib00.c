void mainCRTStartup(void)
{
	struct stack_alloc *pwork, work_image;
	struct str_works works;
	UCHAR *p0;
	int i;

	pwork = (struct stack_alloc *) ((((int) &work_image) + 0x0f) & ~0x0f);
	works.label = works.label0 = pwork->label;
	works.label1 = &pwork->label[sizeof (pwork->label) / sizeof(*pwork->label)];
	works.objs = works.objs0 = pwork->objs;
	works.objs1 = &pwork->objs[sizeof (pwork->objs) / sizeof(*pwork->objs)];
	works.filebuf = works.filebuf0 = pwork->filebuf;
	works.filebuf1 = &pwork->filebuf[sizeof (pwork->filebuf) / sizeof(*pwork->filebuf)];
	works.iobuf0 = pwork->iobuf;
	works.iobuf1 = &pwork->iobuf[sizeof (pwork->iobuf) / sizeof(*pwork->iobuf)];
	works.libname = works.extname = NULL;
	works.flags = 0;

	p0 = GetCommandLineA();
	while (*p0 > ' ')
		p0++;
	cmdline(p0, p0 + GO_strlen(p0), &works);
	libout(&works);

	GOLD_exit(0);
}