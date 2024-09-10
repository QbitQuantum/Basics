static int d2ladder_readladder(void)
{
	FILE				* fp;
	t_d2ladderfile_ladderindex	* ladderheader;
	t_d2ladderfile_ladderinfo	* ladderinfo;
	char				* ladderfile;
	t_d2ladderfile_header		header;
	unsigned int			i, n, temp, count, type, number;

	ladderfile=xmalloc(strlen(prefs_get_ladder_dir())+1+strlen(LADDER_FILE_PREFIX)+1+
			strlen(CLIENTTAG_DIABLO2DV)+1);
	sprintf(ladderfile,"%s/%s.%s",prefs_get_ladder_dir(),LADDER_FILE_PREFIX,CLIENTTAG_DIABLO2DV);
	if (!(fp=fopen(ladderfile,"rb"))) {
		eventlog(eventlog_level_error,__FUNCTION__,"error opening ladder file \"%s\" for reading (fopen: %s)",ladderfile,strerror(errno));
		xfree(ladderfile);
		return -1;
	}
	xfree(ladderfile);
	if (fread(&header,1,sizeof(header),fp)!=sizeof(header)) {
		eventlog(eventlog_level_error,__FUNCTION__,"error reading ladder file");
		fclose(fp);
		return -1;
	}
	max_ladder_type= bn_int_get(header.maxtype);
	if (d2ladderlist_create(max_ladder_type)<0) {
		eventlog(eventlog_level_error,__FUNCTION__,"error create ladder list");
		fclose(fp);
		return -1;
	}
	temp= max_ladder_type * sizeof(*ladderheader);
	ladderheader=xmalloc(temp);
	if (fread(ladderheader,1,temp,fp)!=temp) {
		eventlog(eventlog_level_error,__FUNCTION__,"error read ladder file");
		xfree(ladderheader);
		fclose(fp);
		return -1;
	}
	for (i=0, count=0; i< max_ladder_type ; i++) {
		type=bn_int_get(ladderheader[i].type);
		number=bn_int_get(ladderheader[i].number);
		if (d2ladder_create(type,number)<0) {
			eventlog(eventlog_level_error,__FUNCTION__,"error create ladder %d",type);
			continue;
		}
		fseek(fp,bn_int_get(ladderheader[i].offset),SEEK_SET);
		temp=number * sizeof(*ladderinfo);
		ladderinfo=xmalloc(temp);
		if (fread(ladderinfo,1,temp,fp)!=temp) {
			eventlog(eventlog_level_error,__FUNCTION__,"error read ladder file");
			xfree(ladderinfo);
			continue;
		}
		for (n=0; n< number; n++) {
			d2ladder_append_ladder(type,ladderinfo+n);
		}
		xfree(ladderinfo);
		if (number) count++;
	}
	xfree(ladderheader);
	fclose(fp);
	eventlog(eventlog_level_info,__FUNCTION__,"ladder file loaded successfully (%d types %d maxtype)",count,max_ladder_type);
	return 0;
}