BOOL CDlgIntensity::OnInitDialog() 
{
	// 指向源图像象素的指针
	unsigned char * lpSrc;
	
	// 循环变量
	LONG i;
	LONG j;
	
	// 调用默认OnInitDialog函数
	CDialog::OnInitDialog();
	
	// 获取绘制直方图的标签
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	
	// 计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);
	
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);
	
	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;
	
	// 设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	
	// 重置计数为0
	for (i = 0; i < 256; i ++)
	{
		// 清零
		m_lCount[i] = 0;
	}
	
	// 图像每行的字节数
	LONG lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(m_lWidth * 8);
	
	// 计算各个灰度值的计数
	for (i = 0; i < m_lHeight; i ++)
	{
		for (j = 0; j < m_lWidth; j ++)
		{
			lpSrc = (unsigned char *)m_lpDIBBits + lLineBytes * i + j;
			
			// 计数加1
			m_lCount[*(lpSrc)]++;
		}
	}
	
	// 初始化拖动状态
	m_iIsDraging = 0;
	
	// 返回TRUE
	return TRUE;
}