int main(int argc, char *argv[])
{
	yyin = stdin;

	int i = getoptions(argc, argv);

	char buf[PATH_MAX];
	if (out[0] == '/')
		strcpy(buf, out);
	else
	{
		getcwd(buf, PATH_MAX);
		strcat(buf, "/");
		strcat(buf, out);
	}

	BEntry e;
	if (e.SetTo(out)) error("entry set to %s", out);

	BDirectory d;
	if (e.GetParent(&d)) error("get parent of %s", out);
	if ((gTruncate || gSaveAsHeader) && e.Exists() && e.Remove())
		error("removing %s", out);

	BFile f;
	BResources res;

	if (!gDump)
	{
		if (gTruncate || !e.Exists())
		{
			if (d.CreateFile(buf, &f)) error("creating %s", buf);
			gTruncate = true;
		}
		else
			if (f.SetTo(buf, B_READ_WRITE)) error("opening %s", buf);

		if (gSaveAsHeader)
		{
			gHeader = fopen(buf, "w");
			if (!gHeader) error("Error creating %s", buf);
		}
		else if (res.SetTo(&f, gTruncate) != B_NO_ERROR)
			error("opening resource file %s", buf);
	}

	resFile = &res;

	if (i == argc)
		Work(NULL);
	else
	{
		while (i < argc)
			Work(in = argv[i++]);
	}

	if (verbose)
		puts("done");

	if (gHeader)
		fclose(gHeader);
	else
		f.Sync();

	return 0;
} /* main */