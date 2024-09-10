BOOL win_signal_update(void)
{
	POBJECT_HEAD pObj;
	PROGRESS_BAR* bar;
	TEXT_FIELD*	  txt;

	char str[20];
	INT str_len;


	pObj = (POBJECT_HEAD)&g_win_signal;
	if(pObj->pRoot == NULL)
		return FALSE;


	bar = &sig_bar_level;
	txt = &sig_txt_level_per;
	OSD_SetTextFieldContent(txt, STRING_NUM_PERCENT, OSD_GetProgressBarPos(bar));


	bar = &sig_bar_quality;
	txt = &sig_txt_quality_per;
	OSD_SetTextFieldContent(txt, STRING_NUM_PERCENT, OSD_GetProgressBarPos(bar));

	OSD_DrawObject(pObj, C_UPDATE_ALL);

#if 0
     struct OSDRect rect;
    VSCR vscr;
    int  i,j;
    extern struct osd_s3601_private *gp_osd_s3601_private0;
    UINT8        *pBuf,*pbyte;
    UINT32        *buf;
    //ge_s3601_private_t *osd_s3601_private0 = (ge_s3601_private_t *)(g_ge_dev->priv);
    UINT8 *ge_data_buf = (UINT8 *)(__MM_GE_START_ADDR);
    UINT8 *osd_bg_buf = (UINT8 *)((__MM_OSD_BK_ADDR1 + 31) & 0xFFFFFFE0);
    rect.uLeft = 240;
    rect.uTop  = 162;
    rect.uWidth  = 80;
    rect.uHeight = 160;
    pBuf = (UINT8 *)MALLOC(51200);
    MEMSET(pBuf,0,51200);
    vscr.bBlockID = 0;
    vscr.bColorMode = OSD_HD_ARGB8888;
    vscr.lpbScr = pBuf;
    vscr.updatePending = 1;
    vscr.vR = rect;
    if(color_test_flag)
    {
        libc_printf("\n===============================display buf======================================\n");
        for(i = 0; i < 2; i++)
        {
            pbyte = (UINT8 *)(ge_data_buf) + 5120 * (i+rect.uTop) + rect.uLeft * 4;//
            buf = (UINT32 *)pbyte;  
            for(j = 0;j < rect.uWidth;j++)
            {
                if(j % 8 == 0)
                {
                   libc_printf("\n"); 
                }
                libc_printf("0x%04x,",*buf++);
            }
        }
        libc_printf("\n=================================background buf=================================\n");
        for(i = 0; i < 2; i++)
        {
            pbyte = (UINT8 *)(osd_bg_buf) + 5120 * (i+rect.uTop) + rect.uLeft * 4;//
            buf = (UINT32 *)pbyte;  
            for(j = 0;j < rect.uWidth;j++)
            {
                if(j % 8 == 0)
                {
                   libc_printf("\n"); 
                }
                libc_printf("0x%04x,",*buf++);
            }
        }
        
    }
    while(color_test_flag)
    {
        MEMSET(pBuf,0,51200);
        OSDDrv_RegionRead(g_osd_dev,0,&vscr,&vscr.vR);
        libc_printf("\n----------------------------------------read virtual buf-------------------------------");
        for(i = 0; i < 2; i++)
        {
            pbyte = vscr.lpbScr;
            buf = (UINT32 *)pbyte;  
            for(j = 0;j < rect.uWidth;j++)
            {
                if(j % 8 == 0)
                {
                   libc_printf("\n"); 
                }
                libc_printf("0x%04x,",*buf++);
            }
        }
        libc_printf("\n----------------------------------------read background buf=-------------------------------");
        for(i = 0; i < 2; i++)
        {
            pbyte = (UINT8 *)(osd_bg_buf) + 5120 * (i+rect.uTop) + rect.uLeft * 4;//
            buf = (UINT32 *)pbyte;  
           
            for(j = 0;j < rect.uWidth;j++)
            {
                if(j % 8 == 0)
                {
                   libc_printf("\n"); 
                }
                libc_printf("0x%04x,",*buf++);
            }
        }
        osal_task_sleep(20);
        libc_printf("\n----------------------------------------write-------------------------------");
        OSDDrv_RegionWrite(g_osd_dev,0,&vscr,&vscr.vR);
        for(i = 0; i < 2; i++)
        {
            pbyte = (UINT8 *)(ge_data_buf) + 5120 * (i+rect.uTop) + rect.uLeft * 4;
            buf = (UINT32 *)pbyte;  
            for(j = 0;j < rect.uWidth;j++)
            {
                if(j % 8 == 0)
                {
                   libc_printf("\n"); 
                }
                libc_printf("0x%04x,",*buf++);
            }
        }
        libc_printf("\n----------------------------------------End-------------------------------");
        for(i = 0; i < 2; i++)
        osal_task_sleep(100);
    }
#endif
	return TRUE;
}