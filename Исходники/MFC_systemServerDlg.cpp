void CMFC_systemServerDlg::Thread_getImage(LPVOID lParam)
{
	CMythreadParam * Thread_Info = (CMythreadParam *)lParam;
	CMFC_systemServerDlg * hWnd = (CMFC_systemServerDlg *)CWnd::FromHandle((HWND)Thread_Info->hWnd);
	
	Kinect2Capture kinect;
	kinect.Open(1, 1, 0);

	kinect.uDepthMax = 2000;
	IplImage* img_get = nullptr;
	while (1)
	{
		img_get = kinect.DepthImage();
		if (img_get != NULL)
		{
			cv::Mat src_img = img_get;
			// 設定變換[之前]與[之後]的坐標 (左上,左下,右下,右上)
			cv::Point2f pts1[4] = { roi.pts_depth[0], roi.pts_depth[1], roi.pts_depth[2], roi.pts_depth[3] };
			cv::Point2f pts2[4] = { roi.pts_to[0], roi.pts_to[1], roi.pts_to[2], roi.pts_to[3] };
			// 透視變換行列計算
			cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);
			cv::Mat dst_img;
			// 變換
			cv::warpPerspective(src_img, dst_img, perspective_matrix, cvSize(320, 240), cv::INTER_LINEAR);
			
			cvCopy(&(IplImage)dst_img, m_TabPage1.sImage_depth);
			//*****影像相減*****
			cvAbsDiff(m_TabPage1.sImage_depth, m_TabPage1.sImage_depthGround, m_TabPage1.sImage_depth);
			cvThreshold(m_TabPage1.sImage_depth, m_TabPage1.sImage_depth, 1, 255, CV_THRESH_BINARY);
			//*******************
			//*****erode & dilate*****
			IplConvKernel *pKernel = NULL;
			pKernel = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_RECT, NULL);
			cvErode(m_TabPage1.sImage_depth, m_TabPage1.sImage_depth, pKernel, 1);
			cvDilate(m_TabPage1.sImage_depth, m_TabPage1.sImage_depth, pKernel, 1);
			//*************************
			hWnd->ShowImage(m_TabPage1.sImage_depth, hWnd->GetDlgItem(IDC_IMAGE_binPickLiveDepth),1);
		}
		cvReleaseImage(&img_get);

		img_get = kinect.RGBAImage();
		if (img_get != NULL)
		{
			cv::Mat src_img = img_get;
			// 設定變換[之前]與[之後]的坐標 (左上,左下,右下,右上)
			cv::Point2f pts1[4] = { roi.pts_color[0], roi.pts_color[1], roi.pts_color[2], roi.pts_color[3] };
			cv::Point2f pts2[4] = { roi.pts_to[0], roi.pts_to[1], roi.pts_to[2], roi.pts_to[3] };
			// 透視變換行列計算
			cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);
			cv::Mat dst_img;
			// 變換
			cv::warpPerspective(src_img, dst_img, perspective_matrix, cvSize(320, 240), cv::INTER_LINEAR);
			
			cvCopy(&(IplImage)dst_img, m_TabPage1.sImage_live);
			 
			IplImage* image_show = cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3);
			cvCvtColor(m_TabPage1.sImage_live, image_show, CV_BGRA2BGR);
			hWnd->ShowImage(image_show, hWnd->GetDlgItem(IDC_IMAGE_binPickLive));
			cvReleaseImage(&image_show);
		}
		cvReleaseImage(&img_get);
	}
}