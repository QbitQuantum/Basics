UINT WINAPI
//DWORD WINAPI
#elif defined(POSIX_SYS)
// using pthread
void *
#endif
	ChessRecognition::HoughLineThread(
#if defined(WINDOWS_SYS)
	LPVOID
#elif defined(POSIX_SYS)
	void *
#endif
	Param) {
	// 실제로 뒤에서 동작하는 windows용 thread함수.
	// 함수 인자로 클래스를 받아옴.
	ChessRecognition *_TChessRecognition = (ChessRecognition *)Param;
	_TChessRecognition->_HoughLineBased = new HoughLineBased();

	CvSeq *_TLineX, *_TLineY;
	double _TH[] = { -1, -7, -15, 0, 15, 7, 1 };

	CvMat _TDoGX = cvMat(1, 7, CV_64FC1, _TH);
	CvMat* _TDoGY = cvCreateMat(7, 1, CV_64FC1);
	cvTranspose(&_TDoGX, _TDoGY); // transpose(&DoGx) -> DoGy

	double _TMinValX, _TMaxValX, _TMinValY, _TMaxValY, _TMinValT, _TMaxValT;
	int _TKernel = 1;

	// Hough 사용되는 Image에 대한 Initialize.
	IplImage *iplTemp = cvCreateImage(cvSize(_TChessRecognition->_Width, _TChessRecognition->_Height), IPL_DEPTH_32F, 1);                   
	IplImage *iplDoGx = cvCreateImage(cvGetSize(iplTemp), IPL_DEPTH_32F, 1);  
	IplImage *iplDoGy = cvCreateImage(cvGetSize(iplTemp), IPL_DEPTH_32F, 1);  
	IplImage *iplDoGyClone = cvCloneImage(iplDoGy);
	IplImage *iplDoGxClone = cvCloneImage(iplDoGx);
	IplImage *iplEdgeX = cvCreateImage(cvGetSize(iplTemp), 8, 1);
	IplImage *iplEdgeY = cvCreateImage(cvGetSize(iplTemp), 8, 1);

	CvMemStorage* _TStorageX = cvCreateMemStorage(0), *_TStorageY = cvCreateMemStorage(0);

	while (_TChessRecognition->_EnableThread != false) {
		// 이미지를 받아옴. main루프와 동기를 맞추기 위해서 critical section 사용.
		_TChessRecognition->_ChessBoardDetectionInternalImageProtectMutex.lock();
		//EnterCriticalSection(&(_TChessRecognition->cs));
		cvConvert(_TChessRecognition->_ChessBoardDetectionInternalImage, iplTemp);
		//LeaveCriticalSection(&_TChessRecognition->cs);
		_TChessRecognition->_ChessBoardDetectionInternalImageProtectMutex.unlock();

		// 각 X축 Y축 라인을 검출해 내기 위해서 filter 적용.
		cvFilter2D(iplTemp, iplDoGx, &_TDoGX); // 라인만 축출해내고.
		cvFilter2D(iplTemp, iplDoGy, _TDoGY);
		cvAbs(iplDoGx, iplDoGx);
		cvAbs(iplDoGy, iplDoGy);

		// 이미지 내부에서 최댓값과 최소값을 구하여 정규화.
		cvMinMaxLoc(iplDoGx, &_TMinValX, &_TMaxValX);
		cvMinMaxLoc(iplDoGy, &_TMinValY, &_TMaxValY);
		cvMinMaxLoc(iplTemp, &_TMinValT, &_TMaxValT);
		cvScale(iplDoGx, iplDoGx, 2.0 / _TMaxValX); // 정규화.
		cvScale(iplDoGy, iplDoGy, 2.0 / _TMaxValY);
		cvScale(iplTemp, iplTemp, 2.0 / _TMaxValT);

		cvCopy(iplDoGy, iplDoGyClone);
		cvCopy(iplDoGx, iplDoGxClone);

		// NMS진행후 추가 작업
		_TChessRecognition->_HoughLineBased->NonMaximumSuppression(iplDoGx, iplDoGyClone, _TKernel);
		_TChessRecognition->_HoughLineBased->NonMaximumSuppression(iplDoGy, iplDoGxClone, _TKernel);

		cvConvert(iplDoGx, iplEdgeY); // IPL_DEPTH_8U로 다시 재변환.
		cvConvert(iplDoGy, iplEdgeX);

		double rho = 1.0; // distance resolution in pixel-related units.
		double theta = 1.0; // angle resolution measured in radians.
		int threshold = 20;

		if (threshold == 0)
			threshold = 1;

		// detecting 해낸 edge에서 hough line 검출.
		_TLineX = cvHoughLines2(iplEdgeX, _TStorageX, CV_HOUGH_STANDARD, 1.0 * rho, CV_PI / 180 * theta, threshold, 0, 0);
		_TLineY = cvHoughLines2(iplEdgeY, _TStorageY, CV_HOUGH_STANDARD, 1.0 * rho, CV_PI / 180 * theta, threshold, 0, 0);

		// cvSeq를 vector로 바꾸기 위한 연산.
		_TChessRecognition->_Vec_ProtectionMutex.lock();
		_TChessRecognition->_HoughLineBased->CastSequence(_TLineX, _TLineY);
		_TChessRecognition->_Vec_ProtectionMutex.unlock();

		Sleep(2);
	}

	// mat 할당 해제.
	cvReleaseMat(&_TDoGY);

	// 내부 연산에 사용된 이미지 할당 해제.
	cvReleaseImage(&iplTemp);
	cvReleaseImage(&iplDoGx);
	cvReleaseImage(&iplDoGy);
	cvReleaseImage(&iplDoGyClone);
	cvReleaseImage(&iplDoGxClone);
	cvReleaseImage(&iplEdgeX);
	cvReleaseImage(&iplEdgeY);

	// houghline2에 사용된 opencv 메모리 할당 해제.
	cvReleaseMemStorage(&_TStorageX);
	cvReleaseMemStorage(&_TStorageY);

	delete _TChessRecognition->_HoughLineBased;
#if defined(WINDOWS_SYS)
	_endthread();
#elif defined(POSIX_SYS)

#endif
	_TChessRecognition->_EndThread = true;
	return 0;
}