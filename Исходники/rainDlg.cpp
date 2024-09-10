void CrainDlg::doThread()//由线程执行的方法
{
	CBrush aBrush;//画笔,主要用来填充颜色
	CPen aPen;//钢笔,主要用来画线条
	CRect aRect;//矩形,
	CWnd * pWind=GetDlgItem(IDC_PIC);//获取画图框资源
	CDC* pDC=pWind->GetDC();//画布
	struct dropletchain *pRain;//用来读取雨点链表
	while(1)
	{
		//画背景
		aBrush.CreateSolidBrush(RGB(0,0,0));//设置画笔的颜色,即天空的颜色
		pWind->GetClientRect(&aRect);//获取画布大小
		aRect.bottom-=DEFAULT_BOTTOM_HEIGHT;//修改底部的高度,底部向上为天空
		pDC->FillRect(aRect,&aBrush);//绘制上方天空
		aBrush.DeleteObject();//用完画笔删除
		aBrush.CreateSolidBrush(RGB(9,128,104));//设置池塘的颜色
		aRect.top+=aRect.Height();//顶部下移
		aRect.bottom+=DEFAULT_BOTTOM_HEIGHT;//底部高度下移
		pDC->FillRect(aRect,&aBrush);//绘制下方池塘
		aBrush.DeleteObject();//删除画笔
		pDC->SelectStockObject(NULL_BRUSH);//把DC设置成空心画笔,在画涟漪时可以画出空心椭圆
		pRain=pDropletchain;//把指针移向链表头
		while(pRain)
		{
			aPen.CreatePen(PS_SOLID,pRain->data->thick,pRain->data->color);//创建钢笔
			pDC->SelectObject(&aPen);//用这个钢笔来画画
			if(pRain->data->y>aRect.top)//若雨点到达池塘顶部
			{
				//画涟漪
				pDC->Ellipse(pRain->data->x-pRain->data->radius-ELLIPSE,pRain->data->y-pRain->data->radius,pRain->data->x+pRain->data->radius+ELLIPSE,pRain->data->y+pRain->data->radius);//画出椭圆
				pRain->data->radius++;//涟漪椭圆半径增大
				if(pRain->data->radius>pRain->data->len||pRain->data->x+pRain->data->radius+ELLIPSE>=aRect.Width())
					initDroplet(pRain->data);//如果雨点半径大于雨点长度则重新生成雨点
			}
			else
			{
				//画雨点
				pDC->MoveTo(pRain->data->x,pRain->data->y);//把画笔移动到指定的坐标
				pDC->LineTo(pRain->data->x+(int)pRain->data->len*sin(pRain->data->angle),pRain->data->y+(int)pRain->data->len*cos(pRain->data->angle));//根据角度和长度绘制出斜线
				pRain->data->x+=pRain->data->speed;pRain->data->y+=pRain->data->speed;//雨点的坐标增大,增大幅度为各自的speed
				if(pRain->data->x+(int)pRain->data->len*sin(pRain->data->angle)>=aRect.Width()-pRain->data->thick)
					initDroplet(pRain->data);//如果超出右侧界限则重新生成雨点
			}
			aPen.DeleteObject();//删除钢笔
			pRain=pRain->next;//
		}
		Sleep(100-m_slider.GetPos());//在死循环中休眠线程,形成动画效果
	}
	pDC->ReleaseOutputDC();//释放DC资源
}