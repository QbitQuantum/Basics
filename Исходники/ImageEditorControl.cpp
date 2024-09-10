//绘制背景
BOOL CImageEditorControl::OnEraseBkgnd(CDC * pDC)
{
	//获取大小
	CRect rcClient;
	GetClientRect(&rcClient);

	//创建缓冲
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//变量定义
	HDC hBufferDC=ImageBuffer.GetDC();
	CDC * pBufferDC=CDC::FromHandle(hBufferDC);

	//绘画背景
	pBufferDC->FillSolidRect(&rcClient,RGB(255,255,255));

	//绘画图像
	if (m_ImageSource.IsNull()==false)
	{
		//加载图片
		CPngImage ImageEditGray;
		ImageEditGray.LoadImage(GetModuleHandle(AVATAR_CONTROL_DLL_NAME),TEXT("FACE_EDIT_GRAY"));

		//设置环境
		pBufferDC->SetStretchBltMode(HALFTONE);

		//绘画图片
		m_ImageSource.StretchBlt(hBufferDC,(rcClient.Width()-m_SizeTarget.cx)/2,(rcClient.Height()-m_SizeTarget.cy)/2,
			m_SizeTarget.cx,m_SizeTarget.cy,0,0,m_SizeSource.cx,m_SizeSource.cy);

		//绘画蒙图
		ImageEditGray.DrawImage(pBufferDC,(rcClient.Width()-m_SizeTarget.cx)/2,(rcClient.Height()-m_SizeTarget.cy)/2,
			m_SizeTarget.cx,m_SizeTarget.cy,0,0,ImageEditGray.GetWidth(),ImageEditGray.GetHeight());

		//绘画图片
		m_ImageSource.StretchBlt(hBufferDC,m_rcImageSelect.left,m_rcImageSelect.top,m_rcImageSelect.Width(),m_rcImageSelect.Height(),
			m_SizeSource.cx*(m_rcImageSelect.left-(rcClient.Width()-m_SizeTarget.cx)/2)/m_SizeTarget.cx,
			m_SizeSource.cy*(m_rcImageSelect.top-(rcClient.Height()-m_SizeTarget.cy)/2)/m_SizeTarget.cy,
			m_SizeSource.cx*m_rcImageSelect.Width()/m_SizeTarget.cx,m_SizeSource.cy*m_rcImageSelect.Height()/m_SizeTarget.cy);

		//绘画框架
		DrawLineFrame(pBufferDC);
	}

	//绘画界面
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pBufferDC,0,0,SRCCOPY);

	//清理资源
	ImageBuffer.ReleaseDC();

	return TRUE;
}