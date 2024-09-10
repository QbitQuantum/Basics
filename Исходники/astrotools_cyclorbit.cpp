Tlunaorbit::Tlunaorbit()
{
	FILE *fp;
	int  i;
	char css[1000];

	QString filename=G_datadir();
	filename+=_qstr("\\AstroData\\moon.tab");

	if (_wfopen_s(&fp,filename,_qstr("r"))!=0) throw QError(_text("Unable to find moon.tab file"));
	fscanf(fp,"%s %d",css,&term1count);
	if (strcmp(css,"TAB1")!=0)
		{ _exit(0); }
	for (i=1; i<=term1count; i++)
	{
		fscanf(fp,"%d %d %d %d %d %d",
		&term1[i].i1,
		&term1[i].i2,
		&term1[i].i3,
		&term1[i].i4,
		&term1[i].j1,
		&term1[i].j2);
	}
	fscanf(fp,"%s %d",css,&term2count);
	if (strcmp(css,"TAB2")!=0)
		{ _exit(0); }
	for (i=1; i<=term2count; i++)
	{
		fscanf(fp,"%d %d %d %d %d",
		&term2[i].i1,
		&term2[i].i2,
		&term2[i].i3,
		&term2[i].i4,
		&term2[i].j1);
	}

	fclose(fp);
}