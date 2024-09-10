/***************************************************************
*函数名称：	RectSobelBlob
*
* 参数：	IMG						图像
*			TRect2D					感兴趣区域
*			long					窗口面积
*			long					动态阈值
*			long					斑点的最小面积
*			TBlobTouchBorderFilter	忽略边界
*			long					斑点最小宽度
*			long					斑点最小高度
* 返回值：	不存在斑点	true, 
*			存在斑点	false
*  
* 功能：	在指定的区域内采用动态阈值+
*			斑点分析的方法检测是否存在斑点
*
****************************************************************/
bool CapsuleProc::RectSobelBlob	(	IMG						image, 
									const TRect2D<long>&	roi,
									long					wndSize,
									long					dynThres,
									long					minBlobSize,
									TBlobTouchBorderFilter	ignorBorder,
									long					minBlobWidth,
									long					minBlobHeight)
{
	if(!IsImage(image) || roi.IsNull() )
	{	return true;	}

	bool	success = true;
	IMG	imageROI= NULL;
	CreateImageMap(image , roi.x0(), roi.y0(), roi.x1(), roi.y1(), roi.Width(), roi.Height(), imageROI);
	if(IsImage(imageROI))
	{
		IMG imageSobel = 0;
		FilterSobelVertical(imageROI, FM_5x5, imageSobel);
		success = RectBlackBlob(	imageSobel, 
						wndSize, 
						dynThres, 
						minBlobSize, 
						ignorBorder,
						minBlobWidth,
						minBlobHeight);		
		if(success)
		{
			IMG	imageSobel2	= NULL;
			long	maskVal[]	= { 255 };
			XorConstant		(	imageSobel, 
							maskVal, 
							imageSobel2);
			success = RectBlackBlob	(	imageSobel2,
							wndSize,
							dynThres, 
							minBlobSize,
							ignorBorder,
							minBlobWidth,
							minBlobHeight);
			ReleaseImage(imageSobel2);
		}

		//m_sortObserver.ObserverIMG(SortObserver::MSobel, image);
		//m_sortObserver.ObserverIMG(SortObserver::CSobel, imageSobel);
		ReleaseImage(imageSobel);
	}
	ReleaseImage(imageROI);
	return success;	
}