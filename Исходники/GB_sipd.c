static void GB_MsgHandle(SN_MSG *msg, GB_CONNECT_STATE *gb_cons)
{
	if (msg == NULL)
		return;

	switch (msg->msgId)
	{
		case MSG_ID_FWK_UPDATE_PARAM_IND:
		{
			stParamUpdateNotify *stNotify = (stParamUpdateNotify *)msg->para;
			switch(stNotify->prm_id)
			{
				case PRM_ID_GB_SIPD_CFG:
				{
					if(GB_Get_gGBConnStatus() == 0)
					{
						if(gb_cons->connfd > 0)
						{
							close(gb_cons->connfd);
							GB_ResetConState(gb_cons);
						}
						GB_Refresh_GBCfg();
					}
					else if((gb_cons->cur_state == GB_STATE_RUNNING && gb_cons->bUnRegister == 1)// 正在注销
						|| (GB_Get_gGBConnStatus() == 2) // 离线
						)  
					{
						if(gb_cons->connfd > 0)
						{
							close(gb_cons->connfd);
							GB_ResetConState(gb_cons);
						}
						GB_Set_gGBConnStatus(0);
						GB_Refresh_GBCfg();
					}
					else
					{
						gb_cons->bUnRegister = 1;
						GB_sipd_register(gb_cons, 1); // 不带认证的注销请求
						gb_cons->last_sendtime = get_cur_time()/1000;
						GB_Set_gGBConnStatus(0);
					}		
				}
				break;
				case PRM_ID_GB_SIPD_DEVMODE_CFG:
				{
					
				}
				break;
				
				default:
				break;
			}
		}
		break;
		
		case MSG_ID_FWK_REBOOT_REQ:
		case MSG_ID_FWK_POWER_OFF_REQ:
		case MSG_IF_FWK_IPCHANGE_IND:
		{
			PRM_GB_SIPD_CFG gb_cfg;
			
			TRACE(SCI_TRACE_NORMAL,MOD_GB,"%s  line=%d    msg->msgId=%d\n",__FUNCTION__,__LINE__,msg->msgId);

			SN_MEMSET(&gb_cfg,0,sizeof(gb_cfg));

			GB_Get_GBCfg(&gb_cfg);

			if(gb_cfg.enable != 1)
			{
				break;
			}
			
			if(GB_Get_gGBConnStatus() == 1)
			{
				gb_cons->bUnRegister = 1;
				GB_sipd_register(gb_cons, 1); // 不带认证的注销请求
				gb_cons->last_sendtime = get_cur_time()/1000;
			}
			else
			{
				if(gb_cons->connfd > 0)
				{
					close(gb_cons->connfd);
					GB_ResetConState(gb_cons);
				}

				GB_Set_gGBConnStatus(0);
			}

				gb_ipchange = 1;
				gb_ipchange_time = get_cur_time()/1000;
				//  退出国标模式
			
		}
		break;

		case MSG_ID_GB_GET_STATUS_REQ:
		{
			GB_GET_STATUS_RSP rsp;

			SN_MEMSET(&rsp,0,sizeof(rsp));

			rsp.result = 0;
			rsp.status = GB_Get_gGBConnStatus();

			SendMessageEx(msg->user, MOD_GB, msg->source, msg->xid, msg->thread, msg->msgId + 1, &rsp, sizeof(rsp));
		}
		break;
		
		default:
		{
			
		}
		break;
	}
	FreeMessage(&msg);
}