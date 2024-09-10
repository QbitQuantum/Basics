int 
main(int argc, char *argv[]) {
        
        cv::Mat src = cv::imread("0.bmp", 1);

        vector<Point2f> corners(4);

        corners[0] = Point2f(277,61);
        corners[1] = Point2f(385,52);
        corners[2] = Point2f(410,195);
        corners[3] = Point2f(273,215);

        Mat dst(400, 390, src.type());

        qua_to_rect(src, corners, dst);

        draw_points(src, corners);

        cv::imshow("original", src);
        cv::imshow("result", dst);
        cv::waitKey(0);
        
        return 0;
}