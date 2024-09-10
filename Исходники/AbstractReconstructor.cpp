/**************************************************
matlab resouce:http://www.robots.ox.ac.uk/~vgg/hzbook/code/
vgg_F_from_P.m
*****************************************************/
void AbstractReconstructor::ProjectionToFundamentalMatrix(cv::Mat& mat1, cv::Mat& mat2, cv::Mat& result)
{
    cv::Mat X1,X2,X3,Y1,Y2,Y3;
    X1.create(2,4,CV_32F);
    X2.create(2,4,CV_32F);
    X3.create(2,4,CV_32F);
    Y1.create(2,4,CV_32F);
    Y2.create(2,4,CV_32F);
    Y3.create(2,4,CV_32F);
    //mat1(1,2)  copy to X1
    mat1.row(1).copyTo(X1.row(0));
    mat1.row(2).copyTo(X1.row(1));

    //mat1(2,0)  copy to X2
    mat1.row(2).copyTo(X2.row(0));
    mat1.row(0).copyTo(X2.row(1));

    //mat1(0,1)  copy to X2
    mat1.row(0).copyTo(X3.row(0));
    mat1.row(1).copyTo(X3.row(1));

    //mat2(1,2)  copy to Y1
    mat2.row(1).copyTo(Y1.row(0));
    mat2.row(2).copyTo(Y1.row(1));

    //mat2(2,0)  copy to Y2
    mat2.row(2).copyTo(Y2.row(0));
    mat2.row(0).copyTo(Y2.row(1));

    //mat2(0,1)  copy to Y2
    mat2.row(0).copyTo(Y3.row(0));
    mat2.row(1).copyTo(Y3.row(1));

    cv::Mat  temp;
    temp.create(4,4, CV_32F);

    //calculate result[0,0]
    temp.row(0) = X1.row(0);
    temp.row(1) = X1.row(1);
    temp.row(2) = Y1.row(0);
    temp.row(3) = Y1.row(1);
    result.at<float>(0, 0) = determinant(temp);

    //calculate result[0,1]
    temp.row(0) = X2.row(0);
    temp.row(1) = X2.row(1);
    temp.row(2) = Y1.row(0);
    temp.row(3) = Y1.row(1);
    result.at<float>(0, 1) = determinant(temp);

    //calculate result[0,2]
    temp.row(0) = X3.row(0);
    temp.row(1) = X3.row(1);
    temp.row(2) = Y1.row(0);
    temp.row(3) = Y1.row(1);
    result.at<float>(0, 2) = determinant(temp);

    //calculate result[1,0]
    temp.row(0) = X1.row(0);
    temp.row(1) = X1.row(1);
    temp.row(2) = Y2.row(0);
    temp.row(3) = Y2.row(1);
    result.at<float>(1, 0) = determinant(temp);

    //calculate result[1,1]
    temp.row(0) = X2.row(0);
    temp.row(1) = X2.row(1);
    temp.row(2) = Y2.row(0);
    temp.row(3) = Y2.row(1);
    result.at<float>(1, 1) = determinant(temp);

    //calculate result[1,2]
    temp.row(0) = X3.row(0);
    temp.row(1) = X3.row(1);
    temp.row(2) = Y2.row(0);
    temp.row(3) = Y2.row(1);
    result.at<float>(1, 2) = determinant(temp);

    //calculate result[2,0]
    temp.row(0) = X1.row(0);
    temp.row(1) = X1.row(1);
    temp.row(2) = Y3.row(0);
    temp.row(3) = Y3.row(1);
    result.at<float>(2, 0) = determinant(temp);

    //calculate result[2,1]
    temp.row(0) = X2.row(0);
    temp.row(1) = X2.row(1);
    temp.row(2) = Y3.row(0);
    temp.row(3) = Y3.row(1);
    result.at<float>(2, 1) = determinant(temp);

    //calculate result[2,2]
    temp.row(0) = X3.row(0);
    temp.row(1) = X3.row(1);
    temp.row(2) = Y3.row(0);
    temp.row(3) = Y3.row(1);
    result.at<float>(2, 2) = determinant(temp);

    return ;

}