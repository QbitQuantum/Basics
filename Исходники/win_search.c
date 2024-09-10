static void win_search_program_append(UINT32 tp_idx, UINT16 prog_idx)
{
	UINT32 si,i,j,n,cnt,str_len;
	UINT16* pstr;
	OSD_RECT rect;
	UINT8	shidx;
	char    str[30];
	
	DBG_PRINTF("Enter %s....\n",__FUNCTION__);
	
	if(prog_idx != INVALID_ID)
	{
		P_NODE p_node;

		get_prog_at(prog_idx, &p_node);
		MEMCPY(&win_search_cur_prog[p_node.av_flag], &p_node, sizeof(p_node));
		
		srch_ch_cnt[p_node.av_flag] ++;		
		cnt = srch_ch_cnt[p_node.av_flag];

		if(cnt <= INFOR_CHAN_CNT)
		{
			si = 0;
			n = cnt;
		}
		else
		{
			si = cnt - INFOR_CHAN_CNT;
			n = INFOR_CHAN_CNT;
		}

		if(si != 0)
		{
			for(i=0;i<n - 1;i++)
				MEMCPY(display_strs[10 + p_node.av_flag*10 + i], display_strs[10 + p_node.av_flag*10 + i + 1], MAX_DISP_STR_LEN*2);
		}

		pstr = display_strs[10 + p_node.av_flag*10 + n - 1];		
		if(p_node.ca_mode)
			ComAscStr2Uni("$", pstr);
		else
			ComAscStr2Uni("", pstr);
		str_len = ComUniStrLen(pstr);
		ComUniStrCopyChar((UINT8*)&pstr[str_len] ,p_node.service_name);

		if(p_node.av_flag == PROG_TV_MODE)
		{
			rect.uLeft 	= TVB_L + 20;//INFO_TV_L;
			rect.uTop  	= TVB_T + INFO_TXT_H;//INFO_TV_T+4;
			rect.uWidth = INFO_TV_W;
			rect.uHeight= INFO_TXT_H;
			shidx = TV_TXT_SH_IDX;
		}
		else
		{
			rect.uLeft 	= RADIOB_L + 20;//INFO_RADIO_L;
			rect.uTop  	= RADIOB_T + INFO_TXT_H;//INFO_RADIO_T+4;
			rect.uWidth = INFO_TV_W;//INFO_RADIO_W;
			rect.uHeight= INFO_TXT_H;
			shidx = RADIO_TXT_SH_IDX;
		}
		
		for(i=0;i<n;i++)
		{
			pstr = display_strs[10 + p_node.av_flag*10 + i];
			//win_srch_draw_info(&rect, NULL,pstr, shidx);
			win_srch_draw_info_ex(&rect, NULL,pstr, INFOMATION_TXT_IDX);
			rect.uTop += rect.uHeight;
		}


		rect.uTop = TVB_T+3;
		rect.uLeft += (rect.uWidth-80);
		rect.uWidth = 80;
        rect.uHeight = TXT_H;
		sprintf(str,"%d",cnt);
		win_srch_draw_info(&rect, str,NULL, shidx);
		tp_chsrched = 1;
		
	}

	if(tp_idx != 0xFFFFFFFF)
	{
		T_NODE t_node;
		S_NODE s_node;

		get_tp_by_id(tp_idx, &t_node);
		//get_sat_at(cur_sat_pos, VIEW_ALL,&s_node);
		get_sat_by_id(cur_sat_id, &s_node);
		srch_tp_cnt ++;

		cnt = srch_tp_cnt;
		if(cnt <= INFOR_TP_CNT)
		{
			si = 0;
			n = cnt;
		}
		else
		{
			si = cnt - INFOR_TP_CNT;
			n = INFOR_TP_CNT;
		}
		
		if(si != 0)
		{
			for(i=0;i<n - 1;i++)
			{
				MEMCPY(display_strs[ 30 + i], display_strs[30 + i + 1], MAX_DISP_STR_LEN*2);
			}
		}
		if(n>1)
		{
			pstr = display_strs[ 30 + n - 2];
#if 0			
			str_len = ComUniStrLen(pstr);
#else
			str_len = tp_info_chw_tbl[0] + tp_info_chw_tbl[1] + tp_info_chw_tbl[2] + tp_info_chw_tbl[3] + tp_info_chw_tbl[4];
#endif
			if(tp_chsrched)
				ComAscStr2Uni("OK", &pstr[str_len]);
			else
				ComAscStr2Uni("Failed", &pstr[str_len]);
		}

		pstr = display_strs[30 + n - 1];
		
		sprintf(str,"%d",srch_tp_cnt);
		ComAscStr2Uni(str,&pstr[0]);

#if 0		
		str_len = ComUniStrLen(pstr);
		str_len = tp_info_chw_tbl[0];
		ComUniStrCopyChar(&pstr[str_len], s_node.sat_name);
		str_len = ComUniStrLen(pstr);
		sprintf(str," %d %c %d ... ",t_node.frq,(t_node.pol == 0)? 'H' : 'V',t_node.sym);
		ComAscStr2Uni(str,&pstr[str_len]);
#else
		str_len = tp_info_chw_tbl[0];
		ComUniStrCopyChar((UINT8*)&pstr[str_len], s_node.sat_name);
		
		str_len += tp_info_chw_tbl[1];
		sprintf(str,"%d",t_node.frq);
		ComAscStr2Uni(str,&pstr[str_len]);
		
		str_len += tp_info_chw_tbl[2];
		sprintf(str,"%c",(t_node.pol == 0)? 'H' : 'V');
		ComAscStr2Uni(str,&pstr[str_len]);

		str_len += tp_info_chw_tbl[3];
		sprintf(str,"%d",t_node.sym);
		ComAscStr2Uni(str,&pstr[str_len]);

		str_len += tp_info_chw_tbl[4];
		STRCPY(str,"");
		ComAscStr2Uni(str,&pstr[str_len]);

#endif

		
		tp_chsrched = 0;
		
		rect.uLeft 	= INFO_TP_L;
		rect.uTop  	= INFO_TP_T;
		rect.uWidth = INFO_TP_W;
		rect.uHeight= INFO_TXT_H;
		shidx = TP_TXT_SH_IDX;
		for(i=0;i<n;i++)
		{
			
			pstr = display_strs[30 + i];
#if 0			
			win_srch_draw_info(&rect, NULL,pstr, shidx);
#else
			rect.uLeft 	= INFO_TP_L;
			str_len = 0;
			pstr = display_strs[30 + i];
			for(j=0;j<7;j++)
			{
				rect.uWidth = tp_info_w_tbl[j] - 2;	
				if(j != 5)
					win_srch_draw_info(&rect, NULL,pstr, shidx);				
				else
					win_srch_draw_info(&rect, "...",NULL, shidx);
				rect.uLeft +=  tp_info_w_tbl[j] ;
				if(j < 5)
				{
					pstr += tp_info_chw_tbl[j];
					//pstr += str_len;
				}
			}
#endif

			rect.uTop += rect.uHeight;
		}		

		
	}

	DBG_PRINTF("Exit %s....\n",__FUNCTION__);	
}