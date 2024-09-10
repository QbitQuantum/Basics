Mat& CHandGestureRecognitionSystemDlg::FeatureDetect(const Mat& image_input, Mat& image_output)
{
    image_input.copyTo(image_output);
    cvtColor(image_output, image_output, CV_BGR2GRAY);
#ifdef _DEBUG
    TRACE("gray image channels = %d\n", image_output.channels());
#endif
    // morphology
    Mat kernel = Mat(3,3,CV_8UC1, Scalar(255));
    morphologyEx(image_output, image_output, MORPH_OPEN, kernel);
    // floodfill
    int num_floodfill = 0;
    int area_max = 0;
    int value_max = 0;
    for (int i = 0; i < image_output.rows; i++) {
        unsigned char* p_out = image_output.ptr<uchar>(i);
        for (int j = 0; j < image_output.cols; j++) {
        	if (*(p_out + j) == 255) {
                num_floodfill++;
                Scalar new_val = Scalar(num_floodfill);
                Point seed = Point(j, i);
                CRect rect;
                int area = floodFill(image_output,seed, new_val);
                if (area > area_max) {
                    area_max = area;
                    value_max = num_floodfill;
                }
        	}
        }
    }
    // max area
    int area_left = image_output.cols;
    int area_right = 0;
    int area_top = image_output.rows;
    int area_buttom = 0;
    for (int i = 0; i < image_output.rows; i++) {
        unsigned char* p_out = image_output.ptr<uchar>(i);
        for (int j = 0; j < image_output.cols; j++) {
            if (*(p_out + j) == value_max) {
                *(p_out + j) = 255;
                if (area_left > j) area_left = j;
                if (area_right < j) area_right = j;
                if (area_top > i) area_top = i;
                if (area_buttom < i) area_buttom = i;
            } else {
                *(p_out + j) = 0;
            }
        }
    }
#ifdef _DEBUG
    TRACE("area_left = %d\n", area_left);
    TRACE("area_right = %d\n", area_right);
    TRACE("area_top = %d\n", area_top);
    TRACE("area_buttom = %d\n", area_buttom);
#endif
    // rectangle
    rectangle(image_output, Point(area_left, area_top), Point(area_right, area_buttom), Scalar(255), 5); 
    // moment
    Moments moment = moments(image_output);
    int center_x = moment.m10 / moment.m00;
    int center_y = moment.m01 / moment.m00;
    point_end = Point(center_x, center_y);
    circle(image_output, point_end, 10, Scalar(255), 5);
    GetVector(point_begin, point_end);
    if (vector_length >= 20 || point_begin == Point(image_width / 2, image_height / 2)) {
        point_begin = point_end;
    }
#ifdef _DEBUG
    TRACE("vector_length = %f\n", vector_length);
    TRACE("vector_angle = %f\n", vector_angle);
#endif
    return image_output;
}