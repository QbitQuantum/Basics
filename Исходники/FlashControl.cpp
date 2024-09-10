//绘画函数
VOID CFlashActiveX::DrawControl(HDC hdcDraw, LPCRECT rcDraw, BOOL bErase)
{
	//效验状态
	if (m_hWnd==NULL) return;
	if (m_lTotalFrames==0L) return;
	if (m_pIFalshControl==NULL) return;

	//获取位置
	CRect rcRect;
	GetClientRect(m_hWnd,&rcRect);

	//绘画判断 
	if (rcRect.Width()==0) return;
	if (rcRect.Height()==0) return;

	//接口变量
	IOleObject * pIOleObject=m_pIOleObject;
	IViewObject * pIViewObject=(m_pIViewObjectEx!=NULL)?m_pIViewObjectEx:m_pIViewObject;

	//绘画对象
	if ((pIOleObject!=NULL)&&(pIViewObject!=NULL))
	{
		//创建缓冲
		CImage ImageBuffer;
		ImageBuffer.Create(rcRect.Width(),rcRect.Height(),32);	

		//绘画对象
		CImageDC ImageDC(ImageBuffer);
		OleDraw(pIViewObject,DVASPECT_TRANSPARENT,ImageDC,&rcRect);
		
		//变量定义
		BLENDFUNCTION BlendFunction;
		ZeroMemory(&BlendFunction,sizeof(BlendFunction));

		//设置变量
		BlendFunction.BlendOp=AC_SRC_OVER;
		BlendFunction.AlphaFormat=AC_SRC_ALPHA;
		BlendFunction.SourceConstantAlpha=0xFF;

		//帧数统计
		LONG lCurFrame = m_pIFalshControl->CurrentFrame();
		if(m_lLastFrames != lCurFrame)
		{
			m_lLastFrames = lCurFrame;
			m_lLastFrameCount = 0L;
		}
		else m_lLastFrameCount++;

		//完成判断
		if ((lCurFrame+1L)>=m_lTotalFrames || m_lLastFrameCount>=20)
		{
			//停止播放
			m_pIFalshControl->StopPlay();

			//设置变量
			BlendFunction.SourceConstantAlpha=0x00;

			//事件通知
			if (m_pIFlashControlSink!=NULL)
			{
				m_pIFlashControlSink->OnEventFlashFinish();
			}
		}

		//变量定义
		CPoint ImagePoint(0,0);
		CSize SizeImage(ImageBuffer.GetWidth(),ImageBuffer.GetHeight());		

		//设置窗口
		UpdateLayeredWindow(m_hWnd,NULL,NULL,&SizeImage,ImageDC,&ImagePoint,RGB(0,0,0),&BlendFunction,ULW_ALPHA);
	}

	return;
}