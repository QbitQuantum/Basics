JNIEXPORT void JNICALL Java_com_example_qr_MainActivity_nativeDetect(
		JNIEnv * jenv, jclass, jlong imageGray) {
	LOGD(
			"Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect enter");
	try {
		vector<Rect> RectFaces;
		//       ((DetectionBasedTracker*)thiz)->process(*((Mat*)imageGray));
		//       ((DetectionBasedTracker*)thiz)->getObjects(RectFaces);
		//       vector_Rect_to_Mat(RectFaces, *((Mat*)faces));

		Mat img = *((Mat*) imageGray);
		Mat imgout;
		cvtColor(img, imgout, CV_GRAY2RGB);
		int width = img.cols;
		int height = img.rows;
		uchar *raw = (uchar *) img.data;
//		uchar *raw = (uchar *) imageGray;
		// wrap image data
		Image image(width, height, "Y800", raw, width * height);
		// scan the image for barcodes
		ImageScanner scanner;
		scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

		int n = scanner.scan(image);
		// extract results
		for (Image::SymbolIterator symbol = image.symbol_begin();
				symbol != image.symbol_end(); ++symbol) {
			vector<Point> vp;
			// do something useful with results
			cout << "decoded " << symbol->get_type_name() << " symbol \""
					<< symbol->get_data() << '"' << " " << endl;
			int n = symbol->get_location_size();
			for (int i = 0; i < n; i++) {
				vp.push_back(
						Point(symbol->get_location_x(i),
								symbol->get_location_y(i)));

			}
			RotatedRect r = minAreaRect(vp);
			Point2f pts[4];
			r.points(pts);
			for (int i = 0; i < 4; i++) {
				line(imgout, pts[i], pts[(i + 1) % 4], Scalar(255, 0, 0), 3);
			}
			cout << "Angle: " << r.angle << endl;
		}
		imshow("imgout.jpg", imgout);
		// clean up
		image.set_data(NULL, 0);
		waitKey();

	} catch (cv::Exception& e) {
		LOGD("nativeCreateObject caught cv::Exception: %s", e.what());
		jclass je = jenv->FindClass("org/opencv/core/CvException");
		if (!je)
			je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je, e.what());
	} catch (...) {
		LOGD("nativeDetect caught unknown exception");
		jclass je = jenv->FindClass("java/lang/Exception");
		jenv->ThrowNew(je,
				"Unknown exception in JNI code DetectionBasedTracker.nativeDetect()");
	}
	LOGD(
			"Java_org_opencv_samples_facedetect_DetectionBasedTracker_nativeDetect exit");
}