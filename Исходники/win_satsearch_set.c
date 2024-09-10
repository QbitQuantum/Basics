static UINT8 win_satsrch_set_scroll_drawselectsats(UINT8  start_sat_idx)
{
    struct OSDRect rect;
    UINT16 i,sat_cnt,num;
    UINT16 col,row;
    TEXT_FIELD* txt = &satsrch_multisats_name;
    S_NODE s_node;
    UINT16 top;
    UINT16 str[50];
    UINT16 nStrLen;

    UINT8  disp_total_row,adjust_row,start_disp_id;
    UINT8  next_start_idx=start_sat_idx+2;

    if(single_multi_srch_flag == 0)
        return;

    MEMSET(sat_ids,0,sizeof(sat_ids)/sizeof(sat_ids[0]));

    sat_cnt = num = get_tuner_sat_cnt(TUNER_EITHER_SELECT);//get_selected_sat_num();
    if(num > SELSAT_ROW_CNT *2)
        num = SELSAT_ROW_CNT *2;

    txt->pString = display_strs[0];
    for(i=0; i<sat_cnt; i++)
    {
        get_tuner_sat(TUNER_EITHER_SELECT,i,&s_node);
        sat_ids[i] = s_node.sat_id;
    }

    if(start_sat_idx>=(sat_cnt+SELSAT_ROW_CNT*2-2))
        next_start_idx=0;

    start_disp_id=0;
    if(start_sat_idx==0)
    {
        disp_total_row=1;
        adjust_row=5;
    }
    else if(start_sat_idx==2)
    {
        disp_total_row=2;
        adjust_row=4;
    }
    else if(start_sat_idx==4)
    {
        disp_total_row=3;
        adjust_row=3;
    }
    else if(start_sat_idx==6)
    {
        disp_total_row=4;
        adjust_row=2;
    }
    else
    {
        disp_total_row=SELSAT_ROW_CNT;
        adjust_row=1;
        if(start_sat_idx>=(SELSAT_ROW_CNT*2))
            start_disp_id=start_sat_idx-(SELSAT_ROW_CNT*2)+2;
    }

    /*if(start_sat_idx==0)
    {
    	struct OSDRect r;

    	r.uLeft=SELSAT_L0;//txt.head.frame.uLeft;//200;
    	r.uTop=SELSAT_T-40;//txt.head.frame.uTop;//300;
    	r.uWidth=SELSAT_W*2+40;//txt.head.frame.uWidth;//100;
    	r.uHeight=SELSAT_H*5-30;//txt.head.frame.uHeight;//45;

    	OSD_DrawFrame(&r,RGB24_RGB1555(173,173,173),NULL);
    }*/

    for(i=/*0*//*start_sat_idx*/start_disp_id; i<(/*SELSAT_ROW_CNT*/disp_total_row*2+start_disp_id); i++)
    {
        row = (i-start_disp_id)/2+adjust_row;

        top = SELSAT_T + row * 30/*SELSAT_H*/-40;
        if(i%2 == 0)
            OSD_SetRect(&txt->head.frame, SELSAT_L0, top, SELSAT_W, SELSAT_H-6);
        else
            OSD_SetRect(&txt->head.frame, SELSAT_L1, top, SELSAT_W, SELSAT_H-6);

        get_tuner_sat(TUNER_EITHER_SELECT,i,&s_node);

        if(i<sat_cnt)
        {
            if(s_node.DiSEqC_type !=6)
                ComUniStrCopyChar((UINT8*)txt->pString, s_node.sat_name);
        }
        else
        {
            ComAscStr2Uni("", txt->pString);
            //next_start_idx=0;
        }
        OSD_DrawObject( (POBJECT_HEAD)txt, C_UPDATE_ALL);

        //if(adjust_row && (i%2==1))
        //	adjust_row-=2;
    }

    if(num == 0)
    {
        txt->pString = NULL;
        top = SELSAT_T + 2 * SELSAT_H+40;
        OSD_SetRect(&txt->head.frame, SELSAT_L0 + SELSAT_W/2, top, SELSAT_W, SELSAT_H-6);
        OSD_SetTextFieldContent(txt, STRING_ID , RS_DISPLAY_NO_SATELLITE/*RS_NO_SATELLITE_SELECT*/);
        OSD_DrawObject( (POBJECT_HEAD)txt, C_UPDATE_ALL);
    }

    return next_start_idx;
}