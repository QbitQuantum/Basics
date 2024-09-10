//运行函数
bool CFlowerEffectThread::OnEventThreadRun()
{
	//加载图片
	CPngImage ImageFlower;
	CString strInfo=TEXT("GIFT_"),strImage;
	strImage.Format(TEXT("%s%ld"),strInfo,m_wFlowerID/2+1);
	ImageFlower.LoadImage(GetModuleHandle(PROPERTY_MODULE_DLL_NAME),strImage);
	if(ImageFlower.IsNull())return false;

	//窗体大小
	CRect ClientRect;
	::GetWindowRect(m_hFlowerEffectControl, &ClientRect);

	//绘画大小
	int nCartoonWidth = 150;
	int nCartoonCount = ImageFlower.GetWidth() / nCartoonWidth;

	//过虑散频
	MoveWindow(m_hFlowerEffectControl,0,0,0,0,false);
	::ShowWindow(m_hFlowerEffectControl, SW_SHOW);

	//绘画图片
	for ( int nCartoonIndex=0; nCartoonIndex < nCartoonCount; ++nCartoonIndex )
	{		
		//设备句柄
		HDC hDC=GetDC(m_hFlowerEffectControl);
		if ( hDC==NULL ) return false;

		//系上D C
		CDC	TempDC;
		TempDC.Attach(hDC);

		//内存设备
		CDC *pMemoryDC = CDC::FromHandle(m_ImageBuffer.GetDC());
		CDC *pScreenDC = CDC::FromHandle(m_ImageBufferScreen.GetDC());

		//绘画背景
		pMemoryDC->BitBlt(0,0,ClientRect.Width(),ClientRect.Height(),pScreenDC,0,0,SRCCOPY);

		//绘画礼物
		ImageFlower.DrawImage(pMemoryDC, 0, 0, ClientRect.Width(), ClientRect.Height(),
			nCartoonWidth * nCartoonIndex,0,nCartoonWidth, ImageFlower.GetHeight());

		TempDC.BitBlt(0, 0, ClientRect.Width(), ClientRect.Height(), pMemoryDC, 0, 0, SRCCOPY);

		//显示窗体
		if (nCartoonIndex==0) MoveWindow(m_hFlowerEffectControl,ClientRect.left,ClientRect.top,ClientRect.Width(),ClientRect.Height(),false);

		//释放设备
		TempDC.Detach();
		ReleaseDC(m_hFlowerEffectControl, hDC);
		hDC=NULL;
		m_ImageBuffer.ReleaseDC();
		m_ImageBufferScreen.ReleaseDC();
		pMemoryDC=NULL;

		//线程睡眠
		Sleep(120);
	}

	//隐藏窗体
	::ShowWindow(m_hFlowerEffectControl, SW_HIDE);

	return false;
}