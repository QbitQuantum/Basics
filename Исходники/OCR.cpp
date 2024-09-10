//Segment the chars from plate
vector<CharSegment> OCR::segment(Plate plate){
    Mat input=plate.plateImg;
    vector<CharSegment> output;

    //Threshold input image
    Mat img_threshold;
    //To make char image clearly
//    threshold(input, img_threshold, 60, 255, CV_THRESH_BINARY_INV);	//Spain
//    threshold(input, img_threshold, 150~160, 255, CV_THRESH_BINARY);	//China
    // TODO: IMPORTANT
    threshold(input, img_threshold, 175, 255, CV_THRESH_BINARY);	//China
    if(debug) {
        imshow("OCR_Threshold_Binary", img_threshold);
    }

    Mat img_contours;
    img_threshold.copyTo(img_contours);
    //Find contours of possibles characters
    vector< vector< Point> > contours;
    findContours(img_contours,
            contours, // a vector of contours
            CV_RETR_EXTERNAL, // retrieve the external contours
            CV_CHAIN_APPROX_NONE); // all pixels of each contours
    
    // Draw blue contours on a white image
    cv::Mat result;
    img_threshold.copyTo(result);
    cvtColor(result, result, CV_GRAY2RGB);
    cv::drawContours(result,
    		contours,
            -1, // draw all contours
            cv::Scalar(255,0,0), // in BLUE
            1); // with a thickness of 1

    //Start to iterate to each contour founded
    vector<vector<Point> >::iterator itc = contours.begin();
    //Remove patch that are no inside limits of aspect ratio and area.    
    while (itc!=contours.end()) {
        //Create bounding rect of object
        Rect mr = boundingRect(Mat(*itc));
        rectangle(result, mr, Scalar(0,255,0));	//Possible chars in GREEN

        //Crop image
        Mat auxRoi(img_threshold, mr);
        if(verifySizes(auxRoi)){
            auxRoi=preprocessChar(auxRoi);
            output.push_back(CharSegment(auxRoi, mr));
            rectangle(result, mr, Scalar(0,0,255));	//Possible chars in RED
        }
        ++itc;
    }

    if(debug)
    {
        cout << "OCR number of chars: " << output.size() << "\n";
        imshow("OCR Chars", result);
        cvWaitKey(0);
    }

    return output;
}