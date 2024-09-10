static boolean CSettings_Dialog_HandleEvent(void *po, AEEEvent evt, uint16 wParam, uint32 dwParam)
{
	CSettings* pMe = (CSettings*) po;
	user *pUser=NULL;
	AECHAR *rangetext=NULL;
	char* charrangetext=NULL;
	unsigned long time=0;
   
	if(evt == EVT_WDG_GETPROPERTY && wParam == FID_PREFRECT) {
		//catch FID_PREFRECT and set preferred extent of menu

		AEERect rc;   
		ISHELL_GetDeviceInfo(pMe->pIShell, &pMe->DeviceInfo);
		if(pMe->isRoomimgDialog==1){
			pMe->isRoomimgDialog=0;
			rc.x = pMe->DeviceInfo.cxScreen/10;
			rc.y = pMe->DeviceInfo.cyScreen/2;
			rc.dx = pMe->DeviceInfo.cxScreen*5/6;
			rc.dy = pMe->DeviceInfo.cyScreen-pMe->DeviceInfo.cyScreen*3/5;
			*(AEERect*) dwParam = rc;
		}else{

			rc.x = 0;
			rc.y = pMe->DeviceInfo.cyScreen/4;
			rc.dx = pMe->DeviceInfo.cxScreen;
			rc.dy = pMe->DeviceInfo.cyScreen-pMe->DeviceInfo.cyScreen*19/56;
			*(AEERect*) dwParam = rc;
		}
		return TRUE;
	}

	if(evt == EVT_KEY && (wParam == AVK_CLR || wParam == AVK_SOFT2))
	{
		IROOTFORM_PopForm(pMe->rootForm);
		deleteDialog(pMe);
		deleteShdulerForm(pMe);
		if(pMe->dialog)
		{
			IDIALOG_Release(pMe->dialog);
			pMe->dialog=NULL;
		}
		return TRUE;
	}

	if(evt == EVT_KEY && wParam == AVK_SOFT1)
	{
	   if ( GetUserData(pMe->pIShell, &pUser))
		{			
			if(pMe->dialogEvent==1)
			{
		
				STRCPY(pUser->roomingState,"ON");
				
			}if(pMe->dialogEvent==2)
			{
				
				STRCPY(pUser->roomingState,"OFF");
			
			}
			if(pMe->dialogEvent==3)
			{

			IWIDGET_GetTextWidgetText(pMe->rangeCreateTextWidget,&rangetext);
			charrangetext=MALLOC(30);
			WSTRTOSTR(rangetext,charrangetext,30);

			if(IVALUEMODEL_GetBool(pMe->valueModel3))
			{
				STRCPY(pUser->sheduler,"h");
				if(STRTOUL(charrangetext, NULL, 10)>1000)
					time=500*3600000;
				else
					time = STRTOUL(charrangetext, NULL, 10)*3600000;		
			}
			if(IVALUEMODEL_GetBool(pMe->valueModel4))
			{
				STRCPY(pUser->sheduler,"m");
				time = STRTOUL(charrangetext, NULL, 10)*60000;
			}
			if(IVALUEMODEL_GetBool(pMe->valueModel5))
			{
				STRCPY(pUser->sheduler,"s");
				time = STRTOUL(charrangetext, NULL, 10)*1000;
			}		
			pUser->shedulePeriod=time;
				
		}
		SetUserData(pMe->pIShell, pUser);
		pMe->dialogEvent=0;
		FREEIF(charrangetext);
		FREEIF(pUser);
	}
		
	IROOTFORM_PopForm(pMe->rootForm);
	deleteDialog(pMe);
	deleteShdulerForm(pMe);

	if(pMe->dialog)
	{
		IDIALOG_Release(pMe->dialog);
		pMe->dialog=NULL;
	}
	return TRUE;

   }

   //the  default form handler is swapped with the AppForm handler
   // calling this allows the default form handler to handle the event
   return HANDLERDESC_Call(&pMe->dlgHandler, evt, wParam, dwParam);
}