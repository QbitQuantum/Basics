void LinearFilter::ReflectedIndexingConvolution()
{
	//Mat src = original_image_;
	//Mat dst = processed_image_;
	float sum, x1, y1;
	for (int y = 0; y < original_image_.rows; y++){
		for (int x = 0; x < original_image_.cols; x++){
			sum = 0.0;
			for (int k = -radius_ / 2; k <= radius_ / 2; k++){
				for (int j = -radius_ / 2; j <= radius_ / 2; j++){
					x1 = Reflect(original_image_.cols, x - j);
					y1 = Reflect(original_image_.rows, y - k);
					sum = sum + kernel_[j + radius_ / 2][k + radius_ / 2] * original_image_.at<uchar>(y1, x1);
				}
			}
			sum = (sum > 255) ? 255 : sum;
			sum = (sum < 0) ? 0 : sum;
			processed_image_.at<uchar>(y, x) = sum;
		}
	}
}