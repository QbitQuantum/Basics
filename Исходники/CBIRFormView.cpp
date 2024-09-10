/************************************************************************************
Form视图创建完成后的更新操作
主要包括以下内容：
1. Form视图上控件的创建与初始化；
2. 各个控件大小与分辨率无关化操作；
3. 图像库的扫描与加载（ScanDatabase）
************************************************************************************/
void CCBIRFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 设置当前视图的大小
	SetScrollSizes(MM_TEXT , CSize(10 , 10));

	// 设置当前视图的MFC风格
	DWORD dwStyle = GetWindowLong(mImageDBTree.m_hWnd , GWL_STYLE);
	dwStyle |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;

	SetWindowLong(mImageDBTree.m_hWnd , GWL_STYLE , dwStyle);
	m_allRoot = mImageDBTree.InsertItem("database");
	m_curRoot = m_allRoot;

	// 扫描与应用程序相关的图像库，并加载其中的内容
	ScanDatabase();

	// 预览相关的其它初始化操作：树状控制的初始化、预览图像的初始化与加载等
	mImageDBTree.Expand(m_allRoot , TVE_TOGGLE);

	LoadMyJpegFile("data/image.orig/0.jpg" , &mpImagePPI);

	RECT treeRect;
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_MODELDBTREE);
	pWnd->GetWindowRect(&treeRect);
	pWnd->SetWindowPos(NULL , treeRect.left , treeRect.top , 
		(int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f)) , 
		(int)((float)(treeRect.bottom - treeRect.top) * ((float)mHeight / 738.0f)) , SWP_NOMOVE);

	pWnd = GetDlgItem(IDC_RETRIVEIMAGE);
	pWnd->GetWindowRect(&treeRect);
	pWnd->SetWindowPos(NULL , 5 , 700.0f / 738.0f * (float)mHeight , 
		(int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f)) , 
		(int)((float)(treeRect.bottom - treeRect.top) * ((float)mHeight / 738.0f)) , SWP_NOZORDER);
	int lastWidth = (int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f));

	pWnd = GetDlgItem(IDC_PRRESULT);
	pWnd->GetWindowRect(&treeRect);
	pWnd->SetWindowPos(NULL , 10 + lastWidth , 700.0f / 738.0f * (float)mHeight , 
		(int)((float)(treeRect.right - treeRect.left) * ((float)mWidth / 250.0f)) , 
		(int)((float)(treeRect.bottom - treeRect.top) * ((float)mHeight / 738.0f)) , SWP_NOZORDER);
}