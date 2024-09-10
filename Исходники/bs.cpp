void processVideo(char* videoFilename) {
    //create the capture object
    VideoCapture capture(videoFilename);
    if(!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video file: " << videoFilename << endl;
        exit(EXIT_FAILURE);
    }
    //read input data. ESC or 'q' for quitting
    while( (char)keyboard != 'q' && (char)keyboard != 27 ){

        //read the current frame
        if(!capture.read(frame)) {
            cerr << "Unable to read next frame." << endl;
            cerr << "Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
        //update the background model
           //AND HERE!!!
        pMOG->operator()(frame, fgMaskMOG);
        pMOG2->operator()(frame, fgMaskMOG2);
        //get the frame number and write it on the current frame
        
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20), cv::Scalar(255,255,255), -1);

        // Blob detection

        // Set up the detector with default parameters.
        cv::SimpleBlobDetector detector;
         
        // Detect blobs.
        std::vector<KeyPoint> keypoints;
        detector.detect( fgMaskMOG, keypoints);
         
        // Draw detected blobs as red circles.
        // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
        cv::Mat im_with_keypoints;
        cv::drawKeypoints( frame, keypoints, im_with_keypoints, cv::Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        // Blob detection using BlobTracking
        // TODO: edit cmakelists based on the simple_vehicle_detection cmakelists to solve lib conflicts
        BlobTracking *blob_tracker = new BlobTracking();
        Mat img_output;
        Mat img_mask = imread("imgTest/firstframe.png");
        blob_tracker->process(frame, img_mask, img_output);
        
        //show the current frame and the fg masks
        imshow("Frame", frame);
        imshow("FG Mask MOG", fgMaskMOG);
        imshow("FG Mask MOG 2", fgMaskMOG2);
        imshow("FG Mask MOG with blob keypoints", im_with_keypoints);
        //get the input from the keyboard
        keyboard = waitKey( 0 );

        
    }
    //delete capture object
    capture.release();
}