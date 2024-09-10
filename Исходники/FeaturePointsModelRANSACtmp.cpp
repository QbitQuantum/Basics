pair<Mat, Mat> FeaturePointsRANSAC::calculateProjection(vector<pair<string, Point2f> > ffpsAtOrigin, vector<pair<string, Point3f> > mmPointsAtOrigin)
{
	// Construct V
	Mat V(mmPointsAtOrigin.size(), 3, CV_32F);	// As many rows as Ffp's, and 3 cols (x, y, z)
	for (unsigned int i=0; i<mmPointsAtOrigin.size(); ++i) {
		V.at<float>(i, 0) = mmPointsAtOrigin[i].second.x;
		V.at<float>(i, 1) = mmPointsAtOrigin[i].second.y;
		V.at<float>(i, 2) = mmPointsAtOrigin[i].second.z;
	}
	// Construct wx, wy
	Mat wx(mmPointsAtOrigin.size(), 1, CV_32F);
	Mat wy(mmPointsAtOrigin.size(), 1, CV_32F);
	for (unsigned int i=0; i<mmPointsAtOrigin.size(); ++i) {
		wx.at<float>(i, 0) = ffpsAtOrigin[i].second.x;
		wy.at<float>(i, 0) = ffpsAtOrigin[i].second.y;
	}

	// TODO: check if matrix square. If not, use another invert(...) instead of .inv().
	bool useSVD = true;
	if(V.rows==V.cols)
		useSVD = false;

	cout <<  "wx = " << wx << endl;
	cout <<  "wy = " << wy << endl;
	cout <<  "V = " << V << endl;

	Mat s;
	Mat t;

	if(!useSVD) {
		cout << "det(V) = " << determinant(V) << endl;	// Det() of non-symmetric matrix?
		cout <<  "V.inv() = " << V.inv() << endl;
		s = V.inv() * wx;
		t = V.inv() * wy;
	} else {
		Mat Vinv;
		invert(V, Vinv, cv::DECOMP_SVD);
		cout <<  "invert(V) with SVD = " << Vinv << endl;
		s = Vinv * wx;
		t = Vinv * wy;
	}

	cout <<  "s = " << s << endl;
	cout <<  "t = " << t << endl;

	for(unsigned int i=0; i<V.rows; ++i) {
		cout <<  "<v|s> = wx? " << V.row(i).t().dot(s) << " ?= " << wx.row(i) << endl;
		cout <<  "<v|t> = wy? " << V.row(i).t().dot(t) << " ?= " << wy.row(i) << endl;
	}

	return make_pair(s, t);
}