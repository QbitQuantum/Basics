static void win_mpegYT_player_draw_infor(void)
{
	BITMAP* bmp;
	TEXT_FIELD* txt;
	PROGRESS_BAR* bar;
	mpegYTplayer_bmp_t* bmp_desc;
	mpegYTplayer_txt_t* txt_desc;
	UINT32 i, hd_fulless;
	UINT16 icon;
	char string[30];
	UINT32 hh, mm, ss;
	UINT32 play_pos = 0;
	FileInfo file_node;
	char name_buffer[MAX_FILE_NAME_SIZE + 1];

	bmp = &mpegYT_player_bmp;
	txt = &mpegYT_player_text;
	bar = &mpegYT_player_bar;

	for (i = 0; i < MPEGYT_BMP_NUM; i++)
	{
		bmp_desc = &mpegYTplayer_bmps[i];
		icon = INVALID_ID;
		switch (bmp_desc->bmp_type)
		{
		case MPEGYT_BMP_STATIC:
			//icon = bmp_desc->icon;
			break;
		case MPEGYT_BMP_PLAY_RECORD:
			icon = bmp_desc->icon;
			break;
		case MPEGYT_BMP_PLAY_MODE:
			if (MPEGYTInfo.PlayState < sizeof(mpegplayer_yt_status_icons) / 2)
			{
				icon = mpegplayer_yt_status_icons[MPEGYTInfo.PlayState];
			}
			break;
		case MPEGYT_BMP_HDD_STATUS:
			/*			step_sectors =  (hdd_info.total_size - hdd_info.tms_size) / 5;
						if(step_sectors >0 )
						{
							hd_fulless = (hdd_info.rec_size + step_sectors/2) / step_sectors ;
							if(hd_fulless == 5)
								hd_fulless = 4;
							icon = MP_HDstatus_icons[4-hd_fulless];//hd_fulless -> 4-hd_fulles, show used space!
						}
			*/
			break;
		default:
			break;
		}


		OSD_SetBitmapContent(bmp, icon);
		OSD_SetRect(&bmp->head.frame, bmp_desc->left, bmp_desc->top, bmp_desc->width, bmp_desc->height);
		OSD_DrawObject( (OBJECT_HEAD*) bmp, C_UPDATE_ALL);
	}

	for (i = 0;i < MPEGYT_TXT_NUM;i++)
	{
		txt_desc = &mpegYTplayer_txts[i];

		OSD_SetTextFieldContent(txt, STRING_ANSI, (UINT32)"");

		switch (txt_desc->txt_type)
		{
		case MPEGYT_TXT_PLAY_NAME:
			//get_file_from_file_list(win_file_list[VIDEO_FILE_LIST], mpegYTlist_idx, &file_node);
			//filter_unkownfont_name(file_node.name, name_buffer);
			win_shorten_filename(entry_youtube->title,name_buffer);
			sprintf(name_buffer, "%s", name_buffer);
			OSD_SetTextFieldContent(txt, STRING_UTF8, (UINT32)name_buffer);
			break;
		case MPEGYT_TXT_DATE:
			//sprintf(string,"%02d/%02d",dt.month,dt.day);
			//STRCPY(string, "");
			sprintf(string, "%02d/%02d/%02d",
					entry_youtube->pub_date.year,
					entry_youtube->pub_date.month,
					entry_youtube->pub_date.day);
			OSD_SetTextFieldContent(txt, STRING_ANSI, (UINT32)string);
			break;
		case MPEGYT_TXT_TIME:
			//sprintf(string,"%02d:%02d",dt.hour,dt.min);
			STRCPY(string, "");
			OSD_SetTextFieldContent(txt, STRING_ANSI, (UINT32)string);
			break;
		case MPEGYT_TXT_PLAY_MODE:
			STRCPY(string, "");
			if (MPEGYTInfo.PlayState == MPEG_STOP)
			{
				sprintf(string, "%s", "Stop");
			}
			else if (MPEGYTInfo.PlayState == MPEG_PLAY)
			{
				sprintf(string, "%s", "Play");
			}
			else if (MPEGYTInfo.PlayState == MPEG_PAUSE)
			{
				sprintf(string, "%s", "Pause");
			}
			else if (MPEGYTInfo.PlayState == MPEG_FF || MPEGYTInfo.PlayState == MPEG_FB)
			{
				sprintf(string, "X%d", mpegYTspeed_steps[MPEGYTInfo.PlaySpeed]);
			}
			else if (MPEGYTInfo.PlayState == MPEG_SF || MPEGYTInfo.PlayState == MPEG_SB)
			{
				sprintf(string, "X1/%d", mpegYTspeed_steps[MPEGYTInfo.PlaySpeed]);
			}
			else if(MPEGYTInfo.PlayState == MPEG_STEP)
			{
				sprintf(string,"%s","Step");
			}
#ifdef SUPPORT_DIVX_CERT
            else if(MPEGYTInfo.PlayState == MPEG_RESUME_STOP)
            {
                sprintf(string,"%s","Stop");
            }
#endif
			OSD_SetTextFieldContent(txt, STRING_ANSI, (UINT32)string);
			break;
		case MPEGYT_TXT_PLAY_1ST_TIME:
			STRCPY(string, "");
			MPEGYTInfo.PlayTime = (UINT32)MPGFileDecoderGetPlayTime() + s_ytvideo_seektime;
            if (MPEGYTInfo.PlayState == MPEG_STOP)
                MPEGYTInfo.PlayTime = 0;
#if 1
			hh = MPEGYTInfo.PlayTime / 3600;
			mm = (MPEGYTInfo.PlayTime % 3600) / 60;
			ss = MPEGYTInfo.PlayTime % 60;
#else
			hh = entry_youtube->info->duration/3600;
			mm = (entry_youtube->info->duration % 3600) / 60;
			ss = entry_youtube->info->duration % 60;			
#endif
			sprintf(string, "%02d:%02d:%02d", hh, mm, ss);
			OSD_SetTextFieldContent(txt, STRING_ANSI, (UINT32)string);
			break;

		case MPEGYT_TXT_PLAY_2ND_TIME:
			STRCPY(string, "");
#if 0
			hh = MPEGYTInfo.TotalTime / 3600;
			mm = (MPEGYTInfo.TotalTime % 3600) / 60;
			ss = MPEGYTInfo.TotalTime % 60;
#else
			hh = entry_youtube->info->duration/3600;
			mm = (entry_youtube->info->duration % 3600) / 60;
			ss = entry_youtube->info->duration % 60;	
#endif
			sprintf(string, "%02d:%02d:%02d", hh, mm, ss);
			OSD_SetTextFieldContent(txt, STRING_ANSI, (UINT32)string);
			break;
		case MPEGYT_TXT_HDD_STATUS:
			/*step_sectors = (hdd_info.total_size - hdd_info.tms_size)/100;
			if(step_sectors >0 )
			{
				sprintf(string,"%d%%",(100 - (hdd_info.rec_size+ step_sectors/2 )/step_sectors));
			}
			else
			{
				STRCPY(string,"");
			}
			OSD_SetTextFieldContent(txt, STRING_ANSI, (UINT32)string);
			*/
			break;
		}

		OSD_SetRect(&txt->head.frame, txt_desc->left, txt_desc->top, txt_desc->width, txt_desc->height);
		txt->head.style.bShowIdx = txt_desc->shidx;
		OSD_DrawObject( (OBJECT_HEAD *)txt, C_UPDATE_ALL);
	}

	/* Draw progress bar */
	OSD_SetProgressBarPos(bar, 100);
	OSD_SetRect(&bar->head.frame, BAR_L, BAR_T, BAR_W, 24);
	bar->rcBar.uLeft 	= 2;
	bar->rcBar.uTop 		= 5;
	bar->rcBar.uWidth	= BAR_W - 4;
	bar->rcBar.uHeight 	= 14;//16 - 6;
	bar->wTickFg 		= WSTL_BAR_06;
	OSD_DrawObject((POBJECT_HEAD)bar, C_UPDATE_ALL);

	/* Draw play pos */
//    BarState.nPos = MPEGYTInfo.PlayTime;
	if (BarState.nRange)
	{
		play_pos = BarState.nPos * 100 / BarState.nRange;
	}
	OSD_SetRect(&bmp->head.frame, bar->head.frame.uLeft+6 + (bar->head.frame.uWidth-12)*play_pos / 100*OSD_GetProgressBarPos(bar) / 100 - POS_ICON_WIDTH / 2,
				bar->head.frame.uTop, POS_ICON_WIDTH, bar->head.frame.uHeight);
	OSD_SetBitmapContent(bmp, IM_PVR_DOT);
	OSD_DrawObject((POBJECT_HEAD)bmp, C_UPDATE_ALL);

	/* Draw play cursor */
	if (CURSOR_MOVING == BarState.State)
	{
		if (BarState.nRange)
		{
			play_pos = BarState.nCursor * 100 / BarState.nRange;
		}
		OSD_SetRect(&bmp->head.frame, bar->head.frame.uLeft + 6 + (bar->head.frame.uWidth-4)*play_pos / 100/**OSD_GetProgressBarPos(bar) / 100*/ - POS_ICON_WIDTH / 2,
		//OSD_SetRect(&bmp->head.frame, bar->head.frame.uLeft + 6 + (bar->head.frame.uWidth-4)*play_pos / 100*OSD_GetProgressBarPos(bar) / 100 - POS_ICON_WIDTH / 2,
					bar->head.frame.uTop, POS_ICON_WIDTH, bar->head.frame.uHeight);
		OSD_SetBitmapContent(bmp, IM_PVR_DOT_ORANGE);
		OSD_DrawObject((POBJECT_HEAD)bmp, C_UPDATE_ALL);
	}
}