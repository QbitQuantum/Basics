double calculateArea(Mat img,int col,int row)
{


    Mat A = Mat::ones(row, col, CV_8U);
    return A.dot(img);
}