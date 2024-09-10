void MyTestDialog::DrawPicToHDC(IplImage* img, UINT ID)
{
	//清空
	CStatic* pStatic = (CStatic*)GetDlgItem(ID);
	//pStatic->SetBitmap(NULL);
	CDC* pDC = GetDlgItem(ID)->GetDC();
	CRect rect;
	pStatic->GetClientRect(&rect);
	//pStatic->GetDC()->FillSolidRect(rect.left ,rect.top ,rect.Width(),rect.Height(), RGB(240, 240, 240));
	////
	HDC hDc = pDC->GetSafeHdc();
	//CRect rect;
	//GetDlgItem(ID)->GetClientRect(&rect);
	float widthRatio = (float)rect.Width() / img->width;
	float heightRatio = (float)rect.Height() / img->height;
	float resRatio = widthRatio < heightRatio ? widthRatio: heightRatio;
	int resWidth = img->width * resRatio;
	int resHeight = img->height * resRatio;
	IplImage* img2=cvCreateImage(cvSize(resWidth, resHeight),img->depth, img->nChannels);
	cvResize(img, img2, CV_INTER_NN);

	img = img2;
	CvvImage cimg;
	cimg.CopyOf(img);
	CRect drawRect;
	drawRect.SetRect(rect.TopLeft().x, rect.TopLeft().y, rect.TopLeft().x + img->width - 1, rect.TopLeft().y + img->height - 1);
	cimg.DrawToHDC(hDc, &drawRect);
	ReleaseDC(pDC);
	//cv::imshow("view", img);
	//path1
	//cvShowImage("view",img);

	//path2
//	著作权归作者所有。
//		商业转载请联系作者获得授权，非商业转载请注明出处。
//		作者：匿名用户
//链接：http://www.zhihu.com/question/29611790/answer/45053299
//	来源：知乎

	//cv::Mat img2;
	//cv::Mat img1(img);
	//
	//CRect rect;
	//GetDlgItem(ID)->GetClientRect(&rect);
	//cv::Rect dst(rect.left,rect.top,rect.right,rect.bottom);
	//cv::resize(img1,img2,cv::Size(rect.Width(),rect.Height()));
	//imshow("view",img2);
	//unsigned int m_buffer[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256];	
	//BITMAPINFO* m_bmi = (BITMAPINFO*) m_buffer;
	//BITMAPINFOHEADER* m_bmih = &(m_bmi->bmiHeader);
	//memset(m_bmih, 0, sizeof(*m_bmih));
	//m_bmih->biSize = sizeof(BITMAPINFOHEADER);
	//m_bmih->biWidth = img2.cols;
	//m_bmih->biHeight = -img2.rows;           // 在自下而上的位图中 高度为负
	//m_bmih->biPlanes = 1;
	//m_bmih->biCompression = BI_RGB;
	//m_bmih->biBitCount = 8 * img2.channels();

	//CDC *pDC = GetDlgItem(ID)->GetDC();	
	//::StretchDIBits(
	//	pDC->GetSafeHdc(),
	//	0, 0, rect.Width(), rect.Height(),
	//	0, 0, rect.Width(), rect.Height(),
	//	img2.data,
	//	(BITMAPINFO*) m_bmi,
	//	DIB_RGB_COLORS,
	//	SRCCOPY
	//	);
	//ReleaseDC(pDC);

}