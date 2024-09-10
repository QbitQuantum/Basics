void CAddCamDlg::OnBnClickedAddSetmskBt()
{
	// TODO: 在此添加控件通知处理程序代码
	mRangeIndex = 0;
	char filepath[256];
	Mat mMat;
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|BMP Files (*.bmp)|*.bmp|"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{

		FilePathName = dlg.GetPathName(); //文件名保存在了FilePathName里
		CCommonFunc::UnicodeToAnsi(FilePathName.GetBuffer(), filepath, 256);
		mMat = imread(filepath);
		if(mMat.empty()) return;
		cv::Size mSize = cv::Size(mImgRect.Width(), mImgRect.Height());
		Mat image2 = Mat(mSize, CV_32S);
		resize(mMat, image2, mSize);
		CvImage::Mat2CImage(image2, mimg);
		if (mimg.IsNull())
		{
			CButton* pBt = (CButton*)GetDlgItem(IDC_ADD_REDRAW_BT);
			pBt->EnableWindow(FALSE);
			pBt = (CButton*)GetDlgItem(IDC_ADD_ADDRANGE_BT);
			pBt->EnableWindow(FALSE);
			isDrawImg = false;
			return;
		}
		int nBPP = mMat.channels()*8;
		if (!maskimg.IsNull()) maskimg.Destroy();
		maskimg.Create(mMat.cols, mMat.rows,nBPP );
		CButton* pBt = (CButton*)GetDlgItem(IDC_ADD_REDRAW_BT);
		pBt->EnableWindow(TRUE);
		pBt = (CButton*)GetDlgItem(IDC_ADD_ADDRANGE_BT);
		pBt->EnableWindow(TRUE);
		mRangeIndex = 0;
		for (int i = 0; i < MAX_RANGE_NUM; i++)
		{
			mWarnRange[i].clear();
		}
	}
	else
	{
		return;
	}
	DrawImg();
	isDrawImg = true;
}