void CPropSelUser::drawSkin(void)
{

	if(!imgDialog)
		return;
	CDC *pdc=this->GetWindowDC();
	if(!pdc)return;
	CRect rc;
	this->GetWindowRect(&rc);
	Graphics g(pdc->m_hDC);

	int topHeight=32;//GetSystemMetrics(SM_CYFRAME)+GetSystemMetrics(SM_CYSIZE)+6;
	g.DrawImage(imgDialog,RectF(0.0f,0.0f,10.0f,topHeight),0.0f,0.0f,10.0f,topHeight,UnitPixel);
	g.DrawImage(imgDialog,RectF(10.0f,0.0f,rc.Width()-20,topHeight),9.0f,0.0f,1.0f,topHeight,UnitPixel);
	g.DrawImage(imgDialog,RectF((REAL)rc.Width()-10,0.0f,10.0f,topHeight),imgDialog->GetWidth()-10,0.0f,10.0f,topHeight,UnitPixel);
	m_bkColor=pdc->GetPixel(9,topHeight-1);
	m_txtColor^=m_bkColor;
	int bottomHeight=10;
	g.DrawImage(imgDialog,RectF(0.0f,topHeight,10.0f,rc.Height()-topHeight-bottomHeight),0.0f,topHeight,10.0f,imgDialog->GetHeight()-topHeight-bottomHeight,UnitPixel);
	g.DrawImage(imgDialog,RectF(rc.Width()-10.0f,topHeight,10.0f,rc.Height()-topHeight-bottomHeight),
		imgDialog->GetWidth()-10,topHeight,10.0f,1,UnitPixel);

	g.DrawImage(imgDialog,RectF(0,rc.Height()-bottomHeight,imgDialog->GetWidth()-5,bottomHeight),0,imgDialog->GetHeight()-bottomHeight,10,bottomHeight,UnitPixel);
	g.DrawImage(imgDialog,RectF(10,rc.Height()-bottomHeight,rc.Width()-20,bottomHeight),10,imgDialog->GetHeight()-bottomHeight,1,bottomHeight,UnitPixel);
	g.DrawImage(imgDialog,RectF(rc.Width()-10,rc.Height()-bottomHeight,10,bottomHeight),imgDialog->GetWidth()-10,imgDialog->GetHeight()-bottomHeight,10,bottomHeight,UnitPixel);

	CString s="宋体";

	Font font(s.AllocSysString(),12,0,UnitPixel);
	SolidBrush brush(Color(255,255,255));
	s.Format("请选择道具 [%s] 使用对象，当前游戏中有 %d 个可用用户对象",propItemName,maxUser);
	g.DrawString(s.AllocSysString(),-1,&font,PointF(5,5),0,&brush);
	
	StringFormat sf;
	sf.SetAlignment(StringAlignmentCenter);

	m_bnClose.Invalidate(FALSE);
	brush.SetColor(Color(0,0,0));
	Pen pen(&brush);//20081128
	REAL x,y,w,h; //20081128，计算具体图片的位置
	for(int i=0;i<maxUser;i++)
	{
		x=userRect[i].left+(66-userImg[i]->GetWidth())/2;
		y=userRect[i].top+(105-userImg[i]->GetHeight())/2;
		w=userImg[i]->GetWidth();
		h=userImg[i]->GetHeight();
		g.DrawImage(userImg[i],x,y,w,h);//画头像，替换原来的画头像代码
		//画选择区域边框
		g.DrawRectangle(&pen,userRect[i].left , userRect[i].top , 
			userRect[i].Width() , userRect[i].Height());
		g.DrawString(userName[i].AllocSysString() ,-1 ,&font , 
			RectF(userRect[i].left,userRect[i].bottom+5,userRect[i].Width(),30),&sf,&brush);
	}
	g.ReleaseHDC(pdc->m_hDC);
}