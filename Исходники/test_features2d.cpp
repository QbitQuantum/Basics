    void run(int)
    {
        Ptr<Feature2D> f = Algorithm::create<Feature2D>("Feature2D." + fname);
        if(f.empty())
            return;
        string path = string(ts->get_data_path()) + "detectors_descriptors_evaluation/planar/";
        string imgname1 = path + "box.png";
        string imgname2 = path + "box_in_scene.png";
        Mat img1 = imread(imgname1, 0);
        Mat img2 = imread(imgname2, 0);
        if( img1.empty() || img2.empty() )
        {
            ts->printf( cvtest::TS::LOG, "missing %s and/or %s\n", imgname1.c_str(), imgname2.c_str());
            ts->set_failed_test_info( cvtest::TS::FAIL_INVALID_TEST_DATA );
            return;
        }
        vector<KeyPoint> kpt1, kpt2;
        Mat d1, d2;
        f->operator()(img1, Mat(), kpt1, d1);
        f->operator()(img1, Mat(), kpt2, d2);
        for( size_t i = 0; i < kpt1.size(); i++ )
            CV_Assert(kpt1[i].response > 0 );
        for( size_t i = 0; i < kpt2.size(); i++ )
            CV_Assert(kpt2[i].response > 0 );

        vector<DMatch> matches;
        BFMatcher(NORM_L2, true).match(d1, d2, matches);

        vector<Point2f> pt1, pt2;
        for( size_t i = 0; i < matches.size(); i++ ) {
            pt1.push_back(kpt1[matches[i].queryIdx].pt);
            pt2.push_back(kpt2[matches[i].trainIdx].pt);
        }

        Mat inliers, H = findHomography(pt1, pt2, RANSAC, 10, inliers);
        int ninliers = countNonZero(inliers);

        if( ninliers < min_ninliers )
        {
            ts->printf( cvtest::TS::LOG, "too little inliers (%d) vs expected %d\n", ninliers, min_ninliers);
            ts->set_failed_test_info( cvtest::TS::FAIL_INVALID_TEST_DATA );
            return;
        }
    }