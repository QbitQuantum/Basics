/*--------------------------------------*/
void CFrontier_API_SVDlg::OnPaitMap(void)
{
		if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	int m_CXpos=0,m_CYpos=0,m_CorYLenth = 160,m_CorXLenth = 160;
	int GraphLimit;
	struct 
	{
		int RobRadia;// 机器人的半径
	}VisRobot = {25};// 机器人的图形显示参数
	CRect rect2,rect3;

	CWnd* pWnd = GetDlgItem(IDC_LOCDRAW);//
	CDC* pControlDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pWnd->GetWindowRect(rect2);
	m_CXpos = (rect2.right-rect2.left)/2;
	m_CYpos = (rect2.bottom-rect2.top)/2;
	GraphLimit = 150;
	pControlDC->MoveTo(m_CXpos,m_CYpos-m_CorYLenth);// 机器人朝向,纵轴
	pControlDC->LineTo(m_CXpos,m_CYpos+m_CorYLenth);
	pControlDC->SelectStockObject(LTGRAY_BRUSH);//LTGRAY_BRUSH
	pControlDC->Ellipse(m_CXpos-5, m_CYpos-m_CorYLenth-5,m_CXpos+5, m_CYpos-m_CorYLenth+5 );

	pControlDC->MoveTo(m_CXpos-m_CorXLenth,m_CYpos);// 机器人横轴
	pControlDC->LineTo(m_CXpos+m_CorXLenth,m_CYpos);
	pControlDC->SelectStockObject(LTGRAY_BRUSH);//LTGRAY_BRUSH
	pControlDC->Ellipse(m_CXpos-m_CorXLenth-5, m_CYpos-5,m_CXpos-m_CorXLenth+5, m_CYpos+5 );

	pControlDC->SelectStockObject(HOLLOW_BRUSH);//LTGRAY_BRUSH
	pControlDC->Ellipse(m_CXpos-140-VisRobot.RobRadia, m_CYpos-140-VisRobot.RobRadia,m_CXpos+140+VisRobot.RobRadia, m_CYpos+140+VisRobot.RobRadia);	// 远处
	pControlDC->Ellipse(m_CXpos-20-VisRobot.RobRadia, m_CYpos-20-VisRobot.RobRadia,m_CXpos+20+VisRobot.RobRadia,m_CYpos+20+VisRobot.RobRadia);	//近处

	float temp_dist,temp_ang;
	int temp_far,temp_near;
	temp_far = 2500;
	temp_near = 300;
	int m_tempXPos;
	int m_tempYPos;
	BOOL temp_Blob[6];
	
	temp_Blob[0] = m_Blob1;
	temp_Blob[1] = m_Blob2;
	temp_Blob[2] = m_Blob3;
	temp_Blob[3] = m_Blob4;
	temp_Blob[4] = m_Blob5;
	temp_Blob[5] = m_Blob6;

	UpdateData(TRUE);

	/*------目标物显示------*/
	for (int k=0;k<6;k++)
	{
		if (temp_Blob[k] && VisionBlob[k][0].area>0)
		{	
			DISTANG temp_DistAng;
			memcpy(&temp_DistAng,&VisionDistAng[k][0],sizeof(temp_DistAng));
			CPen pen,*ppen;
			
			COLORREF ObjColor;
			ObjColor = ColorHLSToRGB((WORD)VisionBlob[k][0].hue,150,240);
			pen.CreatePen(PS_SOLID,1,ObjColor);
			CBrush ObjBrush;
			ObjBrush.CreateSolidBrush(ObjColor);
			pControlDC->SelectObject(&ObjBrush);
			ppen = pControlDC->SelectObject(&pen);
			
			if (temp_DistAng.Dist >= temp_far)
			{
				temp_dist = (float)temp_far;
			}
			else if (temp_DistAng.Dist <= temp_near)
			{
				temp_dist = (float)temp_near;
			}
			else
			{
				temp_dist = (float)temp_DistAng.Dist;
			}
			temp_dist = (temp_dist-temp_near)*120/(temp_far-temp_near+300)+(20+VisRobot.RobRadia);
			temp_ang = temp_DistAng.Angle;
			m_tempXPos = (int)(m_CXpos - temp_dist*sin(temp_ang*PI/180));
			m_tempYPos = (int)(m_CYpos - temp_dist*cos(temp_ang*PI/180));
			if (m_bVision)
				pControlDC->Ellipse(m_tempXPos-10,m_tempYPos-10,m_tempXPos+10,m_tempYPos+10);	
			pen.DeleteObject();
			ppen->DeleteObject();
		}
	}


	pWnd->ReleaseDC(pControlDC);
}