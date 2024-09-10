void MarkerRecognizer::markerDetect(Mat& img_gray, vector<Marker>& possible_markers, int min_size, int min_side_length)
{
    Mat img_bin = img_gray;
    int thresh_size = (min_size/4)*2+1;
    adaptiveThreshold(img_gray, img_bin, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, thresh_size, thresh_size/3);
//    threshold(img_gray, img_bin, 125, 255, THRESH_BINARY_INV|THRESH_OTSU);
//    morphologyEx(img_bin, img_bin, MORPH_OPEN, Mat());	//use open operator to eliminate small patch

    vector<vector<Point> > all_contours;
    vector<vector<Point> > contours;
    Mat img_contour = img_bin.clone();
    findContours(img_contour, all_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    for (int i = 0; i < all_contours.size(); ++i)
    {
        if (all_contours[i].size() > min_size)
        {
            contours.push_back(all_contours[i]);
        }
    }

    vector<Point> approx_poly;
    for (int i = 0; i < contours.size(); ++i)
    {
        double eps = contours[i].size()*APPROX_POLY_EPS;
        approxPolyDP(contours[i], approx_poly, eps, true);

        if (approx_poly.size() != 4)
            continue;

        if (!isContourConvex(approx_poly))
            continue;

        //Ensure that the distance between consecutive points is large enough
        float min_side = FLT_MAX;
        for (int j = 0; j < 4; ++j)
        {
            Point side = approx_poly[j] - approx_poly[(j+1)%4];
            min_side = min(min_size, side.dot(side));
        }
        if (min_side < min_side_length*min_side_length)
            continue;

        //Sort the points in anti-clockwise
        Marker marker = Marker(0, approx_poly[0], approx_poly[1], approx_poly[2], approx_poly[3]);
        Point2f v1 = marker.m_corners[1] - marker.m_corners[0];
        Point2f v2 = marker.m_corners[2] - marker.m_corners[0];
        if (v1.cross(v2) > 0)
        {
            swap(marker.m_corners[1], marker.m_corners[3]);
        }
        possible_markers.push_back(marker);
    }
}