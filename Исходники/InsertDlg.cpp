void CInsertDlg::drawpic()
{
	CRect rectPic;
	m_pic.GetClientRect(&rectPic);   //m_picture为Picture Control控件变量，获得控件的区域对象
	CDC* pDC = m_pic.GetWindowDC();    //获得显示控件的DC

	CImage *pImage = new CImage();		//装载图像的类

	int n = all;
	if (cur< n){						//还有图片可以显示
		HRESULT ret;
		CString path = CString(setting.libpath.c_str())
			+ CString("\\") + CString(album.record(fileno[cur]).filename().c_str());
		ret = pImage->Load(path);//从磁盘装载图片,根据页面计算得到的图片下标
		if (FAILED(ret)){
			MessageBox(path + _T("不存在!"));
			return;
		}

		int width = rectPic.Width();	//显示区域的宽和高
		int height = rectPic.Height();

		int picW = pImage->GetWidth();	//图片的宽和高
		int picH = pImage->GetHeight();

		//计算缩放比
		double r1 = double(picW) / double(width);
		double r2 = double(picH) / double(height);

		//r为最优缩放比例
		double r = (r1 >= r2 ? r1 : r2);

		int w = picW / r;
		int h = picH / r;
		int sw = (width - w) / 2;
		int sh = (height - h) / 2;
		//防止缩放后失真
		SetStretchBltMode(pDC->m_hDC, HALFTONE);
		//SetBrushOrgEx(pDC->m_hDC, 0, 0, NULL);
		pImage->StretchBlt(pDC->m_hDC, sw, sh, w, h);

		//显示图片
		pImage->Draw(pDC->m_hDC, sw, sh, w, h);

		ReleaseDC(pDC);
		delete pImage;
	}
	else{
		m_pic.ShowWindow(SW_HIDE);
	}
}