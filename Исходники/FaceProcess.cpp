//响应时间事件
void CFaceProcess::OnTimer(UINT nIDEvent){
	//AfxMessageBox("In OnTimer()");
	 CString     temp="";
 	 const char  *pszStr="";
	 int         match=0;
switch(nIDEvent){
	//定时器1的相应处理部分
   case timer:
	if(m_Video){
		if( !cvGrabFrame( m_Video))
			return ;
		m_GrabFrame = cvRetrieveFrame(m_Video );
		if( !m_GrabFrame)
			return ;
		if( !m_SaveFrame)
			m_SaveFrame = cvCreateImage( cvSize(m_GrabFrame->width,m_GrabFrame->height),
			IPL_DEPTH_8U, m_GrabFrame->nChannels );
		if( m_GrabFrame->origin == IPL_ORIGIN_TL )
			cvCopy( m_GrabFrame, m_SaveFrame, 0 );
		else
			cvFlip( m_GrabFrame, m_SaveFrame, 0 );
//		m_GrabFrame=cvQueryFrame(m_Video);
// 		if(m_GrabFrame->origin==0)
//		m_GrabFrame->origin=1;
        /**************对获取的帧进行人脸检测处理并且显示*****************/
		faceDetector.detect_and_draw(m_SaveFrame);
        //m_GrabFrame=faceDetector.getSrcImage();
	    m_CvvImage.CopyOf(m_SaveFrame,1);
	    m_CvvImage.DrawToHDC(hDC,&rect);
		//cvReleaseImage(&m_SaveFrame);
	 }
//	return;
	/************************************************************************/
	/* 获得b_Process状态                                                             */
	/************************************************************************/
	if(m_Video && b_flagProcess==true)
		b_Process=1;
	else if(m_Video && b_flagProcess==false)
		b_Process=2;
	else
		b_Process=0;
	/************************************************************************/
	/* 根据b_Process状态动态设置控件有效性                                                            */
	/************************************************************************/
     if(b_Process==1)//此时可以关摄像头、保存图片
	 {
		 GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(true);//使控件有效
		 GetDlgItem(IDC_SAVE_PIC)->EnableWindow(true);    //使控件有效
	 }
	 else if(b_Process==2)//此时可以人脸识别、匹配率显示，不能保存图片
	 {
		//更新状态
		GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(true); //使控件有效
		GetDlgItem(IDC_RECOGNISE)->EnableWindow(true);    //使控件有效
        GetDlgItem(IDC_SAVE_PIC)->EnableWindow(false);    //使控件wu效   
	   /******此时可保存供人脸识别用的图片**************************
		//  每次保存五张
		//  定时器而负责定时训练图片，并更新匹配率
		//  保存图片不断覆盖以前的图片
	   ****************************/		
		if((count % 5)==0)
		           count=1;
		 pszStr = testFileName[count].GetBuffer(testFileName[count].GetLength());
		 m_snap=cvCreateImage(cvGetSize(m_SaveFrame),m_SaveFrame->depth,m_SaveFrame->nChannels);
		 cvCopy(m_SaveFrame,m_snap,NULL);
		 //m_snap->origin=1;//等于0保存倒立图向
		 //检测人脸并保存测试图片
		//AfxMessageBox(CString(pszStr)+CString(itoa(count,chEdit,10)));
	    try{
		  if(faceDetector.detect_and_draw(m_snap)){
		     faceImage=faceDetector.getFaceImage();
			 if(faceImage){
			    //faceImage->origin=1;
		     //化简图片
			    if(faceSimplifier.Simplify(faceImage)){
				   faceGray=faceSimplifier.getFaceImage();
				   //faceGray->origin=1;//等于0保存倒立图向
				   cvSaveImage(pszStr,faceGray);	//把图像写入文件
				 //AfxMessageBox(CString(pszStr)+CString(itoa(count,chEdit,10))+"t1");
				   count++;
				}
			}// if(faceImage)
		  }
		}catch(...)  //重要,避免检测不到人脸时的异常终止
		{ /* AfxMessageBox("保存图片失败！！");*/	return ; }
	 }else //b_Process==0)  //此时只可以进行打开摄像头操或者退出
	 {
		 GetDlgItem(IDC_STATIC_OTHER)->EnableWindow(FALSE);//使控件无效
		 GetDlgItem(IDC_SAVE_PIC)->EnableWindow(FALSE);//使控件无效
		 GetDlgItem(IDC_RECOGNISE)->EnableWindow(FALSE);//使控件无效
		 GetDlgItem(ID_CLOSE_CAPTURE)->EnableWindow(FALSE);//使控件无效
	 }
	/************************************************************************/
	/* 显示属性   需要随时更新的在次显示，更新慢的在慢定时器facetimer中更新*/
	/************************************************************************/
	   m_fameCount++;
	//	m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_COUNT);
	  itoa(m_fameCount,chEdit,10);
	  SetDlgItemText(IDC_STATIC_FRAME_COUNT,chEdit);
	break;
		//定时器2的相应处理部分
    case faceTimer:
	   //****************//人脸识别
	 correct=correct+faceRecognitor.recognize();
	 totalTest+=5;
	 matchPercent=float(correct)/totalTest;
	 match=int(matchPercent*100);
	/************************************************************************/
	/* 显示属性   需要随时更新的在次显示，更新慢的在慢定时器facetimer中更新*/
	/************************************************************************/	
    //匹配率的更新
	 itoa(match,chEdit,10);
	 temp=" "+CString(chEdit)+" %";
	 SetDlgItemText(IDC_STATIC_CORRECT,temp);
	 GetDlgItem(IDC_STATIC_CORRECT)->EnableWindow(TRUE);//使控件有效
	//根据匹配判断是否可以进入下一步
	 if(matchPercent>0.75 && totalTest>20)
        GetDlgItem(IDC_OK)->EnableWindow(TRUE);//使控件有效
	//其他更新
	 m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_POS_MSEC);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_OTHER,chEdit);
	 m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_WIDTH);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_Width,chEdit);
	 m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FRAME_HEIGHT);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_HEIGHT,chEdit);
     m_vieoProtery=cvGetCaptureProperty(m_Video,CV_CAP_PROP_FPS);
	 itoa(m_vieoProtery,chEdit,10);
	 SetDlgItemText(IDC_STATIC_FPS,chEdit);
   break;
   default:
	       break;
	}
	//调用基类时间
	CDialog::OnTimer(nIDEvent);
}