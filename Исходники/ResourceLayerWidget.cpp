void CResourceLayerWidget::Create(CWnd *pParentWnd, UINT nLoadDiffuseSpecular, UINT nLoadNormalHeight)
{
	CRect rectDummy;
	rectDummy.SetRectEmpty();

	mDiffuseSpecular.Create("", WS_VISIBLE|WS_CHILD|SS_BITMAP, rectDummy, pParentWnd);
	HBITMAP WhiteBmp = MiscUtils::loadBitmap(NULL, 64);
	mDiffuseSpecular.SetBitmap(WhiteBmp);
	mLoadDiffuseSpecular.Create("Load", WS_CHILD|WS_VISIBLE, rectDummy, pParentWnd, nLoadDiffuseSpecular);
	mNormalHeight.Create("", WS_VISIBLE|WS_CHILD|SS_BITMAP, rectDummy, pParentWnd);
	mNormalHeight.SetBitmap(WhiteBmp);
	mLoadNormalHeight.Create("Load", WS_CHILD|WS_VISIBLE, rectDummy, pParentWnd, nLoadNormalHeight);
	// ::DeleteObject(WhiteBmp); // 否则将看不见Bmp
}