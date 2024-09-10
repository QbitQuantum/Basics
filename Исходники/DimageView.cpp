CImg* CDimageView::Canny(CImg* pImg)
{
	// 各方向梯度值

	// 使用Prewitt模板计算各个方向上的梯度值
	CImg* imgGH=PrewittEdge(pImg,1);
	CImg* imgGV=PrewittEdge(pImg,2);
	CImg* imgGCW=PrewittEdge(pImg,3);
	CImg* imgGCCW=PrewittEdge(pImg,4);
	CImg* imgGratitude = new CImg(*pImg);
	imgGratitude->InitPixels(0);

	int width=pImg->GetWidthPixel();
	int height=pImg->GetHeight();
	// 最大梯度方向
	BYTE * pbDirection = new BYTE [height * width];

	memset(pbDirection, 0,height * width * sizeof(BYTE));

	// 寻找每点的最大梯度方向并写入对应的最大梯度值

	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			BYTE gray = 0;

			if (imgGH->GetGray(j, i) > gray)
			{
				gray = imgGH->GetGray(j, i);
				pbDirection[i * width + j] = 1;
				imgGratitude->SetPixel(j, i, RGB(gray, gray, gray));
			}

			if (imgGV->GetGray(j, i) > gray)
			{
				gray = imgGV->GetGray(j, i);
				pbDirection[i * width + j] = 2;
				imgGratitude->SetPixel(j, i, RGB(gray, gray, gray));
			}

			if (imgGCW->GetGray(j, i) > gray)
			{
				gray = imgGCW->GetGray(j, i);
				pbDirection[i * width + j] = 3;
				imgGratitude->SetPixel(j, i, RGB(gray, gray, gray));
			}

			if (imgGCCW->GetGray(j, i) > gray)
			{
				gray = imgGCCW->GetGray(j, i);
				pbDirection[i * width + j] = 4;
				imgGratitude->SetPixel(j, i, RGB(gray, gray, gray));
			}
		}
	}

	// 阈值化时重用前面的对象
	CImg *pImgThreL = imgGH, *pImgThreH = imgGV;

	// 检查阈值参数，如未给出阈值则计算以取得最佳阈值
	int bThreH;
	int bThreL;

	bThreH = 1.2 * imgGratitude->DetectThreshold(100);
	bThreL = 0.4 * bThreH;
		

	// 将最大梯度图像按高低值分别进行阈值化
	imgGratitude->Threshold(pImgThreL, bThreL);
	imgGratitude->Threshold(pImgThreH, bThreH);

	// 初始化目标图像
	CImg* mImg = new CImg(*pImg);
	mImg->InitPixels(0);
	
	// 根据低阈值图像在高阈值图像上进行边界修补
	for (int i=1; i<height-1; i++)
	{
		for (int j=1; j<width-1; j++)
		{
			if (pImgThreH->GetGray(j, i))
			{
				// 高阈值图像上发现点直接确定
				mImg->SetPixel(j, i, RGB(255, 255, 255));
				
				// 搜索梯度最大方向上的邻域
				switch ( pbDirection[i * width + j] ) {
					case 1:	// 水平方向
						if (pImgThreL->GetGray(j+1, i))
						{
							pImgThreH->SetPixel(j+1, i, RGB(255, 255, 255));
						}
						if (pImgThreL->GetGray(j-1, i))
						{
							pImgThreH->SetPixel(j-1, i, RGB(255, 255, 255));
						}
						break;

					case 2:	// 垂直方向
						if (pImgThreL->GetGray(j, i+1))
						{
							pImgThreH->SetPixel(j, i+1, RGB(255, 255, 255));
						}
						if (pImgThreL->GetGray(j, i-1))
						{
							pImgThreH->SetPixel(j, i-1, RGB(255, 255, 255));
						}
						break;

					case 3:	// 45度方向
						if (pImgThreL->GetGray(j+1, i-1))
						{
							pImgThreH->SetPixel(j+1, i-1, RGB(255, 255, 255));
						}
						if (pImgThreL->GetGray(j-1, i+1))
						{
							pImgThreH->SetPixel(j-1, i+1, RGB(255, 255, 255));
						}
						break;

					case 4:	// 135度方向
						if (pImgThreL->GetGray(j+1, i+1))
						{
							pImgThreH->SetPixel(j+1, i+1, RGB(255, 255, 255));
						}
						if (pImgThreL->GetGray(j-1, i-1))
						{
							pImgThreH->SetPixel(j-1, i-1, RGB(255, 255, 255));
						}
						break;
				}
			}//if
		}//for j
	}//for i



	delete pbDirection;

	return mImg;
}