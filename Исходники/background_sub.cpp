void processVideo(char* videoFilename) {
    //create the capture object
    IplImage *labelImg;//foreground
    CTracker openTracker((float)0.033, (float)0.6, (double)20.0, 10, 3000);
    CvTracks tracks;
    VideoCapture capture(videoFilename);
    if(!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video file: " << videoFilename << endl;
        exit(EXIT_FAILURE);
    }
    bool bInitialized = false;
    //read input data. ESC or 'q' for quitting
    while( (char)keyboard != 'q' && (char)keyboard != 27 ){
    //read the current frame
    if(!capture.read(frame)) {
        cerr << "Unable to read next frame." << endl;
        cerr << "Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    if(bInitialized==false)
    {
        cv::Size frameSize(static_cast<int>(frame.cols), static_cast<int>(frame.rows)); 					
        labelImg = cvCreateImage(frameSize, IPL_DEPTH_LABEL, 1);         
        bInitialized = true;
    }
    //update the background model
    pMOG2.operator ()(frame,fgMaskMOG2);

    //open operator. 
    cv::erode(fgMaskMOG2,fgMaskMOG2,cv::Mat(),cv::Point(-1,-1),1);
    cv::dilate(fgMaskMOG2,fgMaskMOG2,cv::Mat(),cv::Point(-1,-1),4);

    // step 2::blob analysis
    CvBlobs blobs;          
    unsigned int result = cvLabel(&(IplImage)fgMaskMOG2, labelImg, blobs);          
    cvFilterByArea(blobs, 125, 10000);
    cvRenderBlobs(labelImg, blobs, &(IplImage)frame, &(IplImage)frame, CV_BLOB_RENDER_BOUNDING_BOX);
    //cvUpdateTracks(blobs, tracks, 200, 5);
    //cvRenderTracks(tracks, &(IplImage)frame, &(IplImage)frame, CV_TRACK_RENDER_ID|CV_TRACK_RENDER_BOUNDING_BOX|CV_TRACK_RENDER_TO_LOG);
   
    //convert the blobs into detection structure;
    vector<Detection*> detections;
    for (CvBlobs::const_iterator it=blobs.begin();it!=blobs.end();++it)
    {
      CvBlob *blob=(*it).second;
      Detection *_detection = new Detection;
      _detection->centroid.x= blob->centroid.x;
      _detection->centroid.y= blob->centroid.y;
      _detection->brect.x  = blob->minx;
      _detection->brect.y  = blob->miny;
      _detection->brect.height = blob->maxy - blob->miny;
      _detection->brect.width  = blob->maxx - blob->minx;
      detections.push_back(_detection);
    }

    //Step 3 : give the list of all centroids of all detected contours to tracker. Track return the trace of the track, whose values are Kalman-filtered
    if(blobs.size() > 0)
    {			
        openTracker.Update(detections);
        int i, j;
        for(i=0; i < openTracker.tracks.size(); i++)
        {
        //add a threshold to de-noise, if the contour just appeared, maybe noise. set a threshold
        if(openTracker.tracks[i]->trace.size() > 10)
        {
            for(j = 0; j < (openTracker.tracks[i]->trace.size() - 2); j++)
            {
            cv::rectangle(frame, openTracker.tracks[i]->brect, Scalar(255,0,0));
            //line(fore, openTracker.tracks[i]->trace[j], openTracker.tracks[i]->trace[j+1], Colors[openTracker.tracks[i]->track_id % 9], 1, CV_AA);							
            line(frame, openTracker.tracks[i]->trace[j], openTracker.tracks[i]->trace[j+1], Scalar(255,0,0), 1, CV_AA);
            }

        stringstream ss;
        ss << openTracker.tracks[i]->track_id;
        string str = ss.str();
		
        putText(frame, str, openTracker.tracks[i]->trace[j], FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1);
      }
        }
    }
    //get the frame number and write it on the current frame
    stringstream ss;
    rectangle(frame, cv::Point(10, 2), cv::Point(100,20),cv::Scalar(255,255,255), -1);
    //show the current frame and the fg masks
    imshow("Frame", frame);
    imshow("FG Mask MOG 2", fgMaskMOG2);
    //get the input from the keyboard
    keyboard = waitKey( 30 );
    }
    //delete capture object
    capture.release();
    cvReleaseImage(&labelImg); 

}