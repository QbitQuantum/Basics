int BTGE_Voxel_LoadDungeonInfo(
	BTGE_VoxelDungeonInfo *inf, char *name)
{
	VFILE *fd;
	void *p;
	char buf[256];
	char **a, *s;
	int i, j, k;

//	strcpy(buf, tmp->name);
	strcpy(buf, name);
	s=buf+strlen(buf);
	while((s>buf) && (*s!='.'))s--;
	if(*s!='.')s=buf+strlen(buf);
	strcpy(s, ".txt");

	fd=vffopen(buf, "rt");
	if(!fd)return(-1);

	while(!vfeof(fd))
	{
		vfgets(buf, 255, fd);
		a=gcrsplit(buf);
		if(!a[0])continue;

		if(!strcmp(a[0], "$flags"))
		{
		}

		if(!strcmp(a[0], "$dung_vox"))
		{
			j=BTGE_Voxel_IndexVoxelName(a[1]);
			if(j<0)
			{
				printf("BTGE_Voxel_LoadDungeonInfo: "
					"%s Bad Voxel Type %s\n", name, a[1]);
				continue;
			}

			i=inf->n_idx++;
			inf->idx_vox[i].type=j;

			inf->idx_rgba[i*4+0]=atoi(a[2]);
			inf->idx_rgba[i*4+1]=atoi(a[3]);
			inf->idx_rgba[i*4+2]=atoi(a[4]);
			inf->idx_rgba[i*4+3]=255;
			
			for(j=5; a[j]; j++)
			{
				if(!strcmp(a[j], "unbreakable"))
					{ inf->idx_vox[i].type|=VOX_TYM_UNBREAKABLE; }
				if(!strcmp(a[j], "flexform"))
					{ inf->idx_vox[i].type|=VOX_TYM_FLEXFORM; }
				if(!strncmp(a[j], "aux=", 4))
					{ inf->idx_vox[i].aux=atoi(a[j]+4); }
				if(!strncmp(a[j], "aux2=", 5))
					{ inf->idx_vox[i].aux2=atoi(a[j]+5); }
				if(!strncmp(a[j], "vlight=", 7))
					{ inf->idx_vox[i].vlight=atoi(a[j]+7); }
				if(!strncmp(a[j], "slight=", 7))
					{ inf->idx_vox[i].slight=atoi(a[j]+7); }
				if(!strncmp(a[j], "delay=", 6))
					{ inf->idx_vox[i].delay=atoi(a[j]+6); }
			}
		}
		
		if(!strcmp(a[0], "$dung_allow_nx"))
		{
			i=inf->allow_n_edge[0]++;
			inf->allow_edge[0][i]=BTGE_Voxel_IndexDungeonName(a[1]);
		}
		if(!strcmp(a[0], "$dung_allow_px"))
		{
			i=inf->allow_n_edge[1]++;
			inf->allow_edge[1][i]=BTGE_Voxel_IndexDungeonName(a[1]);
		}
		if(!strcmp(a[0], "$dung_allow_ny"))
		{
			i=inf->allow_n_edge[2]++;
			inf->allow_edge[2][i]=BTGE_Voxel_IndexDungeonName(a[1]);
		}
		if(!strcmp(a[0], "$dung_allow_py"))
		{
			i=inf->allow_n_edge[3]++;
			inf->allow_edge[3][i]=BTGE_Voxel_IndexDungeonName(a[1]);
		}
		if(!strcmp(a[0], "$dung_allow_nz"))
		{
			i=inf->allow_n_edge[4]++;
			inf->allow_edge[4][i]=BTGE_Voxel_IndexDungeonName(a[1]);
		}
		if(!strcmp(a[0], "$dung_allow_pz"))
		{
			i=inf->allow_n_edge[5]++;
			inf->allow_edge[5][i]=BTGE_Voxel_IndexDungeonName(a[1]);
		}

		if(!strcmp(a[0], "$dung_allow_biome"))
		{
			i=inf->allow_n_biome++;
			inf->allow_biome[i]=BTGE_Voxel_IndexBiomeName(a[1]);
		}

		if(!strcmp(a[0], "$dung_deny_biome"))
		{
			i=inf->deny_n_biome++;
			inf->deny_biome[i]=BTGE_Voxel_IndexBiomeName(a[1]);
		}

		if(!strcmp(a[0], "$dung_min_z"))
		{
			inf->min_z=atoi(a[1]);
		}

		if(!strcmp(a[0], "$dung_max_z"))
		{
			inf->max_z=atoi(a[1]);
		}
	}

	vfclose(fd);
	return(0);
}