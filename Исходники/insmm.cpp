// =====================================================================
	void handle_mm_stuff(char *mailbuf,int fromwhere)
// =====================================================================
{
static int preflen=strlen(MM_PREFIX);
char	*p,*t;
char	name[300];
char	mmcod[MAX_PATH],mmbase[MAX_PATH];

	if (GetKeyState(VK_CONTROL) & 0x80000000)
		return;

// WAVES
// Format: 	MM_PREFIX|mmtype|whentoplay|name
	p=mailbuf;
handle_wav:
	if ((gc.sound_enabled && !gc.sound_already_done) || fromwhere==3)
	{
find_ag1:
		p=strstr(p,MM_PREFIX);
		if (p)
		{
			p+=preflen;
			switch (*p)
			{
				case 'W':
				case 'w':
					break;
				case 'B':
				case 'b':
					if ((gc.bmps_enabled && !gc.bmps_already_done) || fromwhere==3)
					{
						p-=preflen;
						goto handle_bmp;
					}
					goto find_ag1;
				case '\0':
					return;
				default:
					goto find_ag1;
			}

			p++;
			if (fromwhere!=3)
			{
				switch (*p)	// 1-Play on display , 2-Play on income
				{
					case '1':
						if (fromwhere!=1)
							goto handle_bmp;
						break;
					case '2':
						if (fromwhere!=2)
							goto handle_bmp;
						break;
					default:
						goto handle_bmp;
				}
			}
			p++;
			name[0]=0;
			sscanf(p,"%s",name);
			if (!name[0] || strlen(name)>8)
				goto handle_bmp;

			t=name;
			while (*t)
			{
				if (!isxdigit(*t))
					goto handle_bmp;
				t++;
			}
			strcpy(mmcod,"00000000");
			memcpy(mmcod+(8-strlen(name)),name,strlen(name));
//			strcpy(mmcod,name);
			strcat(mmcod,".WAV");
			make_path(mmbase,gc.MultimedPath,mmcod);
			if (access(mmbase,0))
			{
				if (gc.no_error)
					err_out("W_CNFMMXF",mmbase);
				goto handle_bmp;
			}
			gc.sound_already_done=1;
			test_sound(mmbase);
		}
		else
			return;
	}

// BITMAPS
// Format: 	MM_PREFIX|mmtype|whentoplay|name with ending NULL
handle_bmp:
	if ((gc.bmps_enabled && !gc.bmps_already_done) || fromwhere==3)
	{
find_ag2:
		p=strstr(p,MM_PREFIX);
		if (p)
		{
			p+=preflen;
			switch (*p)
			{
				case 'W':
				case 'w':
					if ((gc.sound_enabled && !gc.sound_already_done) || fromwhere==3)
					{
						p-=preflen;
						goto handle_wav;
					}
					goto find_ag2;
				case 'B':
				case 'b':
					break;
				case '\0':
					return;
				default:
					goto find_ag2;
			}
			p++;
			if (fromwhere!=3)
			{
				switch (*p)	// 1=Play on display , 2=Play on income
				{
					case '1':
						if (fromwhere!=1)
							goto handle_wav;
						break;
					case '2':
						if (fromwhere!=2)
							goto handle_wav;
						break;
					default:
						goto handle_wav;
				}
			}
			p++;
			name[0]=0;
			sscanf(p,"%s",name);
			if (!name[0] || strlen(name)>8)
				goto handle_wav;

			t=name;
			while (*t)
			{
				if (!isxdigit(*t))
					goto handle_wav;
				t++;
			}
			strcpy(mmcod,"00000000");
			memcpy(mmcod+(8-strlen(name)),name,strlen(name));
			strcpy(mmcod,name);
			strcat(mmcod,".BMP");
			make_path(mmbase,gc.MultimedPath,mmcod);
			if (access(mmbase,0))
			{
				if (gc.no_error)
					err_out("W_CNFMMXF",mmbase);
				goto handle_wav;
			}
			gc.bmps_already_done=1;
			display_bitmap(mmbase);
		}
		else
			return;
		
		goto handle_wav;
	}
}