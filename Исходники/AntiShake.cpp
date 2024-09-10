/* It is a function that call getHoography multiple times and measure its accuracy.
 * If it runs the function more than the maxLoop value or if the accuracy measure
 * starts to increase, the loop stops*/
cv::Mat AntiShake::calcHomographyFeedbackController(Mat &img_1, Mat &img_2, int loops,
		double final_pic_size, int featurePoints, int coreSize, double absoluteRelation,
		int matches_type) {
	// STEP 0: RE-ESCALE, SO THE BIGGEST RESOLUTION IS 590x(something <= 590)
	Mat workImage1, workImage2;
	double scale = 1.0 / (MAX(img_1.rows,img_1.cols) / final_pic_size);
	if (final_pic_size == 0) {
		scale = 1.0;
	}
	workImage1.create(scale * img_1.rows, scale * img_1.cols, img_1.type());
	workImage2.create(scale * img_2.rows, scale * img_2.cols, img_2.type());
	cv::resize(img_1, workImage1, workImage1.size(), 0, 0, INTER_CUBIC);
	cv::resize(img_2, workImage2, workImage2.size(), 0, 0, INTER_CUBIC);
	cout << "=== STEP 0 complete: RE-ESCALE" << endl;

	// LETS NOW START TO ITERATE IN ORTHER TO get a Homography matrix and refine it
	Mat homography;
	vector<cv::Mat> Hs, eigenvalues;
	vector<double> dets;
	int loopCounter = 0;
	do {
		loopCounter++;
		try {
			//pixels:
			homography = antiShake(workImage1, workImage2, matches_type, featurePoints, coreSize,
					absoluteRelation); // exceptions could appear here... //STEPS 1 to 8 there.
			double det = determinant(homography);
			Mat eigen;
			cv::eigen(homography, eigen);
			cout << endl << "==== STEP 9: HOMOGRAPHY: " << endl << homography << endl << "determinant: "
					<< det << endl << "eigenvalues: " << eigen << endl << endl;

			// *** Checks if the determinant is small enough. If not, the transformation could be awful.
			if (det != 1) {
				Hs.push_back(homography);
				eigenvalues.push_back(eigen);
				dets.push_back(abs(det - 1));

				applyHomography(homography, workImage1, workImage2);

				//Checks if the error has decreased in the last iteration:
				int size = dets.size();
				if (size > 2) {
					if (dets[size - 1] > dets[size - 2]) {
						/*
						 * Explaining the above if comparision:
						 * 		- dets[size - 1] is the nth (last) calculated determinant
						 * 		- dets[size - 2] is the (n-1)th (penultimate) calculated determinant*
						 * 		- The biggest is the difference between the two pictures, the highest
						 * 		will be the det value. Thing is: once the algorithm is well applicated,
						 * 		if applyied again in the now fixed pictures, should generate a matrix similar
						 * 		to the Identity I (at least more similar to I than the first matrix).
						 * 		- dets receive the value ov abd(det -  1). It is used as the measuring parameter.
						 * 		If the value of the det(n) increases from one run to the next,
						 * 		means the algorithm may not be being well used (for any picture noise or miscalibration)
						 */
						cout << "==== POP BACK" << endl;
						//Remove last element of the vectors
						Hs.pop_back();
						eigenvalues.pop_back();
						dets.pop_back();
						break;
					}
				}
			} else {
				// if abs(det-1) is too high, give him some munchies along with the identity matrix:
				break;
			}
		} catch (Exception &e) {
			cout
					<< "ATTENTION ON THE ANTISHAKE.CPP CLASS: exception found in the function getHomographyFeedbackController. ERROR: "
					<< e.err << endl;
			homography = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
			cout << "IDENTITY 1" << endl;
		}
	} while (loopCounter < loops || homography.empty());

	// CALCULATES RESULTANT HOMOGRAPHY:
	Mat resultantH = (Mat_<double>(3, 3) << 1, 0, 0, 0, 1, 0, 0, 0, 1);
	for (unsigned int position = 0; position < Hs.size(); ++position) {
		resultantH = (Hs[position]) * resultantH;
	}
	if (abs(determinant(resultantH) - 1.0) < maxDetDiff) {
		return resultantH;
	} else {
		return Hs[0];
	}
}