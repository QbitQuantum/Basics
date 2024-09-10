//处理图片
bool CRichEditMessage::LoadRichEditImage(HINSTANCE hInstance, UINT uResourceID, CDataObject&ImageDataObject)
{
	//加载图片
	CBitImage ImageFile;
	ImageFile.LoadFromResource(hInstance,uResourceID);

	//失败判断
	if (ImageFile.IsNull()==true)
	{
		ASSERT(FALSE);
		return false;
	}

	//创建表情
	CImage ImageRichEdit;
	ImageRichEdit.Create(ImageFile.GetWidth(),ImageFile.GetHeight(),32);

	//绘画表情
	CDC * pDC=CDC::FromHandle(ImageRichEdit.GetDC());
	pDC->FillSolidRect(0,0,ImageFile.GetWidth(),ImageFile.GetHeight(),m_crFillColor);
	ImageFile.TransDrawImage(pDC,0,0,RGB(255,0,255));

	//设置图片
	ImageRichEdit.ReleaseDC();
	ImageDataObject.SetImage(ImageRichEdit.Detach());

	return true;
}