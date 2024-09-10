/*******************
CImg CImg::operator - (CImg gray)

功能：图像按位减

参数：
	CImg 对象

返回值:
	CImg： 相减后的 CImg 类图像对象
*******************/
CImg CImg::operator - (CImg &gray)
{
	CImg grayRet = *this; //返回图像

	//取得图像的高和宽
	int nHeight = GetHeight();
	int nWidth = GetWidthPixel();

	int i, j;//循环变量
	
	//不能在CImg类对象中直接进行像素相减，因为相减的结果可能小于0
	vector< vector<int> > GrayMat;//相减后暂存图像的灰度点阵
	vector<int> vecRow(nWidth, 0); //GrayMat中的一行（初始化为0）
	for(i=0; i<nHeight; i++)
	{
		GrayMat.push_back(vecRow);
	}

	//最大、最小灰度和值
	int nMax = -255;
	int nMin = 255; 

	//逐行扫描图像
	for(i=0; i<nHeight; i++)
	{
		for(j=0; j<nWidth; j++)
		{
			//按位相加
			GrayMat[i][j] = GetGray(j, i) - gray.GetGray(j, i);
			
			//统计最大、最小值
			if( GrayMat[i][j] > nMax)
				nMax = GrayMat[i][j];
			if( GrayMat[i][j] < nMin)
				nMin = GrayMat[i][j];
		}// j
	}// i
	
	
	//将GrayMat的取值范围重新归一化到[0, 255]
	int nSpan = nMax - nMin;
	
	for(i=0; i<nHeight; i++)
	{
		for(j=0; j<nWidth; j++)
		{
			BYTE bt;
			if(nSpan > 0)
				bt = (GrayMat[i][j] - nMin)*255/nSpan;
			else if(GrayMat[i][j] <= 255)
				bt = GrayMat[i][j] ;
			else
				bt = 255;
				
			grayRet.SetPixel(j, i, RGB(bt, bt, bt));			
			

		}// for j
	}// for i
		
	
	
	return grayRet;
}