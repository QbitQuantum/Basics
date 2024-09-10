static Mat endpointError( const Mat_<Point2f>& flow1, const Mat_<Point2f>& flow2 )
{
    Mat result(flow1.size(), CV_32FC1);
    for ( int i = 0; i < flow1.rows; ++i )
    {
        for ( int j = 0; j < flow1.cols; ++j )
        {
            const Point2f u1 = flow1(i, j);
            const Point2f u2 = flow2(i, j);

            if ( isFlowCorrect(u1) && isFlowCorrect(u2) )
            {
                const Point2f diff = u1 - u2;
                result.at<float>(i, j) = sqrt((float)diff.ddot(diff)); //distance
            } else
                result.at<float>(i, j) = std::numeric_limits<float>::quiet_NaN();
        }
    }
    return result;
}