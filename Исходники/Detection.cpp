JNIEXPORT jboolean JNICALL Java_pris_videotest_JNIClient_detect(JNIEnv * env,
		jclass, jbyteArray pixels, jint width, jint height) {
	jbyte * cPixels;
	cPixels = env->GetByteArrayElements(pixels, 0);

	cv::Mat imgData(height, width, CV_8UC1, (unsigned char*) cPixels);

	IplImage *frame = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	*frame = imgData.operator _IplImage();
	//imgData.release();

	cvSmooth(frame, frame, CV_GAUSSIAN, 3, 0, 0);     ///<高斯滤波
	cv::Mat m_OriFrameMat = frame;
	//cvReleaseImage(&frame);
	resize(m_OriFrameMat, m_ResizeFrameMat,
			cv::Size(m_nVideoResizeW, m_nVideoResizeH), 0, 0, CV_INTER_LINEAR); ///<压缩 640*480 m_pResizeFrame=30*40
	//m_OriFrameMat.release();
	//cvtColor(m_ResizeFrameMat, m_GrayFrameMat, CV_BGRA2GRAY, 1); ///<灰度化
	//m_ResizeFrameMat.release();
	m_pBGSubMOG2.operator()(m_ResizeFrameMat, foregroundMat, 0.001);
	m_ResizeFrameMat = foregroundMat;

	int i, j, k;
	k = 0;
	for (i = 0; i < m_nVideoResizeH; i++) {
		for (j = 0; j < m_nVideoResizeW; j++) {
			if (m_ResizeFrameMat.data[i * m_nVideoResizeW + j] != 0) {
				k++; ///<计算二值前景图像非0像素点个数
			}
		}
	}
	//m_GrayFrameMat.release();
	//delete frame;
	double k_ratio = (double) k / (double) (m_nVideoResizeW * m_nVideoResizeH);
	if (k_ratio <= 0.01) {
		env->ReleaseByteArrayElements(pixels, cPixels, 0);
		return false;
	}
	if (k_ratio / m_rFGSegThreshold > 1.5 || k_ratio / m_rFGSegThreshold < 0.79)
		m_rFGSegThreshold = k_ratio;

	///检测到运动视频段
	if (k_ratio >= m_rFGSegThreshold) {
		env->ReleaseByteArrayElements(pixels, cPixels, 0);
		return true;
	}
	env->ReleaseByteArrayElements(pixels, cPixels, 0);
	return false;
}