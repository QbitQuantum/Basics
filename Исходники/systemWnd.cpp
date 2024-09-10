BOOL CGmodeWnd::Exec()
{
	int			i;
	BOOL		bPush = FALSE;
	POINT		icPt;
	char		str[MAX_PATH];

	if(cgview_mode!=sysInf.execMode)return FALSE;
	switch(state){
	  case 0:
	  case 2:
	  case 4:
	  case 5:
		time = bgInf.look_cnt-timeGetTime();
		baseWnd.alpha = float(bgInf.look_max-time)/bgInf.look_max;
		if(time<=0){
			baseWnd.alpha = 1.0f;
			bgInf.look_cnt = 0;
			if(state==4)state = 1;
			else state ++;
		}
		if(state==3 && (selectNum==5 || selectNum==6 || selectNum==7)){
			bgInf.look_max = 2100;
			bgInf.look_cnt = timeGetTime() +bgInf.look_max;
		}else if(state==5){
			baseWnd.alpha = 1.0f -baseWnd.alpha;
		}else if(state==6){
			changeExecMode( opening_mode );	
		}
		panel[0].alpha = panel[1].alpha = button.alpha = baseWnd.alpha;
		return TRUE;
	  case 1:
		if(keyState.push_action && selectNum>=0){
			if(AVG_GetCgFlag(selectNum+1)==FALSE)break;
			PlayEffectNum(evtHandle[1],SelectSnd);
			wsprintf(str,"v00%02d0",selectNum);
			baseWnd.loadLGF(pack_eventcg,str);
			state = 2;
			bgInf.look_max = 900;
			bgInf.look_cnt = timeGetTime() +bgInf.look_max;
			panel[0].alpha = panel[1].alpha = button.alpha = baseWnd.alpha = 0;
			switch(selectNum){
			  case 5:
				scrollOffset.x = 680;
				scrollOffset.y = 0;
				break;
			  case 6:
				scrollOffset.x = 0;
				scrollOffset.y = 600;
				break;
			  case 7:
				scrollOffset.x = 0;
				scrollOffset.y = 0;
				break;
			}
			break;
		}else if(keyState.push_left || keyState.push_up){
			bPush = TRUE;
			if(selectNum==0)selectNum = 11;
			else selectNum --;
		}else if(keyState.push_right || keyState.push_down){
			bPush = TRUE;
			selectNum ++;
			if(selectNum > 11)selectNum = 0;
		}
		if(bPush){
			icPt.x = 54  +(selectNum%4)*177 +50;
			icPt.y = 104 +(selectNum/4)*136 +50;
			ClientToScreen(sysInf.hWnd,&icPt);
			SetCursorPos(icPt.x, icPt.y);
		}else{
			selectNum = -1;
		}
		for(i=0;i<12;i++){
			rect.left = 54+ 177*(i%4);	rect.right = rect.left +160;
			rect.top = 104+136*(i/4);	rect.bottom = rect.top +120;
			if(PtInRect(&rect,sysInf.msPoint)){
				selectNum = i;
				break;
			}
		}
		if(btn.CheckState(&sysInf.msPoint) || keyState.push_cancel){
			PlayEffectNum(evtHandle[1],CancelSnd);
			baseWnd.BltFast(0,0,&g_DibInf.colorBuf,NULL,FALSE);
			state = 5;
			bgInf.look_max = 900;
			bgInf.look_cnt = timeGetTime() +bgInf.look_max;
			return TRUE;
		}
		break;
	  case 3:
		switch(selectNum){
		  case 5:
			time = bgInf.look_cnt-timeGetTime();
			if(time<=0){
				scrollOffset.x = 0;
				scrollOffset.y = 680;
			}else{
				scrollOffset.x = 680 -(bgInf.look_max-time)*680/bgInf.look_max;
				scrollOffset.y = (bgInf.look_max-time)*680/bgInf.look_max;
			}
			break;
		  case 6:
			time = bgInf.look_cnt-timeGetTime();
			scrollOffset.x = 0;
			if(time<=0){
				scrollOffset.y = 0;
			}else{
				scrollOffset.y = 600-(bgInf.look_max-time)*600/bgInf.look_max;
			}
			break;
		  case 7:
			time = bgInf.look_cnt-timeGetTime();
			scrollOffset.x = 0;
			if(time<=0){
				scrollOffset.y = 600;
			}else{
				scrollOffset.y = (bgInf.look_max-time)*600/bgInf.look_max;
			}
			break;
		}
		if(keyState.push_action || keyState.push_cancel){
			PlayEffectNum(evtHandle[1],CancelSnd);
			baseWnd.loadLGF(pack_gparts,"CGmodeBase");
			state = 4;
			bgInf.look_max = 900;
			bgInf.look_cnt = timeGetTime() +bgInf.look_max;
			panel[0].alpha = panel[1].alpha = button.alpha = baseWnd.alpha = 0;
		}
		break;
	}
	return TRUE;
} // CGmodeWnd::Exec