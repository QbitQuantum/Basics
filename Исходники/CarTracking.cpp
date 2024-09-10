int main(int argc, const char* argv[])  
{  

	const int MAX_SIZE = 400;

	Mat frame; 
	Mat noBackground; 


	Ptr<BackgroundSubtractor> pMOG; //MOG Background subtractor  
	pMOG = new BackgroundSubtractorMOG2();  

	/* Blob Tracking Algorithm */
	Mat  img_blob; 
	BlobTracking* blobTracking;
	blobTracking = new BlobTracking;

	/* Motion detector */
	MotionTracker* tracker;
	tracker = new MotionTracker;


	string fileName = argv[1]; 
	VideoCapture stream1(fileName);   
	Mat img_mask;

	// we need a first frame to configure points if not defined
	stream1.read(frame);
	bool mustResize = ((frame.size().width) > MAX_SIZE) ? 1 : 0;
	double fps = stream1.get(CV_CAP_PROP_FPS);

	tracker->init(frame, fileName);
	tracker->setFPS(fps);
	long frames  = 0;
	cout << fps << " fps " << endl;

	while (true) {     

		if(!(stream1.read(frame))){
			break; 
		} 

		if (mustResize)
			resize(frame, frame, Size(frame.size().width/2, frame.size().height/2) );  

		//edianBlur(frame, frame, 11);
		pMOG->operator()(frame, noBackground);

		if ( !noBackground.empty())
		{
			blobTracking->process(frame, noBackground, img_blob);
			tracker->setTracks(blobTracking->getTracks());
			tracker->detect(frame,frames);
		} 

		if (waitKey(1) >= 0)     
			break;     
	}

	return 0;

}  