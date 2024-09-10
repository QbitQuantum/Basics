void load_app_icon(void)
	{
	unsigned long tmp;
	int i, fh, n, len;
	char inf[256]={0};
	char *mono_mask, *mono_data, *col_mask, *col_data;
	CICONBLK *icon=NULL;

	if(	app_icon_mode==1)
		return;
	app_icon_mode = 1;

	strcpy(inf,home);
	strcat(inf,"defaults\\MyTask.ico");
	fh=(int)Fopen(inf,FO_READ);

	if (fh<0L)
		{
		strcpy(inf,home);
		strcat(inf,"MyTask.ico");
		fh=(int)Fopen(inf,FO_READ);
		}

	if (fh>=0L)
		{
		read(fh, &tmp, 4);		n = (int)tmp;
		icons_spec_app = calloc(1,n*sizeof(struct _icons_spec_app));
		memset(icons_spec_app, 0, n*sizeof(struct _icons_spec_app));
		for(i=0; i<n; i++)
			{
			read(fh, &icons_spec_app[i].obj_no, 4);
			read(fh, &tmp, 4);			len = (int)tmp;
			icons_spec_app[i].name = calloc(1,len+1L);
			memset(icons_spec_app[i].name, 0, len+1);
			read(fh, icons_spec_app[i].name, len);
			icons_app.how_many++;

			if(mini_icons!=NULL)
				{
				if(icons_spec_app[i].obj_no<=0)
					{
/*
					OBJECT *tmp=NULL;
					int j=(int)strlen(icons_spec_app[i].name);
					for(; j>0, icons_spec_app[i].name[j]!='\\'; j--)
						;
					if(stic)
						{
						tmp = stic->str_icon(&icons_spec_app[i].name[++j], 2);
						if(tmp)
							icon = (CICONBLK*)(tmp->ob_spec.ciconblk);
						}
					else	*/
						icon = (CICONBLK*)(mini_icons[abs(icons_spec_app[i].obj_no+1)].ob_spec.ciconblk);
					}
				else
					icon = (CICONBLK*)(mini_icons[icons_spec_app[i].obj_no].ob_spec.ciconblk);
				}
			if(stic)				/* Ikonka wzieta ze StIc					*/
				{
				OBJECT *tmp=NULL;
				int j=(int)strlen(icons_spec_app[i].name);
				for(; j>0, icons_spec_app[i].name[j]!='\\'; j--)
					;
				tmp = stic->str_icon(&icons_spec_app[i].name[++j], 2);
				if(tmp)
					icon = (CICONBLK*)(tmp->ob_spec.ciconblk);
				}
			if(icon)				/* Czy mamy jakas ikonke wogole?	*/
				{
				mono_data = (char*)icon->monoblk.ib_pdata;
				mono_mask = (char*)icon->monoblk.ib_pmask;
				col_data = (char*)icon->mainlist->col_data;
				col_mask = (char*)icon->mainlist->col_mask;
				}
			if(icon)
				add_icon((void *)icons_spec_app, APP_TRAY, icons_app.how_many, mono_data, mono_mask, col_data, col_mask);
			}
		if(icon)
			{
			bigbutton->ob_next = -1;
			fix_width();
			move_applications(1);
			icons_spec_app->no = n;
			}
		close(fh);
		}
	}