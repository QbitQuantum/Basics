static PRESULT factoryset_sel_callback(POBJECT_HEAD pObj, VEVENT event, UINT32 param1, UINT32 param2)
{
	PRESULT ret = PROC_PASS;
	VACTION unact;
	UINT32 sel;
	UINT8 bID;
 	char str[10];
    	UINT16 * Uni_str;
    	UINT8* pstr;
	UINT16 cur_idx;
	COM_POP_LIST_TYPE_T list_type;
	OSD_RECT rect;
	COM_POP_LIST_PARAM_T param;
	UINT16 i,n = 0;
	S_NODE s_node;
	UINT32 flag;

	bID = OSD_GetObjID(pObj);

	switch(event)
	{
	case EVN_PRE_CHANGE:
		sel = *((UINT32*)param1);
		break;
		
	case EVN_POST_CHANGE:
		sel = param1;
		
		
	        if(bID == IDC_CON5)
	        {
			get_sat_at(sel,SET_SELECTED,&s_node);	
			#if 0
			#ifdef SUPPORT_TWO_TUNER  //guop modify
			#ifdef SUPPORT_SELECT_SAME_SAT
			OSD_SetTextFieldContent(&satsrch_txt6_note , STRING_ID, ((s_node.reserve_1 == 0) ? RS_LNB1 : RS_LNB2));
			#else
			OSD_SetTextFieldContent(&satsrch_txt6_note , STRING_ID, (s_node.tuner1_valid ? RS_LNB1 : RS_LNB2));
			#endif			
			OSD_DrawObject((POBJECT_HEAD)&satsrch_txt6_note, C_UPDATE_ALL);
			#endif
			#endif
	        }
		break;
		
	case EVN_REQUEST_STRING:
		sel = param1;
		Uni_str= (UINT16*)param2;
		if(bID == IDC_CON5)
		{
			get_sat_name_factory(2,sel,Uni_str);
			sys_data_set_cur_satidx(sel);
		}	
		break;
#if	 0	
	case EVN_UNKNOWN_ACTION:
		unact = (VACTION)(param1>>16);		
		if(unact ==  VACT_POP_UP)
		{
			OSD_SetRect2(&rect,&pObj->frame);
			switch(bID)
			{
			case SAT_ID:
				rect.uLeft -= 80;
				rect.uWidth += 80;
				list_type 	= POP_LIST_TYPE_SAT;
				rect.uHeight = 300;
				param.id 	= TUNER_EITHER;
				param.cur 	= SATSRCH_SAT_IDX;
				if(single_multi_srch_flag == 0)
					param.selecttype = POP_LIST_SINGLESELECT;
				else
				{
					MEMSET(sat_select,0,sizeof(sat_select));
					n = get_tuner_sat_cnt(TUNER_EITHER);
					if(n == 0)
					{
						list_type = 0xFF;
						break;
					}

					for(i=0;i<n;i++)
					{
						get_tuner_sat(TUNER_EITHER,i,&s_node);
						if(s_node.selected_flag)
							sat_select[i] = 1;							
					}
#if (defined(SUPPORT_TWO_TUNER) || !defined(SELECT_SAT_ONLY))
					param.selecttype = POP_LIST_MULTISELECT;
#else
					param.selecttype = POP_LIST_SINGLESELECT;
#endif
					param.select_array = sat_select;					
				}
				break;
			default:
				list_type = 0xFF;							
			}
			
			if(list_type == 0xFF)
				break;

			cur_idx = win_com_open_sub_list(list_type,&rect,&param);
			if(single_multi_srch_flag == 0)
			{
				if(cur_idx == LIST_INVALID_SEL_IDX || cur_idx == param.cur)
					break;
			}
			else
			{
				/* Check the select satellite */

#if (defined(SUPPORT_TWO_TUNER) || !defined(SELECT_SAT_ONLY))				
				for(i=0;i<n;i++)
				{
					if(win_comlist_ext_check_item_sel(i))
						flag = 1;
					else
						flag = 0;
					get_tuner_sat(TUNER_EITHER,i,&s_node);
					if(s_node.selected_flag != flag)
					{
						s_node.selected_flag = flag;
						modify_sat(s_node.sat_id, &s_node);						
					}
				}
				update_data(TYPE_SAT_NODE);
#endif				
			}

			if(single_multi_srch_flag == 0)
				SATSRCH_SAT_IDX = cur_idx;
			get_sat_at(cur_idx,SET_SELECTED,&s_node);		
#ifdef SUPPORT_SELECT_SAME_SAT
			OSD_SetTextFieldContent(&satsrch_txt6_note , STRING_ID, ((s_node.reserve_1 == 0) ? RS_LNB1 : RS_LNB2));
#else
			OSD_SetTextFieldContent(&satsrch_txt6_note , STRING_ID, (s_node.tuner1_valid ? RS_LNB1 : RS_LNB2));
#endif
			OSD_DrawObject((POBJECT_HEAD)&satsrch_txt6_note, C_UPDATE_ALL);
			OSD_TrackObject((POBJECT_HEAD)&satsrch_item1, C_DRAW_SIGN_EVN_FLG | C_UPDATE_ALL);
			if(single_multi_srch_flag)
			{
				/* TODO :
					Draw the select satellites name */
				//win_satsrch_set_drawselectsats();
				
				UINT16 sat_cnt = get_tuner_sat_cnt(TUNER_EITHER_SELECT);
				
				if(sat_cnt <=(SELSAT_ROW_CNT*2))
					win_satsrch_set_fix_drawselectsats();
				else
				{
					start_scroll_sat_id=0;
					api_stop_timer(&sat_display_scroll);
			        		sat_display_scroll = api_start_timer("SATDISP",500,(OSAL_T_TIMER_FUNC_PTR)sat_search_scroll_disp_handler);
				}
			}
		}
		break;
		#endif
	}

	return ret;
	
}