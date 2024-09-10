/*
* Correlación del vector signal usando la máscara mask
*/
void crossCorrelation(Mat &input, Mat &mask) {

	int offset_mask = mask.cols / 2;
	Mat input_copy;
	input.copyTo(input_copy);

	for (int i = offset_mask - 1; i < input.rows - offset_mask - 1; i++) {
		for (int j = offset_mask - 1; j < input.cols - offset_mask - 1; j++) {
			Mat roi = Mat(input_copy, Rect(j - offset_mask + 1, i - offset_mask + 1, mask.cols, mask.rows));
			double dot_product = mask.dot(roi);		//Producto escalar entre la máscara y la sección de la imagen
			input.at<float>(Point(j,i)) = dot_product;
		}
	}

}