// CbehaviorView 绘图
void CbehaviorView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

	//CMemoryDC *pMemDC = NULL;
	//pDC = pMemDC = new CMemoryDC(pDC);

// 	RECT rect;
// 	GetClientRect(&rect);
// 	int nWidth = rect.right;
// 	int nHeight = rect.bottom;
// 
// 	pMemDC->FillSolidRect(0, 0, nWidth, nHeight, RGB(255, 255, 255));
// 	gdi->StartDrawing(pDC->GetSafeHdc());
	//gdi->TextAtPos(0, 0, "Hello");
	//list<Vehicle*>& vehicleList = GlobalVar::instance().GetGameWorld()->GetAllBots();
	//if (vehicleList.size() > 0)
	//{
	//	int xOffset = 0;
	//	int yOffset = 0;

	//	Vehicle* pFirstVehicle = (*vehicleList.begin());
	//	pFirstVehicle->GetBrain()->RenderText(xOffset, yOffset);
	//}
	//gdi->StopDrawing(pDC->GetSafeHdc());
	//
	//delete pMemDC;

	// 绘制图片
	CBitmap bitmap;  
	CDC dcMemory;  
	int result;  
	bitmap.CreateBitmap(128, 128, 1, 32, m_lpBuf);

	result = bitmap.SetBitmapBits(128 * 128 * 4, m_lpBuf);
	dcMemory.CreateCompatibleDC(pDC);
	CBitmap *pbmpOld = dcMemory.SelectObject(&bitmap);
	//m_pDC->StretchBlt(0,0,目宽,目高,&dcMemory,0,0,源宽,源高,SRCCOPY);  
	pDC->BitBlt(0, 0, 128, 128, &dcMemory, 0, 0, SRCCOPY);  
	pDC->StretchBlt(0, 0, 128 / 2, 128 / 2,&dcMemory, 0, 0, 128, 128, SRCCOPY);  
	dcMemory.SelectObject(pbmpOld);

	return ;
}