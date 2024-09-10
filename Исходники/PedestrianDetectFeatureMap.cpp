cv::Mat PedestrianFeatureMap::compute(int frame) {

    cv::Mat img = m_frame.color;

    std::vector<cv::Rect> found, found_filtered;
    std::vector<double> weights;
    m_HOG.detectMultiScale(img, found, weights, 0.7, cv::Size(8,8), cv::Size(32,32), 1.05, 2);

    for (size_t i = 0 ; i < found.size() ; i++) {
        cv::Rect r = found[i];

        found_filtered.push_back(r);
    }


    cv::Mat smap(img.size(), CV_32FC1, cv::Scalar(0.f));


    for (size_t i = 0 ; i < found_filtered.size() ; i++) {
        cv::Rect r2 = found_filtered[i];
        r2.x += roundl(r2.width*0.1);
        r2.width = roundl(r2.width*0.8);
        r2.y += roundl(r2.height*0.06);
        r2.height = roundl(r2.height*0.9);

        // show bounding box
        // cv::rectangle(img, r2.tl(), r2.br(), cv::Scalar(0,255*weights[i],0), 2);

        cv::rectangle(smap, r2.tl(), r2.br(), cv::Scalar(1), cv::FILLED);
	}
    


    if(m_FaceCascadeEnabled) {
        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        cv::resize(gray, gray, cv::Size(1400, 788));
        std::vector<cv::Rect> faceFeatures;
        if (m_FaceCascadeEnabled)
            m_face_cascade.detectMultiScale(gray, faceFeatures, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(15, 15));
        
        float scalingFactorX = static_cast<float>(img.cols) / 1400.f;
        float scalingFactorY = static_cast<float>(img.rows) / 788.f;

        for (size_t i = 0; i < faceFeatures.size(); ++i) {
            cv::Rect r2 = faceFeatures[i];
            r2.x *= scalingFactorX;
            r2.y *= scalingFactorY;
            r2.width *= scalingFactorX;
            r2.height *= scalingFactorY;

            r2.x += roundl(r2.width*0.1);
            r2.width = roundl(r2.width*0.8);
            r2.y += roundl(r2.height*0.06);
            r2.height = roundl(r2.height*0.9);

            cv::rectangle(smap, r2.tl(), r2.br(), cv::Scalar(1), cv::FILLED);
            
        }
    }
    
    return smap;
}