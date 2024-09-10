static PRESULT lan_con_callback(POBJECT_HEAD pObj, VEVENT event, UINT32 param1, UINT32 param2)
{
	PRESULT ret = PROC_PASS;
	UINT32 i;
	UINT8	unact;
	BOOL subt_popup;
	CONTAINER* cont = (CONTAINER*)pObj;
	UINT8	id = OSD_GetObjID(pObj);
	SYSTEM_DATA* p_sys_data;
	UINT8 lang_code[8];
    
	switch(event)
	{
	case EVN_PRE_OPEN:
#ifdef EXIT_KEY_EXIT_ALL_MENU
	         exit_key_flag =  FALSE;
#endif
		wincom_open_subtitle((POBJECT_HEAD)&win_lan_con,RS_SYSTEM_LANGUAGE, 0);
#ifdef SHOW_WELCOME_SCREEN
		if(show_win_as_welcome)
		//if(1)
		{
			OSD_SetAttr(&lan_item_con6, C_ATTR_ACTIVE);
			((POBJECT_HEAD)(&lan_item_con1))->bUpID = 6;
			((POBJECT_HEAD)(&lan_item_con5))->bDownID = 6;
            //win_lan_con.head.style.bShowIdx = WSTL_WIN_BODYLEFT_01_HD;
            //win_lan_con.head.style.bHLIdx = WSTL_WIN_BODYLEFT_01_HD;
           // win_lan_con.head.style.bSelIdx = WSTL_WIN_BODYLEFT_01_HD;
           // win_lan_con.head.style.bGrayIdx = WSTL_WIN_BODYLEFT_01_HD;
            OSD_SetRect(&(win_lan_con.head.frame), MAIN_W_L, W_T, MAIN_W_W, W_H);
		}
		else
		{
			OSD_SetAttr(&lan_item_con6, C_ATTR_HIDDEN);
			((POBJECT_HEAD)(&lan_item_con1))->bUpID = 5;
			((POBJECT_HEAD)(&lan_item_con5))->bDownID = 1;
            win_lan_con.head.style.bShowIdx = WIN_SH_IDX;
            win_lan_con.head.style.bHLIdx = WIN_HL_IDX;
            win_lan_con.head.style.bSelIdx = WIN_SL_IDX;
            win_lan_con.head.style.bGrayIdx = WIN_GRY_IDX;

            OSD_SetRect(&(win_lan_con.head.frame), W_L, W_T, W_W, W_H);
    		//remove_menu_item(&win_lan_con, (OBJECT_HEAD *)&lan_item_con6, CON_H + CON_GAP);
			
		}
         ((CONTAINER*)(&win_lan_con))->FocusObjectID = 1;
#endif

		p_sys_data=sys_data_get();
//libc_printf("\nmmmmm-lan_open--mmmmmmm==%d\n",p_sys_data->lang.OSD_lang);
		win_lan_set_menu_lan_string(p_sys_data->lang.OSD_lang);
		win_lan_set_1st_audio_lan_string(p_sys_data->lang.Audio_lang_1);
		win_lan_set_2nd_audio_lan_string(p_sys_data->lang.Audio_lang_2);
		win_lan_set_subtitle_lan_string(p_sys_data->lang.sub_lang);
		win_lan_set_teletext_lan_string(p_sys_data->lang.ttx_lang);
#ifdef ORDER_GZ1207009
		win_lan_set_epg_lan_string(p_sys_data->lang.epg_lang);
#endif

#ifdef SUPPORT_POP_SUBT
		subt_popup = TRUE;
#else
		subt_popup = FALSE;
#endif

#ifdef PREVIEW_SUBMENU  //-a by wangyang 
{
				
			POBJECT_HEAD focusObj=OSD_GetFocusObject(pObj);
			
			if(param2==MENU_OPEN_TYPE_OTHER)
			{
				lan_item_set[focusObj->bID-1]->style.bHLIdx=TXTS_SH_IDX;
				lan_item_name[focusObj->bID-1]->style.bHLIdx=TXTN_SH_IDX;
			}
			else
			{
				lan_item_set[focusObj->bID-1]->style.bHLIdx=TXTS_HL_IDX;
				lan_item_name[focusObj->bID-1]->style.bHLIdx=TXTN_HL_IDX;
			}

}
#endif

	/*	if(subt_popup) //-d by wangyang  for add subtitle language
		{
			remove_menu_item(&win_lan_con, (POBJECT_HEAD)lan_items[3], (CON_H + CON_GAP));			
		}*/
		break;
	
	case EVN_POST_OPEN:
		wincom_open_commen_help(pObj);//-a by wangyang 
		break;
		
	case EVN_PRE_CLOSE:
#ifdef EPG_MULTI_LANG
#ifndef ORDER_GZ1207009
		/*set epg language*/
		p_sys_data = sys_data_get();
		STRCPY(lang_code,stream_iso_639lang_abbr[p_sys_data->lang.OSD_lang]);
		epg_set_lang_code(lang_code);
#endif
#endif

#ifndef NEW_DEMO_FRAME
		UIChChgApplyAudLanguage();
#endif
//libc_printf("\nmmmmm---mmmmmmm==%d\n",p_sys_data->lang.OSD_lang);
		sys_data_save(1);
		/* Make OSD not flickering */
		*((UINT32*)param2) &= ~C_CLOSE_CLRBACK_FLG;	
		
		break;

	case EVN_POST_CLOSE:
              TTXEng_set_g0_set();
  		wincom_close_subtitle();
			OSD_ClearScreen();
#ifdef EXIT_KEY_EXIT_ALL_MENU
	        if( exit_key_flag == TRUE)
	        	{
 			 exit_key_flag =FALSE;
			mm_leave_all_menu();
		}
#endif
		//OSD_TrackObject( (POBJECT_HEAD) &g_win_mainmenu, C_UPDATE_ALL);
		break;
	}
	return ret;
}