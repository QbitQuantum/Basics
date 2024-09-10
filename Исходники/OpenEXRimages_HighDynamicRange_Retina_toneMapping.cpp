/*
 * objective : get the gray level map of the input image and rescale it to the range [0-255]
 */
 static void rescaleGrayLevelMat(const cv::Mat &inputMat, cv::Mat &outputMat, const float histogramClippingLimit)
 {

     // adjust output matrix wrt the input size but single channel
     std::cout<<"Input image rescaling with histogram edges cutting (in order to eliminate bad pixels created during the HDR image creation) :"<<std::endl;
     //std::cout<<"=> image size (h,w,channels) = "<<inputMat.size().height<<", "<<inputMat.size().width<<", "<<inputMat.channels()<<std::endl;
     //std::cout<<"=> pixel coding (nbchannel, bytes per channel) = "<<inputMat.elemSize()/inputMat.elemSize1()<<", "<<inputMat.elemSize1()<<std::endl;

     // rescale between 0-255, keeping floating point values
     cv::normalize(inputMat, outputMat, 0.0, 255.0, cv::NORM_MINMAX);

     // extract a 8bit image that will be used for histogram edge cut
     cv::Mat intGrayImage;
     if (inputMat.channels()==1)
     {
         outputMat.convertTo(intGrayImage, CV_8U);
     }else
     {
         cv::Mat rgbIntImg;
         outputMat.convertTo(rgbIntImg, CV_8UC3);
         cv::cvtColor(rgbIntImg, intGrayImage, cv::COLOR_BGR2GRAY);
     }

     // get histogram density probability in order to cut values under above edges limits (here 5-95%)... usefull for HDR pixel errors cancellation
     cv::Mat dst, hist;
     int histSize = 256;
     calcHist(&intGrayImage, 1, 0, cv::Mat(), hist, 1, &histSize, 0);
     cv::Mat normalizedHist;
     normalize(hist, normalizedHist, 1, 0, cv::NORM_L1, CV_32F); // normalize histogram so that its sum equals 1

     double min_val, max_val;
     minMaxLoc(normalizedHist, &min_val, &max_val);
     //std::cout<<"Hist max,min = "<<max_val<<", "<<min_val<<std::endl;

     // compute density probability
     cv::Mat denseProb=cv::Mat::zeros(normalizedHist.size(), CV_32F);
     denseProb.at<float>(0)=normalizedHist.at<float>(0);
     int histLowerLimit=0, histUpperLimit=0;
     for (int i=1;i<normalizedHist.size().height;++i)
     {
         denseProb.at<float>(i)=denseProb.at<float>(i-1)+normalizedHist.at<float>(i);
         //std::cout<<normalizedHist.at<float>(i)<<", "<<denseProb.at<float>(i)<<std::endl;
         if ( denseProb.at<float>(i)<histogramClippingLimit)
             histLowerLimit=i;
         if ( denseProb.at<float>(i)<1-histogramClippingLimit)
             histUpperLimit=i;
     }
     // deduce min and max admitted gray levels
     float minInputValue = (float)histLowerLimit/histSize*255;
     float maxInputValue = (float)histUpperLimit/histSize*255;

     std::cout<<"=> Histogram limits "
             <<"\n\t"<<histogramClippingLimit*100<<"% index = "<<histLowerLimit<<" => normalizedHist value = "<<denseProb.at<float>(histLowerLimit)<<" => input gray level = "<<minInputValue
             <<"\n\t"<<(1-histogramClippingLimit)*100<<"% index = "<<histUpperLimit<<" => normalizedHist value = "<<denseProb.at<float>(histUpperLimit)<<" => input gray level = "<<maxInputValue
             <<std::endl;
     //drawPlot(denseProb, "input histogram density probability", histLowerLimit, histUpperLimit);
     drawPlot(normalizedHist, "input histogram", histLowerLimit, histUpperLimit);

     // rescale image range [minInputValue-maxInputValue] to [0-255]
     outputMat-=minInputValue;
     outputMat*=255.0/(maxInputValue-minInputValue);
     // cut original histogram and back project to original image
     cv::threshold( outputMat, outputMat, 255.0, 255.0, 2 ); //THRESH_TRUNC, clips values above 255
     cv::threshold( outputMat, outputMat, 0.0, 0.0, 3 ); //THRESH_TOZERO, clips values under 0

 }