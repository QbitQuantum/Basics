void CGyfxyHostView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	CWnd *pListCtrl		= GetDlgItem(IDC_LIST_RESULT);
	CWnd *pProgWnd		= GetDlgItem(IDC_PROGRESS_STATE); 
	/////////////////////////////////////////////////////////
	CWnd *pButStart		= GetDlgItem(IDC_TEST_START); 
	CWnd *pButStop		= GetDlgItem(IDC_TEST_STOP);
	CWnd *pButClose		= GetDlgItem(ID_FILE_CLOSE);

	CWnd *pButRst		= GetDlgItem(IDC_RESET); 
	CWnd *pButWPot 		= GetDlgItem(ID_WEIGHT_POT); 
	CWnd *pButWsample	= GetDlgItem(ID_WEIGHT_SAMPLE);  

	CWnd *pAutoNO		= GetDlgItem(IDC_BUTTON_AUTO_NO);
	CWnd *pDownload		= GetDlgItem(IDC_BUTTON_SAMPLE_DN);
	CWnd *pUpload		= GetDlgItem(IDC_BUTTON_SAMPLE_UD);

	CWnd *pLeftTempText		= GetDlgItem(IDC_STATIC_LEFT_TEMP);
	CWnd *pRightTempText	= GetDlgItem(IDC_STATIC_RIGHT_TEMP);
	CWnd *pWaterTempText	= GetDlgItem(IDC_STATIC_WATER_TEMP);
	CWnd *pInfo				= GetDlgItem(IDC_STATIC_INFO);

	if(pProgWnd!=NULL)
	{
		RECT rect, rectProgress;
		RECT rectStart,rectStop,rectClose,rectRst,rectWPot,rectWsample,rectList; 
		RECT rectAuto,rectDownload,rectUpload;

		RECT rectLeftTemp,rectRightTemp,rectWaterTemp,rectInfo;


		int iHeight;
		GetClientRect(&rect);
		pListCtrl->GetWindowRect(&rectList);
		pProgWnd->GetWindowRect(&rectProgress);  
		/////////////////////////////////////////
		pButStart->GetWindowRect(&rectStart); 
		pButClose->GetWindowRect(&rectClose); 
		pButRst->GetWindowRect(&rectRst);
		pButWPot->GetWindowRect(&rectWPot);
		pButWsample->GetWindowRect(&rectWsample); 

		pAutoNO->GetWindowRect(&rectAuto);
		pDownload->GetWindowRect(&rectDownload);
		pUpload->GetWindowRect(&rectUpload);


		pLeftTempText->GetWindowRect(&rectLeftTemp);		
		pRightTempText->GetWindowRect(&rectRightTemp);			
		pWaterTempText->GetWindowRect(&rectWaterTemp);			
		pInfo->GetWindowRect(&rectInfo);					
		/////////////////////////////////////////////
		ScreenToClient(&rectList);
		ScreenToClient(&rectProgress);  
		ScreenToClient(&rectStart); 
		ScreenToClient(&rectClose); 

		ScreenToClient(&rectRst);
		ScreenToClient(&rectWPot);
		ScreenToClient(&rectWsample); 

		ScreenToClient(&rectAuto);
		ScreenToClient(&rectDownload);
		ScreenToClient(&rectUpload); 

		ScreenToClient(&rectLeftTemp); 
		ScreenToClient(&rectRightTemp );
		ScreenToClient(&rectWaterTemp);
		ScreenToClient(&rectInfo); 
		///////////////////////////////////////////////////
		//按钮
		int iButHigh,iButWidth;
		iButHigh	= rectStart.bottom - rectStart.top;
		iButWidth	= rectStart.right  - rectStart.left;
		//
		rectRst.left		= 40;
		rectRst.right		= 40+iButWidth;
		rectRst.bottom		= rect.bottom-10;
		rectRst.top			= rect.bottom-10-iButHigh;
		pButRst->MoveWindow(&rectRst);
		pButRst->Invalidate(FALSE);

		//
		rectClose.right		= rect.right-40;
		rectClose.left		= rect.right-40-iButWidth;
		rectClose.bottom	= rect.bottom-10;;
		rectClose.top		=  rect.bottom-10-iButHigh;
		pButClose->MoveWindow(&rectClose);
		pButClose->Invalidate(FALSE);
		//称坩埚		 
		rectWPot.left		= 40+(rectClose.left-rectRst.left)/5;
		rectWPot.right		= rectWPot.left	+iButWidth;
		rectWPot.bottom		= rect.bottom-10;
		rectWPot.top		= rect.bottom-10-iButHigh;
		pButWPot->MoveWindow(&rectWPot);
		pButWPot->Invalidate(FALSE);
		//称样品
		rectWsample.left		= 40+(rectClose.left-rectRst.left)*2/5;
		rectWsample.right		= rectWsample.left	+iButWidth;
		rectWsample.bottom		= rect.bottom-10;
		rectWsample.top			= rect.bottom-10-iButHigh;
		pButWsample->MoveWindow(&rectWsample);
		pButWsample->Invalidate(FALSE);
		//		
		rectStart.left		= 40+(rectClose.left-rectRst.left)*3/5;
		rectStart.right		= rectStart.left	+iButWidth;
		rectStart.bottom		= rect.bottom-10;
		rectStart.top			= rect.bottom-10-iButHigh;
		pButStart->MoveWindow(&rectStart);
		pButStart->Invalidate(FALSE);  
		 
		rectStop.left		= 40+(rectClose.left-rectRst.left)*4/5;
		rectStop.right		= rectStop.left	+iButWidth;
		rectStop.bottom		= rect.bottom-10;
		rectStop.top		= rect.bottom-10-iButHigh;
		pButStop->MoveWindow(&rectStop);
		pButStop->Invalidate(FALSE);  
		//左温度,右温度
		//中间炉子温度
		//信息栏
		int staticHigh,staticWidth = 0;

		staticHigh			= rectLeftTemp.bottom - rectLeftTemp.top;
		staticWidth			= 80;
		rectLeftTemp.left	= 40; 
		rectLeftTemp.right	= 40+staticWidth;
		rectLeftTemp.bottom = (rect.bottom-100);
		rectLeftTemp.top    = (rectLeftTemp.bottom-staticHigh);

		pLeftTempText->MoveWindow(&rectLeftTemp);
		pLeftTempText->Invalidate(FALSE);

		rectRightTemp.left	= 40; 
		rectRightTemp.right	= 40+staticWidth;
		rectRightTemp.bottom = (rect.bottom-90+staticHigh);
		rectRightTemp.top    = (rectRightTemp.bottom-staticHigh);

		pRightTempText->MoveWindow(&rectRightTemp);
		pRightTempText->Invalidate(FALSE);


		rectWaterTemp.left	= rectRightTemp.left + 180;;
		rectWaterTemp.right	= rectWaterTemp.left+staticWidth;
		rectWaterTemp.bottom = (rect.bottom-100);
		rectWaterTemp.top    = (rectWaterTemp.bottom-staticHigh);

		pWaterTempText->MoveWindow(&rectWaterTemp);
		pWaterTempText->Invalidate(FALSE);

		rectInfo.left	= rectRightTemp.left + 180;; 
		rectInfo.right	= rectInfo.left+staticWidth;
		rectInfo.bottom = (rect.bottom-90+staticHigh);
		rectInfo.top    = (rectInfo.bottom-staticHigh);

		pInfo->MoveWindow(&rectInfo);
		pInfo->Invalidate(FALSE);
			//,,,;
		/*
		CWnd *pLeftTempText		= GetDlgItem(IDC_STATIC_LEFT_TEMP);
		CWnd *pRightTempText	= GetDlgItem(IDC_STATIC_RIGHT_TEMP);
		CWnd *	= GetDlgItem(IDC_STATIC_WATER_TEMP);
		CWnd *				= GetDlgItem(IDC_STATIC_INFO);
		*/

		//进度条
		iHeight = rectProgress.top-rectProgress.bottom;
		rectProgress.right = rect.right-rectProgress.left;		
		rectProgress.bottom = rect.bottom-40;
		rectProgress.top	= rectProgress.bottom +iHeight;
		pProgWnd->MoveWindow(&rectProgress);
		pProgWnd->Invalidate(FALSE);
		///////////////////////////////////////////////////
		iButHigh	= rectAuto.bottom - rectAuto.top;
		iButWidth	= rectAuto.right  - rectAuto.left;

		rectAuto.left		= 40;
		rectAuto.right		= 40+iButWidth;
		rectAuto.top		= rect.top+10;
		rectAuto.bottom		= rect.top+10+iButHigh;
		pAutoNO->MoveWindow(&rectAuto);
		pAutoNO->Invalidate(FALSE);

		
		rectUpload.right		= rect.right - 40;
		rectUpload.left			= rectUpload.right-iButWidth;
		rectUpload.top			= rect.top+10;
		rectUpload.bottom		= rect.top+10+iButHigh;
		pUpload->MoveWindow(&rectUpload);
		pUpload->Invalidate(FALSE);

		
		rectDownload.left		= (rectAuto.left+rectUpload.left)/2;
		rectDownload.right		= rectDownload.left	+iButWidth;
		rectDownload.top		= rect.top+10;
		rectDownload.bottom		= rect.top+10+iButHigh;
		pDownload->MoveWindow(&rectDownload);
		pDownload->Invalidate(FALSE);

		////结果报告 
		rectList.right	= rect.right-rectList.left;	
		rectList.top	= rectAuto.bottom +10;	
		rectList.bottom = (rect.bottom-120);
		pListCtrl->MoveWindow(&rectList);
		pListCtrl->Invalidate(FALSE); 
		///////////////////////////////////////////////////
	} 
}