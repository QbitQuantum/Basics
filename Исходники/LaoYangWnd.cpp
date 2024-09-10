//注: 更新操作全部在后台设备描述表完成 然后把后台的显示到前景  因为内存的速度远远大于显示器
void CLaoYangWnd::Update()
{
	static int oldTime=0;//计时器
	int newTime=GetTickCount();//返回当前时间
	if(newTime-oldTime<100)//50毫秒走一步
		return;
	
	oldTime=newTime;//更新时间
	int i,j;								
	::FillRect(this->hbackdc,&this->clientRC,(HBRUSH)GetStockObject(WHITE_BRUSH));//白色刷子擦除客户区域
	///////////////画网格//////////////////		
	for(i = 0;i<50*20;i+=20)
	{
		::MoveToEx(this->hbackdc,i,0,NULL);
		::LineTo(this->hbackdc,i,50*15);
	}
	for(i = 0;i<50*15;i+=15)
	{
		::MoveToEx(this->hbackdc,0,i,NULL);
		::LineTo(this->hbackdc,50*20,i);
	}
	///////////////画地图///////////////////
	HBRUSH hb = ::CreateSolidBrush(RGB(0,0,0));
	::SelectObject(this->hbackdc,hb);
	for(j = 0;j<51;j++)
		for(i = 0;i<51;i++)
			if('1' == path[j][i])
				::Rectangle(this->hbackdc,i*20,j*15,i*20+20,j*15+15);
	//////////////画路径////////////////////
	char buffer[500] = {0};
	sprintf(buffer,"起点(%d,%d) 终点(%d,%d)",res[this->sumway-1].y,
		res[this->sumway-1].x,res[0].y,res[0].x);
	TextOut(hbackdc,450,0,buffer,strlen(buffer));
	HBRUSH hbway = ::CreateSolidBrush(RGB(0,255,0));
	::SelectObject(this->hbackdc,hbway);
	for(i = this->sumway-1 /*- this->step*/;i>=0;i--)
	{				
		int x1 = res[i].y*20,y1 = res[i].x*15;
		int x2 = x1+20,y2 = y1+15;
		::Rectangle(this->hbackdc,x1,y1,x2,y2);
	}	
	//////////////贴位图///////////////////
	TransparentBlt(this->hbackdc,res[this->sumway - this->step-1].y*20,
		res[this->sumway - this->step-1].x*15,
		w,h,this->memDC,0,0,this->w,this->h,GetPixel(this->memDC,0,0));
	if(this->sumway - this->step > 1)//行走的实现
	    this->step++;
	//////////////后台设备描述表在前景中显示///////////////////////////
	::BitBlt(this->hdc,0,0,this->clientRC.right,this->clientRC.bottom,this->hbackdc,0,0,SRCCOPY);
	::DeleteObject(hbway);	
	::DeleteObject(hb);
}