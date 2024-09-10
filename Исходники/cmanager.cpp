void CManager::CreateGUI()
{
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    moveWindow("Control", 700, 0);

    cvCreateTrackbar("LowH", "Control", &m_nLowH, 255); //Hue (0 - 179)//Create trackbars in "Control" window
    cvCreateTrackbar("HighH", "Control", &m_nHighH, 255);

    cvCreateTrackbar("LowS", "Control", &m_nLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &m_nHighS, 255);

    cvCreateTrackbar("LowV", "Control", &m_nLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &m_nHighV, 255);

    cvCreateTrackbar("Analytics", "Control", (int*) &m_bAnalytics, 1);
}