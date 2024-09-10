//绘画同意标志
void CUsingSkinClass::DrawArgeeFlag(CDC * pDC, int iXPos, int iYPos)
{
	CGameImageHelper ImageHandle(&m_PicAgree);
	CDC destdc;
	destdc.CreateCompatibleDC(pDC);
	destdc.SelectObject(ImageHandle);
	::TransparentBlt(pDC->GetSafeHdc(),iXPos,iYPos,ImageHandle.GetWidth(),ImageHandle.GetHeight(),destdc.GetSafeHdc(),0,0,ImageHandle.GetWidth(),ImageHandle.GetHeight(),destdc.GetPixel(0,0));
	//AFCStretchImage(pDC,iXPos,iYPos,AGREE_WIDTH,AGREE_HEIGHT,ImageHandle,0,0,AGREE_WIDTH,AGREE_HEIGHT,RGB(0,128,128));
	///{{ Added by zxd 20100709 释放GDI资源
	destdc.DeleteDC();
	/// Added by zxd 20100709 释放GDI资源}}
	return;
}