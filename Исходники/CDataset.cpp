int CDataset::extractFeatures(const CConfig& conf){

    int imgRow = this->img.at(0)->rows, imgCol = this->img.at(0)->cols;
    cv::Mat *integralMat;

    if(conf.learningMode != 1){
        if(conf.rgbFeature == 1){ // if got rgb image only, calc hog feature
            feature.clear();
            feature.resize(32);
            for(int i = 0; i < 32; ++i)
                feature.at(i) = new cv::Mat(imgRow, imgCol, CV_8UC1);

            cv::cvtColor(*img.at(0), *(feature.at(0)), CV_RGB2GRAY);

            cv::Mat I_x(imgRow, imgCol, CV_16SC1);
            cv::Mat I_y(imgRow, imgCol, CV_16SC1);


            cv::Sobel(*(feature.at(0)), I_x, CV_16S, 1, 0);
            cv::Sobel(*(feature.at(0)), I_y, CV_16S, 0, 1);

            cv::convertScaleAbs(I_x, *(feature[3]), 0.25);
            cv::convertScaleAbs(I_y, *(feature[4]), 0.25);

            // Orientation of gradients
            for(int  y = 0; y < img.at(0)->rows; y++)
                for(int  x = 0; x < img.at(0)->cols; x++) {
                    // Avoid division by zero
                    float tx = (float)I_x.at<short>(y, x) + (float)copysign(0.000001f, I_x.at<short>(y, x));
                    // Scaling [-pi/2 pi/2] -> [0 80*pi]
                    feature.at(1)->at<uchar>(y, x) = (uchar)(( atan((float)I_y.at<short>(y, x) / tx) + 3.14159265f / 2.0f ) * 80);
                    //std::cout << "scaling" << std::endl;
                    feature.at(2)->at<uchar>(y, x) = (uchar)sqrt((float)I_x.at<short>(y, x)* (float)I_x.at<short>(y, x) + (float)I_y.at<short>(y, x) * (float)I_y.at<short>(y, x));
                }

            // Magunitude of gradients
            for(int y = 0; y < img.at(0)->rows; y++)
                for(int x = 0; x < img.at(0)->cols; x++ ) {
                    feature.at(2)->at<uchar>(y, x) = (uchar)sqrt(I_x.at<short>(y, x)*I_x.at<short>(y, x) + I_y.at<short>(y, x) * I_y.at<short>(y, x));
                }

            hog.extractOBin(feature[1], feature[2], feature, 7);

            // calc I_xx I_yy
            cv::Sobel(*(feature.at(0)), I_x, CV_16S, 2, 0);
            cv::Sobel(*(feature.at(0)), I_y, CV_16S, 0, 2);

            cv::convertScaleAbs(I_x, *(feature[5]), 0.25);
            cv::convertScaleAbs(I_y, *(feature[6]), 0.25);

            cv::Mat img_Lab;
            cv::cvtColor(*img.at(0), img_Lab, CV_RGB2Lab);
            cv::vector<cv::Mat> tempfeature(3);

            cv::split(img_Lab, tempfeature);

            for(int i = 0; i < 3; ++i)
                tempfeature.at(i).copyTo(*(feature.at(i)));

            // min max filter
            for(int c = 0; c < 16; ++c)
                minFilter(feature[c], feature[c + 16], 5);
            for(int c = 0; c < 16; ++c)
                maxFilter(feature[c], feature[c], 5);

        }else{
            feature.clear();

            // calc gray integral image
            cv::Mat grayImg(imgRow + 1, imgCol, CV_8U);
            cv::cvtColor(*img.at(0), grayImg, CV_RGB2GRAY);
            integralMat = new cv::Mat(imgRow + 1, imgCol + 1, CV_64F);
            cv::integral(grayImg, *integralMat, CV_64F);
            feature.push_back(integralMat);

            // calc r g b integral image
            std::vector<cv::Mat> splittedRgb;
            cv::split(*img.at(0), splittedRgb);
            for(int i = 0; i < splittedRgb.size(); ++i){
                integralMat = new cv::Mat(imgRow + 1, imgCol + 1, CV_64F);
                cv::integral(splittedRgb.at(i), *integralMat, CV_64F);
                feature.push_back(integralMat);
            }



            featureFlag = 1;
        }
    }

    if(img.size() > 1){
        cv::Mat tempDepth = cv::Mat(img.at(0)->rows, img.at(0)->cols, CV_8U);// = *img.at(1);

        if(img.at(1)->type() != CV_8U)
            img.at(1)->convertTo(tempDepth, CV_8U, 255.0 / (double)(conf.maxdist - conf.mindist));
        else
            tempDepth = *img.at(1);
        integralMat = new cv::Mat(imgRow + 1, imgCol + 1, CV_64F);
        cv::integral(tempDepth, *integralMat, CV_64F);
        feature.push_back(integralMat);

        featureFlag  = 1;
    }

    return 0;
}