static PRESULT win_tplist_list_unkown_act_proc(VACTION act)
{
	PRESULT ret = PROC_LOOP;
	UINT8	pre_sat_idx;
	UINT16 sel,sat_cnt;
	OSD_RECT rect;
	COM_POP_LIST_PARAM_T param;
	OBJLIST* ol;
	S_NODE s_node;
	T_NODE t_node;
	UINT32 freq,symb,pol;
	UINT8 back_saved;
	UINT32 ftaonly_VPid,srch_chan_APid,nit_PPid;
	UINT32 choice;
	POBJECT_HEAD sub_menu;
	INT32 iret;
	UINT16 pre_sat_id,cur_sat_id;

	sat_cnt = get_tuner_sat_cnt(TUNER_EITHER);
	
	get_tuner_sat(TUNER_EITHER, cur_tp_sat_idx, &s_node);
	ol = &tplst_olist;
	sel = OSD_GetObjListCurPoint(ol);

	pre_sat_idx = cur_tp_sat_idx;

	switch(act)
	{
	case VACT_SAT_PRE:
		if(cur_tp_sat_idx > 0)
			cur_tp_sat_idx --;
		else
			cur_tp_sat_idx = sat_cnt - 1;
		goto SAT_CHANGE;
		
	case VACT_SAT_NEXT:
		if(cur_tp_sat_idx < (sat_cnt - 1))
			cur_tp_sat_idx ++;
		else
			cur_tp_sat_idx = 0;					
		goto SAT_CHANGE;
		
	case VACT_SAT_SELECT:
		param.id = TUNER_EITHER;
		param.cur = cur_tp_sat_idx;
		param.selecttype = POP_LIST_SINGLESELECT;	
		OSD_SetRect(&rect, LST_SAT_L - 20 , LST_SAT_T, LST_SAT_W + 40, 360);
		rect.uTop += LST_SAT_H;
		sel = win_com_open_sub_list(POP_LIST_TYPE_SAT,&rect,&param);
		if(sel < sat_cnt)
			cur_tp_sat_idx = sel;			
		goto SAT_CHANGE;
SAT_CHANGE:
        tp_list_pos = 0;
        tp_list_top = 0;
		if(cur_tp_sat_idx != pre_sat_idx)
		{
			pre_tp_sat_idx = pre_sat_idx;
			get_tuner_sat(TUNER_EITHER, pre_sat_idx, &s_node);			
			pre_sat_id = s_node.sat_id;

			get_tuner_sat(TUNER_EITHER, cur_tp_sat_idx, &s_node);			
			cur_sat_id = s_node.sat_id;

			#ifdef SUPPORT_TWO_TUNER
			#ifdef SUPPORT_SELECT_SAME_SAT
				cur_tuner_idx = s_node.reserve_1; //s_node.tuner1_valid? 0 : 1;
			#else
				cur_tuner_idx = s_node.tuner1_valid? 0 : 1;			
			#endif
			#endif
			
			if(win_tplist_check_change())
				update_data();
			win_tplist_load_sat(TRUE);
			//OSD_TrackObject( (POBJECT_HEAD)&tplst_olist, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
			OSD_TrackObject( (POBJECT_HEAD)&g_win_tplist, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
			api_stop_timer(&tpturn_timer_id);			
			tpturn_timer_id = api_start_timer(TPTURN_TIMER_NAME, TPTURN_TIMER_TIME, win_tplist_tpturn_handler);		
		}
		break;
	case VACT_TP_EDIT:
		/* If not TP, can't EDIT */
		if(OSD_GetObjListCount(ol) == 0)
			break;
		
		get_tp_at(s_node.sat_id,sel, &t_node);		
		choice = win_tpe_open(0, s_node.sat_id, t_node.tp_id);
		if( choice)
 		{
			win_tpe_get_setting(&freq, &symb, &pol);
			if(freq != t_node.frq || symb != t_node.sym || pol != t_node.pol)
			{
				t_node.frq = freq;
				t_node.sym = symb;
				t_node.pol = pol;				
				modify_tp(t_node.tp_id,&t_node);
				api_stop_timer(&tpturn_timer_id);
				tpturn_timer_id = api_start_timer(TPTURN_TIMER_NAME, TPTURN_TIMER_TIME, win_tplist_tpturn_handler);
				
			}
		}
		
		//OSD_TrackObject( (POBJECT_HEAD)ol, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
		OSD_TrackObject( (POBJECT_HEAD)&g_win_tplist, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
		
		break;
	case VACT_TP_ADD:
		if(OSD_GetObjListCount(ol) == MAX_TP_NUM)
			break;
		extern UINT32 edit_tp_exist;
	    edit_tp_exist = 0;
		
		choice = win_tpe_open(1, s_node.sat_id, 0);
		if(choice)
		{
			win_tpe_get_setting(&freq, &symb, &pol);
			MEMSET(&t_node,0,sizeof(t_node) );
			t_node.frq = freq;
			t_node.sym = symb;
			t_node.pol = pol;	
			t_node.sat_id = s_node.sat_id;
			iret = add_node(TYPE_TP_NODE,s_node.sat_id,(void*)&t_node);
			if((iret == DBERR_MAX_LIMIT) || (iret == DBERR_FLASH_FULL))
			{
				OSD_TrackObject( (POBJECT_HEAD)ol, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
				win_compopup_init(WIN_POPUP_TYPE_OK);
				win_compopup_set_msg(NULL,NULL, RS_DISPLAY_TOO_MANY_TP);
				win_compopup_open_ext(&back_saved);
				break;				
			}
			OSD_SetObjListCount(ol, OSD_GetObjListCount(ol) + 1);
			//OSD_TrackObject( (POBJECT_HEAD)ol, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
			OSD_TrackObject( (POBJECT_HEAD)&g_win_tplist, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
			OSD_ChangeFocus((POBJECT_HEAD)ol,OSD_GetObjListCount(ol) - 1, C_DRAW_SIGN_EVN_FLG | C_UPDATE_FOCUS);

			api_stop_timer(&tpturn_timer_id);
			tpturn_timer_id = api_start_timer(TPTURN_TIMER_NAME, TPTURN_TIMER_TIME, win_tplist_tpturn_handler);
			
		}
		else
		{
            OSD_TrackObject( (POBJECT_HEAD)&g_win_tplist, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
			//OSD_TrackObject( (POBJECT_HEAD)ol, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
             if( edit_tp_exist > 0)
             {
                 OSD_ChangeFocus((POBJECT_HEAD)ol,edit_tp_exist - 1, C_DRAW_SIGN_EVN_FLG | C_UPDATE_FOCUS);
                 edit_tp_exist = 0;
             }
             //OSD_TrackObject( (POBJECT_HEAD)ol, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
		}
		break;
	case VACT_TP_DEL:
		/* If not TP, can't DEL */
		if(OSD_GetObjListCount(ol) == 0)
			break;

		win_compopup_init(WIN_POPUP_TYPE_OKNO);
		win_compopup_set_msg(NULL, NULL,RS_DISPLAY_SURE_TO_DELETE);
		if(win_compopup_open_ext(&back_saved) != WIN_POP_CHOICE_YES)
			break;
		
		get_tp_at(s_node.sat_id,sel, &t_node);	
		del_tp_by_id(t_node.tp_id);
		OSD_SetObjListCount(ol, OSD_GetObjListCount(ol) -1);
		OSD_TrackObject( (POBJECT_HEAD)ol, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
		
		if( OSD_GetObjListCount(ol) > 0)
		{	
			if(sel ==  OSD_GetObjListCount(ol))	/* Delete last TP */
				OSD_ChangeFocus((POBJECT_HEAD)ol,OSD_GetObjListCount(ol) - 1, C_DRAW_SIGN_EVN_FLG | C_UPDATE_FOCUS);
			else
				tpturn_timer_id = api_start_timer(TPTURN_TIMER_NAME, TPTURN_TIMER_TIME, win_tplist_tpturn_handler);		
		}
		break;
	case VACT_TP_SRCH:
		/* If not TP, can't SEARCH */
		if(OSD_GetObjListCount(ol) == 0)
			break;

        sys_data_set_cur_satidx(cur_tp_sat_idx);
        tp_list_pos = OSD_GetObjListCurPoint(ol);
        tp_list_top = OSD_GetObjListTop(ol);

		choice = win_tpsrch_open(&ftaonly_VPid,&srch_chan_APid,&nit_PPid);
		if(choice==1)
		{
			win_tpsrch_set_search_param(ftaonly_VPid,srch_chan_APid,nit_PPid);
			sub_menu = (POBJECT_HEAD)&g_win_search;
			wincom_close_help();
			if(OSD_ObjOpen(sub_menu, 0xFFFFFFFF) != PROC_LEAVE)
			{
				menu_stack_push(sub_menu);
				set_movedish_flag(TRUE);/*only tp search,need not moving dish when return*/
			}
		}
		else if(choice==2) //pid search
		{
			tp_VPid = ftaonly_VPid;
			tp_APid = srch_chan_APid;
			tp_PPid = nit_PPid;
			
			prog_callback_register((prog_node_return)win_tplist_set_search_pid_callback);

			get_tp_at(s_node.sat_id,sel,&t_node);
			win_search_set_pid_param(t_node.tp_id, tp_VPid, tp_APid, tp_PPid);
			
			win_tpsrch_set_search_param(P_SEARCH_FTA|P_SEARCH_SCRAMBLED,P_SEARCH_TV|P_SEARCH_RADIO,0);

			sub_menu = (POBJECT_HEAD)&g_win_search;
			wincom_close_help();
			if(OSD_ObjOpen(sub_menu, 0xFFFFFFFF) != PROC_LEAVE)
				menu_stack_push(sub_menu);

		}
		else
		{
			//OSD_TrackObject( (POBJECT_HEAD)ol, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
			OSD_TrackObject( (POBJECT_HEAD)&g_win_tplist, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
		}	
		break;
		
	}


	return ret;	
}