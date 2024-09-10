UINT32 osdwnd_hidewnd(PGUI_WINDOW pwnd,UINT32 param)
{//clear wnd
	UINT32 i;
	PGUI_VSCR	pvscr;
	PGUI_REGION 	prgn;
	PGUI_OBJWND wndobj;
	//TODO:windows clear code
	
	if(gelib_get_wndmonitor()&&g_wndrects_cnt)
	{
		wndobj = (PGUI_OBJWND)param;
		for(i = 0;i < g_wndrects_idx;i++)
		{
			if(MEMCMP(&(wndobj->frame),&(g_wnd_rects[i]),sizeof(GUI_RECT)) == 0)
			{
				MEMSET(&(g_wnd_rects[i]),0x0,sizeof(GUI_RECT));

				if(g_wndrects_cnt > 0)
					g_wndrects_cnt--;
			}
		}

		if(gelib_wndrects_showoff() && g_osdwnd_onoff)
		{
			pvscr = OSD_GetTaskVscr(osal_task_get_current_id());
			prgn = gelib_getdstrgn(pvscr->dst_layer,pvscr->dst_rgn);
			ge_show_onoff((struct ge_device *)gui_dev,(ge_surface_desc_t *)prgn->hsurf,0);
			if(gelib_getdual_support())
			{
				prgn = gelib_getdstrgn(GUI_SLVGMA_SURF,0);
				ge_show_onoff_deo((struct ge_device *)gui_dev,(ge_surface_desc_t *)prgn->hsurf,0);
			}			
			
			g_osdwnd_onoff = 0;
		}
	}
	else if((g_wndrects_cnt == 0)&&(g_wnd_monitors == 1))
	{
		if(gelib_wndrects_showoff() && g_osdwnd_onoff)
		{
			pvscr = OSD_GetTaskVscr(osal_task_get_current_id());
			prgn = gelib_getdstrgn(pvscr->dst_layer,pvscr->dst_rgn);
			ge_show_onoff((struct ge_device *)gui_dev,(ge_surface_desc_t *)prgn->hsurf,0);
			
			g_osdwnd_onoff = 0;
		}
	}
	
	return 0;
}