void win_progname_draw_infor(void)
{
	UINT16 group_name[MAX_SERVICE_NAME_LENGTH + 1 + 10];
	UINT8   group_type,av_mode;

	UINT16 cur_channel;
	P_NODE p_node;
	S_NODE s_node;
//	T_NODE t_node;
	char string[100];
	char prog_name[MAX_SERVICE_NAME_LENGTH + 1];
	INT32 ret,len;
	UINT32 i,j;
	BITMAP* bmp;
	TEXT_FIELD* txt;
	UINT16 icon;
	date_time dt;
	prog_txt_t* p_prog_txt;
	prog_bmp_t* p_prog_bmp;
	eit_event_info_t *pe=NULL,*fe=NULL;
	UINT8 *s1=NULL,*s2=NULL;
	INT32 strlen;
	struct ACTIVE_SERVICE_INFO service;

	struct t_ttx_lang *ttx_lang_list;
	UINT8 ttx_lang_num;
	struct t_subt_lang* sub_lang_list;
	UINT8 sub_lang_num;

	bmp = &prog_bmp;
	txt = &prog_text;
	UINT32 fav_mask;

	fav_mask = 0;
	for(i=0;i<MAX_FAVGROUP_NUM;i++)
		fav_mask |= (0x01<<i);


	av_mode = sys_data_get_cur_chan_mode();
	cur_channel = sys_data_get_cur_group_cur_mode_channel();
	ret = get_prog_at(cur_channel,&p_node);
	get_sat_by_id(p_node.sat_id, &s_node);
	get_cur_group_name((char*)group_name,&group_type);
	get_local_time(&dt);
/*
#ifdef _EPG_MULTI_SERVICE
#ifdef EPG_FAST_PARSE			
	epg_fast_pasrse_set(FALSE,NULL,NULL);
#endif
	get_tp_by_id(p_node.tp_id, &t_node);
	api_epg_parse(p_node.tp_id, t_node.network_id, t_node.t_s_id, p_node.prog_number, epg_type_pf);

	struct active_service_t service;
	service.tp_id = p_node.tp_id;
	service.orig_network_id = t_node.network_id;
	service.ts_id = t_node.t_s_id;
	service.service_id = p_node.prog_number;
	api_epg_set_active_service(&service, 1);

	api_epg_parse(p_node.tp_id, t_node.network_id, t_node.t_s_id, p_node.prog_number, epg_type_pf);
#endif
*/
	service.tp_id = p_node.tp_id;
	service.service_id = p_node.prog_number;
	epg_set_active_service(&service, 1);

	/*current next epg info */
	pe=epg_get_cur_service_event((INT32)cur_channel, PRESENT_EVENT, NULL,NULL,NULL, /*event_update*/TRUE);
	fe=epg_get_cur_service_event((INT32)cur_channel, FOLLOWING_EVENT, NULL,NULL,NULL, event_update);
    if(event_update==FALSE)
    {
        if(pe==NULL || fe==NULL)
        {
            event_update = TRUE;    
        }
    }
    else
    {
        if(pe!=NULL && fe!=NULL)
        {
            event_update = FALSE;
        }
    }
	s1=epg_get_event_name(pe, &len);
//	s1=(UINT8*)epg_get_event_name(pe, present_name, 32);
	s2=epg_get_event_name(fe, &len);
//	s2=(UINT8*)epg_get_event_name(fe, following_name, 32);

	TTXEng_GetInitLang(&ttx_lang_list, &ttx_lang_num);
	subt_get_language(&sub_lang_list ,&sub_lang_num);
	if(sub_lang_num == 0)
		TTXEng_GetSubtLang(&ttx_lang_list,&sub_lang_num);

		
	for(i=0;i<PROG_BMP_NUM;i++)
	{
	    p_prog_bmp = &prog_bmps[i];
	    icon = INVALID_ID;
	    switch(p_prog_bmp->bmp_type)
	    {
	     case PROG_BMP_STATIC:
	        icon = prog_bmps[i].icon;
	       break;
#ifndef MODIFY_FOR_EGYPT_CUSTOMER	   
	    case PROG_BMP_AV_TYPE:
	        if(av_mode==TV_CHAN)
	            icon = IM_INFO_BAR_TV;
	        else
	            icon = IM_INFO_BAR_RADIO;            
	        break;
#endif
	    case PROG_BMP_EPG:
	        if( (s1||s2) )
	            icon = prog_bmps[i].icon;
	        break;
	    case PROG_BMP_TTX:
			if(ttx_lang_num>0)
	            icon = prog_bmps[i].icon;
	        break;
	    case PROG_BMP_SUBT:
			if(sub_lang_num>0)
	            icon = prog_bmps[i].icon;
	        break;			
	    case PROG_BMP_LOCK:
	        if(p_node.lock_flag)
	            icon = prog_bmps[i].icon;
	        break;
	    case PROG_BMP_FAV:
			if(p_node.fav_group[0] & fav_mask)
				icon = prog_bmps[i].icon;
	       break;
	    case PROG_BMP_CA:
			{
#if 0				
				BOOL			b,bFlag;

				INT8 level,quality,lock;
				signal_lock_status lock_flag;
				signal_scramble_status scramble_flag;
				signal_lnbshort_status lnbshort_flag;
				signal_parentlock_status parrentlock_flag;

				bFlag = GetSignalStatus(&lock_flag, &scramble_flag,&lnbshort_flag,&parrentlock_flag);  
				if(bFlag && lock_flag== SIGNAL_STATUS_LOCK
					&& lnbshort_flag==SIGNAL_STATUS_LNBNORMAL 
					&& parrentlock_flag==SIGNAL_STATUS_PARENT_UNLOCK
					&& scramble_flag == SIGNAL_STATUS_SCRAMBLED)
					icon = prog_bmps[i].icon;
#else
				if(p_node.ca_mode)
					icon = prog_bmps[i].icon;
#endif				
					
        	}
			break;
        default:
            break;
        }
	OSD_SetBitmapContent(bmp, icon);
	OSD_SetRect(&bmp->head.frame, p_prog_bmp->left, p_prog_bmp->top, p_prog_bmp->width,p_prog_bmp->height);
	OSD_DrawObject( (OBJECT_HEAD*) bmp, C_UPDATE_ALL);
    }
    
    for(i=0;i<PROG_TXT_NUM;i++)
    {
        p_prog_txt = &prog_txts[i];
        
        string[0] = '\0';
        switch(p_prog_txt->txt_type)
        {
        case PROG_TXT_PROG_NAME: 
#ifndef DB_USE_UNICODE_STRING  
            STRCPY(prog_name,p_node.service_name);
            for(j=0;j<STRLEN(prog_name);j++)
                if(prog_name[j] >= 0x80)
                {
                    prog_name[j] = '\0';
                    break;
                }
            if(p_node.ca_mode==0)
                sprintf(string,"%s(%s)",prog_name,s_node.sat_name);
            else
                sprintf(string,"$%s(%s)",prog_name,s_node.sat_name);

#else
            if(p_node.ca_mode==0)
                STRCPY(string,"");
            else
                STRCPY(string,"$");
			
            ComAscStr2Uni(string,len_display_str);
            strlen = ComUniStrLen( len_display_str);
            //strcpy_uni(&len_display_str[strlen],p_node.service_name);
            ComUniStrCopyChar((UINT8 * )&len_display_str[strlen],p_node.service_name);
            strlen = ComUniStrLen( len_display_str);
            ComAscStr2Uni("(",&len_display_str[strlen]);
            strlen = ComUniStrLen( len_display_str);
            ComUniStrCopyChar((UINT8 * )&len_display_str[strlen],s_node.sat_name);
            strlen = ComUniStrLen( len_display_str);
            ComAscStr2Uni(")",&len_display_str[strlen]);
#endif            
            
            break;
        case PROG_TXT_DATE:
            sprintf(string,"%02d/%02d",dt.month,dt.day);
            ComAscStr2Uni(string, (UINT16 *)len_display_str);
            break;
        case PROG_TXT_TIME:
            sprintf(string,"%02d:%02d",dt.hour,dt.min);
            ComAscStr2Uni(string, (UINT16 *)len_display_str);
            break;
        case PROG_TXT_PROG_NUM:
            sprintf(string,"%04d",cur_channel + 1);
            ComAscStr2Uni(string, (UINT16 *)len_display_str);
            break;
        case PROG_TXT_EPG_NOW:
            if (s1 )				
			{
				sprintf(string,"Now: ");
				ComAscStr2Uni(string, (UINT16 *)len_display_str);
				len =ComUniStrLen(len_display_str);
				ComUniStrCopyChar((UINT8*)&len_display_str[len],s1);
			}
            else
			{
                        OSD_SetTextFieldStrPoint(txt,NULL);
                        OSD_SetTextFieldContent(txt,STRING_ID,RS_EPG_NO_INFORMATION);
			}
            break;
        case PROG_TXT_EPG_NEXT:
            if (s2)				
			{
				sprintf(string,"Next: ");
				ComAscStr2Uni(string, (UINT16 *)len_display_str);
				len =ComUniStrLen(len_display_str);
				ComUniStrCopyChar((UINT8*)&len_display_str[len],s2);		
			}
            else
			{
	            sprintf(string," ");
	            ComAscStr2Uni(string, (UINT16 *)len_display_str);
			}
    	     break;
        case PROG_TXT_PROG_GROUP:
#ifndef DB_USE_UNICODE_STRING  
            sprintf(string,"%s",group_name);
#else
            ComUniStrCopy(len_display_str, group_name);
#endif
            break;
        default:
            ;
        }  

#ifndef DB_USE_UNICODE_STRING
        ComAscStr2Uni(string, (UINT16 *)len_display_str);
#else

/*
        if(p_prog_txt->txt_type != PROG_TXT_PROG_NAME 
            && p_prog_txt->txt_type != PROG_TXT_PROG_GROUP
                        &&p_prog_txt->txt_type != PROG_TXT_EPG_NOW
            &&p_prog_txt->txt_type != PROG_TXT_EPG_NEXT)
            ComAscStr2Uni(string, (UINT16 *)len_display_str);
*/
	if(p_prog_txt->txt_type == PROG_TXT_PROG_NUM) 
		txt->head.bFont = 2;
	else
		txt->head.bFont = 0;
 
#endif

	OSD_SetRect(&txt->head.frame, p_prog_txt->left, p_prog_txt->top, p_prog_txt->width,p_prog_txt->height);
	//txt->pText = (UINT8*)len_display_str;
	txt->head.style.bShowIdx = p_prog_txt->shidx;
	OSD_DrawObject( (OBJECT_HEAD *)txt, C_UPDATE_ALL);
	OSD_SetTextFieldContent(txt,STRING_ID,0);
	OSD_SetTextFieldStrPoint(txt,len_display_str);
    }
#ifdef MODIFY_FOR_EGYPT_CUSTOMER
	progname_signal_refresh(TRUE);
#endif

}