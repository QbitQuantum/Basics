void
cameraClient::run(){
	jderobot::ImageDataPtr dataPtr;
	IceUtil::Time last;

	int iterIndex = 0;
	int totalRefreshRate = 0;

	last=IceUtil::Time::now();
	while (!(_done)){

		iterIndex ++;
		if (pauseStatus){
			IceUtil::Mutex::Lock sync(this->controlMutex);
			this->semWait.wait(sync);
		}

		try{

			dataPtr = this->prx->getImageData(this->mImageFormat);
			cv::Mat image = CameraUtils::getImageFromCameraProxy(dataPtr);
			this->controlMutex.lock();
			image.copyTo(this->data);
			this->newData=true;
			this->semBlock.broadcast();
			this->controlMutex.unlock();


		}
		catch(...){
			LOG(WARNING) << prefix +"error during request (connection error)";
			usleep(50000);

		}

		int process = (IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds());



		if (process > (int)cycle ){
			DLOG(WARNING) << "--------" + prefix + " adquisition timeout-";
		}
		else{
			int delay = (int)cycle - process;
			if (delay <1 || delay > (int)cycle)
				delay = 1;

			usleep(delay);
		}


		int rate =(int)(1000000/(IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds()));
		totalRefreshRate =  totalRefreshRate + rate;
		this->refreshRate= totalRefreshRate / iterIndex;
		last=IceUtil::Time::now();

		if (iterIndex == INT_MAX) 
		{
			iterIndex = 0;
			DLOG(INFO) << "*** Counter reset";
		}

	}
	this->data.release();
}