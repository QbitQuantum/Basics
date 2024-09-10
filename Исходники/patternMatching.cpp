//FUNCTIONS
static void cameraPoseFromHomography(vector<Point2f> corner, Mat& H, float& ext_camera_height, float& ext_pitch_angle,
		Mat image, Mat &K, const Mat &VP1, const Mat &VP2, Mat & VVP, Mat &P, Mat &camerCenter) {

	Mat NEW_K = K;
	vector<Point3f> po;

	float z = 0.;
	const float unit = HOUSE_SIZE;
	for (int i = -4; i < 5; i++) // si prende il sistema di riferimento al centro della scacchiera. In alternativa i = 0 e <9, j=0 e j<9
		for (int j = -4; j < 5; j++)
			po.push_back(Point3f((float) (j * unit), (float) (i * unit), (float) (z * unit)));

	//  MIGLIORA LA CALIBRAZIONE
	Mat distCoeffs;
	vector<Mat> rvecsCalib, tvecsCalib;
	vector<vector<Point3f> > obj;
	obj.push_back(po);
	vector<vector<Point2f> > img;
	img.push_back(corner);
	calibrateCamera(obj, img, image.size(), NEW_K, distCoeffs, rvecsCalib, tvecsCalib,
			CV_CALIB_USE_INTRINSIC_GUESS | CV_CALIB_ZERO_TANGENT_DIST | CV_CALIB_FIX_K1 | CV_CALIB_FIX_K2
					| CV_CALIB_FIX_K3 | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5 | CV_CALIB_FIX_K6);

	// BEGIN::: RICALCOLO IL VVP
	Mat w_star = NEW_K * NEW_K.t(); // DIAC
//	cout << NEW_K << w_star;
	w_star = normalize3matrix(w_star);

	Mat w = w_star.inv(); // IAC
	w = normalize3matrixf(w);
//	cout << w_star << w;

	Mat vl = VP1.cross(VP2); // line at infinity
	Mat vl_norm = normalizeLine(vl);
//	cout << vl << vl_norm;
	Mat NEW_VVP = w_star * vl_norm; // vertical vanishing point
	NEW_VVP = normalizeVectf(NEW_VVP);
	// END:::

	Mat rvec, tvec, distcoeff;
	solvePnPRansac(po, corner, NEW_K, distcoeff, rvec, tvec, false, 100, 8.0, 32, noArray(), CV_ITERATIVE);

	/*In the derivation of the camera model and its parametrization (6.10) it is assumed that
	 * the coordinate systems used in both the image and the 3D world are right handed systems,
	 * as shown in figure 6.1(pl54). However, a common practice in measuring image coordinates is
	 * that the y-coordinate increases in the downwards direction, thus defining a left handed
	 * coordinate system, contrary to figure 6.1 (pi54). A recommended practice in this case is to
	 * negate the y-coordinate of the image point so that the coordinate system again becomes right
	 * handed. However, if the image coordinate system is left handed, then the consequences are not grave.
	 * The relationship between world and image coordinates is still expressed by a 3 x 4
	 * camera matrix. Decomposition of this camera matrix according to (6.11) with K of the
	 * form (6.10) is still possible with ax and ay positive. The difference is that R now
	 * represents the orientation of the camera with respect to the negative z-axis. In addition,
	 *  the depth of points given by (6.15) will be negative instead of positive for points in
	 *  front of the camera. If this is borne in mind then it is permissible to use left handed
	 *  coordinates in the image.*/

	cv::Mat R;
	cv::Rodrigues(rvec, R); // R is 3x3
	Mat R_orig = R.clone();
	Mat t_orig = tvec.clone();
	R = R.t();  // rotation of inverse
	tvec = -R * tvec; // translation of inverse CENTRO CAMERA!

	cv::Mat T(4, 4, R.type()); // T is 4x4
	T(cv::Range(0, 3), cv::Range(0, 3)) = R * 1; // copies R into T
	T(cv::Range(0, 3), cv::Range(3, 4)) = tvec * 1; // copies tvec into T
	// fill the last row of T (NOTE: depending on your types, use float or double)
	double *p = T.ptr<double>(3);
	p[0] = p[1] = p[2] = 0;
	p[3] = 1;

	Mat trans = tvec;
	ext_camera_height = norm(trans.row(2) * HOUSE_SIZE / unit);

	/* P */

	// primo modo : calcolo esplicito dei parametri estrinseci
	P = Mat(3, 4, R.type()); // P is 3x4
	Mat KR = NEW_K * R_orig;
	Mat Kt = NEW_K * t_orig;

	P(cv::Range(0, 3), cv::Range(0, 3)) = KR * 1;
	P(cv::Range(0, 3), cv::Range(3, 4)) = Kt * 1;

	for (int pi = 0; pi < 3; pi++)
		for (int pj = 0; pj < 4; pj++)
			P.at<double>(pi, pj) = P.at<double>(pi, pj) / P.at<double>(2, 3);

	for (unsigned int i = 0; i < po.size(); i++) { // si prende il sistema di riferimento al centro della scacchiera. In alternativa i = 0 e <9, j=0 e j<9
		Mat X_i = (Mat_<double>(4, 1) << (float) po[i].x, (float) po[i].y, (float) po[i].z, 1.);
		Mat x_i = P * X_i;
		x_i = normalizeVect(x_i);

		circle(image, Point2f(x_i.at<double>(0, 0), x_i.at<double>(0, 1)), 1, Scalar(0, 0, 255), 2);
	}

	// secondo modo _ projectPoints
	vector<Point2f> imageX;
	Mat rvec_t;
	Rodrigues(R.t(), rvec_t);
	projectPoints(po, rvec_t, t_orig, NEW_K, distcoeff, imageX);
	float sum_error = 0;

	int min_error_index;
	double min_error = 9999999.;
	double central_vertex_error; // errore nel vertice centrale della scacchiera (i=40)
	for (unsigned int i = 0; i < imageX.size(); i++) {
		circle(image, imageX[i], 1, Scalar(255, 0, 0), 2);
		double error2 = pow(imageX[i].x - corner[i].x, 2) + pow(imageX[i].y - corner[i].y, 2);
		if (min_error > sqrt(error2)) {
			min_error = sqrtf(error2);
			min_error_index = i;
		}

		if (i == 40)
			central_vertex_error = error2;
		sum_error += (error2);
	}
	if (min_error == central_vertex_error)
		min_error_index = 40; // se l'errore minimo si ha anche nella casa centrale, si preferisce metterlo l� il frame

	cout << "Final error :" << sqrt(sum_error / imageX.size()) << " Min error :" << min_error << " @ point "
			<< min_error_index << " : " << po[min_error_index] << endl;

	//Mat M = K * R.t(); // P = M ! p4 // o R?
	Mat C_homo(4, 1, tvec.type()); // centro camera in coordinate world omogenee
	C_homo(cv::Range(0, 3), cv::Range(0, 1)) = tvec * 1;
	C_homo(cv::Range(3, 4), cv::Range(0, 1)) = 1. * 1;

	Mat plane = (Mat_<double>(4, 1) << 0, 0, 1., 0); // piano scacchiera Z=0

	Mat pp = (Mat_<double>(3, 1) << NEW_K.at<double>(0, 2), NEW_K.at<double>(1, 2), 1.);
	Mat P_cross = P.t() * ((P * P.t()).inv());
	pp.convertTo(pp, CV_64F);
	P_cross.convertTo(P_cross, CV_64F);
	Mat X_pp = P_cross * pp;
	X_pp = normalizeVect(X_pp, 3); // un punto 3D-h**o sulla retta tra punto principale (pp) e centro camera (C_homo)

	Mat Plucker_line_XppC = X_pp * C_homo.t() - C_homo * X_pp.t(); // linea pp C in coordinate Plucker (P3)

	Mat X_pp_on_chessboard = Plucker_line_XppC * plane; // pto intersezione piano scacchiera con linea
	X_pp_on_chessboard = normalizeVect(X_pp_on_chessboard, 3);

	//Point3f X_pp_on_chessboard_EU = Point3f(X_pp_on_chessboard.at<double>(0,0),X_pp_on_chessboard.at<double>(0,1),X_pp_on_chessboard.at<double>(0,2));
	double dist_C_X_pp_chess = norm(X_pp_on_chessboard - C_homo);
	double dist_C_X_pp_chess_CM = dist_C_X_pp_chess * HOUSE_SIZE / unit;
	ext_pitch_angle = acos(ext_camera_height / dist_C_X_pp_chess_CM) - M_PI / 2;
//	cout << endl << dist_C_X_pp_chess_CM << endl;

	//assign outputs
	camerCenter = Mat(C_homo);
	K = NEW_K;
	VVP = NEW_VVP;
}