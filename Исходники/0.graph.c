prgraph()
	{
	VERT v;
	int i;
	if (progress) fprintf(stderr,"prgraph():\n");
	for (v = 0; v < nodenum; ++v)
		{
		fprintf(stderr,"%d %s:",v, typename[NTYPE(v)]);
		for (i = 0; i < ARCNUM(v); ++i)
			{
			printf("%d ",ARC(v,i));
			ASSERT(UNDEFINED <= ARC(v,i) && ARC(v,i) < nodenum, prgraph);
			}
		printf("\n");
		}
	printf("\n\n");
	}