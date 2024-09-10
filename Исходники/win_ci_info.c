static void ci_info_init()
{
	char * tmp;
	UINT8 *tmp_buf;
	
	// init
	MEMSET(&ci_info, 0, sizeof(ci_info));
	// get menu string
	tmp_buf = (void*)(win_ci_get_tmp_buf());
	
	tmp = api_ci_get_menu_string(tmp_buf, CI_DATA_BUFFER_LEN, ci_slot);

	if(tmp != NULL)
	{
		ci_info_set_string(ci_info.name, CI_MENU_TXT_LENGTH, tmp);
	}
	else
	{
		ci_info.name[0] = '\0';
	}


	//set the window style as the difference show modal
	win_ci_info_set_colorstyle();
	if(win_ci_info_modal == WIN_CI_INFO_SHOW_AS_MODAL)
	{
        OSD_SetColor((POBJECT_HEAD)&g_win_ci_info,WIN_SH_IDX_SD,WIN_HL_IDX_SD,WIN_SL_IDX_SD,WIN_GRY_IDX_SD);
        OSD_MoveObject((POBJECT_HEAD)&g_win_ci_info, W_L_SD,W_T_SD, 0);//62, 55, 0);
		OSD_MoveObject((POBJECT_HEAD)&txt_ci_info_split1, W_L_SD + 10, SPLIT_1_T_SD, 0); //62, SPLIT_1_T, 0);
		OSD_MoveObject((POBJECT_HEAD)&txt_ci_info_split2, W_L_SD + 10, SPLIT_2_T_SD, 0);//62, SPLIT_2_T - 1, 0);
	}
	else
	{
		OSD_SetColor((POBJECT_HEAD)&g_win_ci_info, WIN_SUBMENU_BODY_FRAME, WIN_SUBMENU_BODY_FRAME, WIN_SUBMENU_BODY_FRAME, WIN_SUBMENU_BODY_FRAME);//guop
		OSD_MoveObject((POBJECT_HEAD)&g_win_ci_info, W_L,W_T, 0);
		OSD_MoveObject((POBJECT_HEAD)&txt_ci_info_split1, SPLIT_1_L, SPLIT_1_T, 0);
		OSD_MoveObject((POBJECT_HEAD)&txt_ci_info_split2, SPLIT_1_L, SPLIT_2_T, 0);
	}
	

	/////////////////////////////////////////////////////////////////////////	
	//clear the menu
	//1. CI Title
	OSD_SetTextFieldContent(&txt_ci_info_title, STRING_UNICODE, (UINT32)"");
	//2. sub title
	ci_info_subtitle_content[0].text.pString = NULL;
	
	//3. bottom 
	OSD_SetTextFieldContent(&txt_ci_info_bottom, STRING_UNICODE, (UINT32)"");
	//4. list
	OSD_SetObjListCount(&olst_ci_info, 0);
	
	OSD_SetAttr(&sb_ci_info, C_ATTR_HIDDEN);

	//show the ci enquiry dialog
	OSD_SetObjpNext(&txt_ci_info_bottom, NULL);
	//the the windows focus to the dialog
	g_win_ci_info.FocusObjectID = 1;


}