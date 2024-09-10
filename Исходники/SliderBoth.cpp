void SliderBoth::SetBlockColor()
{
#if 1
	CClientDC dc(this);
	//CDC* pdc = this->GetDC();
	//CDC*dc = this->GetDC();
	CRect rc;
	GetClientRect(&rc);
	
	CreateCompatibleDC((HDC)&dc);


	int iNumTic=(pos.iMax-pos.iMin)/pos.iTick;
	const int iL=MARGIN_SLIDE;
	const int iR=rc.right-MARGIN_SLIDE;
	const double dbStep=(iR-iL)*1.0/iNumTic;
	double db=iL;



	CBrush brush;             
	//brush.CreateSolidBrush(RGB(200,100,255));  
	brush.CreateSolidBrush(RGB(165,196,211));   
	//CBrush * pOldBrush= dc.SelectObject (&brush);
	CBrush * pOldBrush= dc.SelectObject (&brush);//LSC


	double lval = pos.iL*dbStep;//左边滑块
	double rval = pos.iR*dbStep;//右边滑块

	int iM=iNumTic/2;
	int RectaParam1,RectaParam2 = rc.top+1,RectaParam3,RectaParam4 = rc.bottom-MARGIN_SLIDE*2;

	if (pos.iL>=iM)
	{
		RectaParam1 = (int)lval;//+MARGIN_SLIDE*2;
	}else 
	{
		RectaParam1 = (int)lval+MARGIN_SLIDE*2;
	}

	if (pos.iR <= iM)
	{
		RectaParam3 = (int)rval+12;

	}else
	{
		RectaParam3 = (int)rval+3;
	}

//	dc.Rectangle((int)lval+MARGIN_SLIDE*2,rc.top+1,(int)rval,rc.bottom-MARGIN_SLIDE*2); 
	dc.Rectangle(RectaParam1,RectaParam2,RectaParam3,RectaParam4);
	dc.SelectObject (pOldBrush);
	brush.DeleteObject();
#endif
}