void CDlgFeatMatch::OnMatchsingle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);  //Inputs from controls
    m_image=m_pView->GetDocument()->image;
	
	if (m_image==NULL)
	{
		MessageBox("Input image!");
		return;
	}
	if (featmodel==NULL)
	{
		MessageBox("Train model!");
		return;
	}
	
    if(!m_wholetarget)
	{        
		mvSetFeatParam(MV_TARGET_X,m_troix,featparam);
		mvSetFeatParam(MV_TARGET_Y,m_troiy,featparam);
		mvSetFeatParam(MV_TARGETROI_X,m_troiwidth,featparam);
		mvSetFeatParam(MV_TARGETROI_Y,m_troilength,featparam);
		mvSetFeatParam(MV_ACCEPTANCE,m_acceptance,featparam);

       	CDC* mpDC =m_pView->GetDC();        // Obtain display control's DC
		HDC mhDC = mpDC ->GetSafeHdc();   
		
		CPen yellowpen;
		yellowpen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
		CPen* pOldPen = mpDC->SelectObject(&yellowpen);
		
		mpDC->MoveTo(m_troix,m_troiy);
		mpDC->LineTo(m_troix+m_troiwidth,m_troiy);
		mpDC->MoveTo(m_troix+m_troiwidth,m_troiy);
		mpDC->LineTo(m_troix+m_troiwidth,m_troiy+m_troilength);
		mpDC->MoveTo(m_troix+m_troiwidth,m_troiy+m_troilength);
		mpDC->LineTo(m_troix,m_troiy+m_troilength);
		mpDC->MoveTo(m_troix,m_troiy+m_troilength); 
		mpDC->LineTo(m_troix,m_troiy);
		
		mpDC->SelectObject(pOldPen); 
        ReleaseDC( mpDC );
	}
	if(m_wholetarget)
	{
		mvSetFeatParam(MV_TARGET_X,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGET_Y,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGETROI_X,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_TARGETROI_Y,MV_DEFAULT,featparam);
		mvSetFeatParam(MV_ACCEPTANCE,m_acceptance,featparam);
	}

	double t1=(double)mvGetTickCount();
    if(!mvFeatFind(m_image,featmodel,featparam,featresult))
	{
		MessageBox("No match image found!");
		return;
	}
	double t2=(double)mvGetTickCount();
	m_time=(t2-t1)/mvGetTickFrequency()*1000;
	
	mvFeatGetResult(featresult,MV_RESULT_X,&m_posx);
	mvFeatGetResult(featresult,MV_RESULT_Y,&m_posy);
	mvFeatGetResult(featresult,MV_RESULT_SCORE,&m_score);

	
	UpdateData(FALSE);
    

	CDC* mpDC =m_pView->GetDC();        // Obtain display control's DC
    HDC mhDC = mpDC ->GetSafeHdc();   

	CPen greenpen;
	greenpen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	CPen* pOldPen = mpDC->SelectObject(&greenpen);
    
	int rx=m_modelwidth/2;
	int ry=m_modellength/2;

	mpDC->MoveTo(m_posx-rx,m_posy-ry);
	mpDC->LineTo(m_posx+rx,m_posy-ry);
	mpDC->MoveTo(m_posx+rx,m_posy-ry);
	mpDC->LineTo(m_posx+rx,m_posy+ry);
	mpDC->MoveTo(m_posx+rx,m_posy+ry);
	mpDC->LineTo(m_posx-rx,m_posy+ry);
	mpDC->MoveTo(m_posx-rx,m_posy+ry);
	mpDC->LineTo(m_posx-rx,m_posy-ry);
	
    mpDC->SetPixel(m_posx,m_posy,RGB(0,255,0));
	mpDC->MoveTo(m_posx-3,m_posy);
	mpDC->LineTo(m_posx+4,m_posy);
	mpDC->MoveTo(m_posx,m_posy-3);
	mpDC->LineTo(m_posx,m_posy+4);
	
    mpDC->SelectObject(pOldPen); 
    ReleaseDC( mpDC );
}