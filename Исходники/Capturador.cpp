bool CCapturador::CapturePatternsUndisorted(Mat& CameraMatrix,Mat& DistMatrix,int time)
{
	m_vCaptures.clear();
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	bool bMakeCapture = false;
	int nPatterns = 0;
	namedWindow("Camera", 1);
	namedWindow("Patrones");
/*
	HWND win_handle = FindWindow(0, L"Patrones");
	if (!win_handle)
	{
		printf("Failed FindWindow\n");
	}

	// Resize
	unsigned int flags = (SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER);
	flags &= ~SWP_NOSIZE;
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int w = m_Options->m_nWidth;
	unsigned int h = m_Options->m_nHeight;
	SetWindowPos(win_handle, HWND_NOTOPMOST, x, y, w, h, flags);

	// Borderless
	SetWindowLong(win_handle, GWL_STYLE, GetWindowLong(win_handle, GWL_EXSTYLE) | WS_EX_TOPMOST);
	ShowWindow(win_handle, SW_SHOW);
	cvMoveWindow("Patrones", 0, 0);
    */
    long A = getTickCount();
    long B = getTickCount();
	bool start = false;
	for (int i = 0;;)
	{
		imshow("Patrones", m_vPatterns[i]);
		Mat frame;
		cap >> frame;
		if (frame.empty())
			return false;
		Mat view, rview, map1, map2;
		initUndistortRectifyMap(CameraMatrix, DistMatrix, Mat(),
			getOptimalNewCameraMatrix(CameraMatrix, DistMatrix, frame.size(), 1, frame.size(), 0),
			frame.size(), CV_16SC2, map1, map2);
		remap(frame, rview, map1, map2, INTER_LINEAR);
		imshow("Camera", rview);
        B = getTickCount();
		int C = B - A;
		if ((C>time&&start) || waitKey(30) >= 0)
		{
			start = true;
			cout << "time = " << C << endl;
            A = getTickCount();
			i++;
			Mat capture = frame.clone();
			Mat gray;
			cv::cvtColor(capture, gray, CV_BGR2GRAY);
			m_vCaptures.push_back(gray);
			if (++nPatterns >= m_nPatterns)
				break;
		};
	}
	cout << "Patrones capturados." << endl;
	cvDestroyWindow("Patrones");
	return true;
}