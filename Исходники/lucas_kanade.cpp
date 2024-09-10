double* LucasKanade::GradientEstimationAtY() {
	Frame* frame = frames[frames.size() / 2];
	int rows = frame->Rows();
	int cols = frame->Columns();
	double* iy = new double[rows * cols];

	double* ptr = iy;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j, ++ptr) {
			int pix_sum = 0;
			for (int k = kGradientBegin; k <= kGradientEnd; ++k) {
				if (i + k < 0 || rows <= i + k) continue;
				pix_sum += frame->GetPixel(i + k, j) * kGradient[k - kGradientBegin];
			}
			*ptr = static_cast<double>(pix_sum) / 12.0;
		}
	}
	return iy;
}