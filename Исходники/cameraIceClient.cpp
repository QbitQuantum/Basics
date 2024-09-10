void
CameraIceClient::run(){
	jderobot::ImageDataPtr dataPtr;
	colorspaces::Image::FormatPtr fmt;
	IceUtil::Time last;

	int iterIndex = 0;
	int totalRefreshRate = 0;
	int refrRate = 0;

	JdeRobotTypes::Image img;

	last=IceUtil::Time::now();
	while (this->on){

		iterIndex ++;
		if (pauseStatus){
			IceUtil::Mutex::Lock sync(this->controlMutex);
			this->semWait.wait(sync);
		}

		try{

			
			dataPtr = this->prx->getImageData(this->mImageFormat);

			

			

			// Putting image data
			img.data = CameraUtils::getImageFromCameraProxy(dataPtr);
			
			img.format = dataPtr->description->format;
			img.width = dataPtr->description->width;
			img.height = dataPtr->description->height;
			img.timeStamp = dataPtr->timeStamp.seconds + dataPtr->timeStamp.useconds * 1e-6;




		}
		catch(std::exception& e){
			LOG(WARNING) << prefix +"error during request (connection error): " << e.what() << std::endl;
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
		refrRate = totalRefreshRate / iterIndex;
		last=IceUtil::Time::now();

		if (iterIndex == INT_MAX) 
		{
			iterIndex = 0;
			DLOG(INFO) << "*** Counter reset";
		}

		this->controlMutex.lock();
		this->image = img;
		this->refreshRate = refrRate;
		this->controlMutex.unlock();

	}

	this->image.data.release();
}