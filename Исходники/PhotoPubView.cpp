// CPhotoPubView 绘制
void CPhotoPubView::DrawImage(CDC *pDC,IplImage *pImg)
{
	int wid=0,hi=0;

	CRect ClipBox;
	GetClientRect(&ClipBox);
	if (!pImg) {
		CBitmap bkg;
		bkg.LoadBitmap(IDB_BACKGROUND);
		CBrush brush(&bkg);
		pDC->FillRect(&ClipBox,&brush);	
		return;
	}

	wid=int(pImg->width*m_ratio);
	hi=int(pImg->height*m_ratio);

	IplImage *pStub=pImg;
	IplImage *pTmp=NULL;
	if (wid!=pImg->width) {
		pTmp=cvCreateImage(cvSize(wid,hi),IPL_DEPTH_8U,3);
		cvResize(pImg,pTmp);
		pStub=pTmp;
	}
		

	CRgn WindowRgn;
	WindowRgn.CreateRectRgnIndirect(&ClipBox);
	CRect ImageRect(0,0,wid,hi);
	int top=max((ClipBox.Height()-hi)/2,0);
	int left=max((ClipBox.Width()-wid)/2,0);
	ImageRect.MoveToXY(left,top);
	CRgn ImageRgn;
	ImageRgn.CreateRectRgnIndirect(&ImageRect);
	WindowRgn.CombineRgn(&WindowRgn,&ImageRgn,RGN_DIFF);

	CBitmap bkg;
	bkg.LoadBitmap(IDB_BACKGROUND);
	CBrush brush(&bkg);
	pDC->FillRgn(&WindowRgn,&brush);	
	
	memset(m_bmih_buffer, 0, sizeof(*m_bmih_buffer));
    m_bmih_buffer->biSize = sizeof(BITMAPINFOHEADER);
    m_bmih_buffer->biWidth = wid;
    m_bmih_buffer->biHeight = -hi;
    m_bmih_buffer->biPlanes = 1;
    m_bmih_buffer->biBitCount = 24;
    m_bmih_buffer->biCompression = BI_RGB;


	SetDIBitsToDevice(
		pDC->m_hDC, 
		ImageRect.left,ImageRect.top,pStub->width,pStub->height, 
		0, 0, 0, hi, pStub->imageData, m_bmi_buffer, DIB_RGB_COLORS 
	);

	cvReleaseImage(&pTmp);

}