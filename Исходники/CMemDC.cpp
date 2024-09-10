	~CMemDC(){
                               //在内存画布释放时将内存画布的内容绘制在目标区域中
		m_pDC->BitBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),this,m_Rect.left,m_Rect.top,SRCCOPY);
		SelectObject(m_poldbmp);  //选中之前选中的位图对象
		if (m_poldbmp != NULL)   //判断位图对象是否为空
		{
			delete m_poldbmp;      //释放位图对象
		}
		DeleteObject(this);  //释放设备上下文
	}