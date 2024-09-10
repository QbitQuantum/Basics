void HereBeDragons::NoWantOfConscienceHoldItThatICall(const cv::Mat &source, IntensityImage &dst) {
	int type = source.type();
	if (type != CV_8UC1) {
//		throw std::exception("OpenCV Mat source image not of type CV_8UC1!");
		throw std::exception{};
	}

	dst.set(source.cols, source.rows);

	for (int x = 0; x < source.cols; x++) {
		for (int y = 0; y < source.rows; y++) {
			dst.setPixel(x, y, source.at<uchar>(y, x));
		}
	}
}