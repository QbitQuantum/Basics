	int Global_Plan(GP_FUNC_INPUT * pInput, GP_INFO * pData, GP_LOCAL_DATA * pLocal)
	{
		
		/* 0 全局规划预处理 */
		/* 0.1 调用计数器自增 */
		if(myFrameid==1)
			MBUG("WARNING:this shell is for simulate only, no use any more\n");
		++myFrameid;
		pData->header.id = myFrameid;
		MBUG("\n*************************FRAME_ID %d***********************************\n", myFrameid);
		/* 0.2 检查规划器状态 */
		
		if(RNDF_ERROR == gp.stat())
			{
				MBUG("GP@%d : GP is INVALID(RNDF STATUS ERROR, CHECK FILE task OR RECOVERY POINT)!\n", myFrameid);
				MBUG("**********************************************************************\n");
				return 1;
			}
		
		/* 0.3 预置全局规划信息，更新动态数据 */
		
		gpInput = pInput;
		gpOutput = pData;
		gpEvent = pLocal;
		memcpy(&pData->state, &pInput->state, sizeof(STATE));
		gps[0] = pInput->state.pos.com_coord.x;
		gps[1] = pInput->state.pos.com_coord.y;
		gps[2] = pInput->state.pos.yaw*(180.0*1e-8)/3.1415926535898;

#ifdef USING_ROBIX4
		rbxReadStatus(&robixStatus);
#else
		if(myFrameid==1)
			robixStatus=S_INVALID;
		else
			robixStatus=S_ROAD_NAV;
#endif
		/* 1 执行全局规划 */
		switch(robixStatus)
		{
		case S_INVALID:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "N/A", "S_INVALID");
			tryRecover();
			MBUG("**********************************************************************\n");
			break;
		case S_WAIT:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "N/A", "S_WAIT");
			tryRecover();
			MBUG("**********************************************************************\n");
			break;
		case S_WAIT_LIGHT:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_WAIT_LIGHT");
			gp.context(gps,gpOutput);
			MBUG("**********************************************************************\n");
			break;
		case S_ROAD_NAV:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_ROAD_NAV");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_CROSS_UND:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_CROSS_UND");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_STRAIGHT:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_STRAIGHT");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_LEFT:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_LEFT");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_RIGHT:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_RIGHT");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_UTURN:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_UTURN");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_PARKING:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_PARKING");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_FREE_RUN:
			MBUG("GP@%d : gpState = {%s} (robixStatus = %s)\n", myFrameid, "Run", "S_FREE_RUN");
			trySwitch();
			MBUG("**********************************************************************\n");
			break;
		case S_TASK_OVER:
			MBUG("GP@%d: gpState = {%s} (robixStatus = %s)\n", myFrameid, "Off", "S_TASK_OVER");
			gpState = Off;
			gp.context(gps,gpOutput);
			MBUG("**********************************************************************\n");
			break;
		default:
			break;
		}
		return 0;
	}