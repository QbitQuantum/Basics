void pointcloudClient::run(){

	IceUtil::Time last;

	last=IceUtil::Time::now();

	while (!(_done)){
		if (pauseStatus){
			IceUtil::Mutex::Lock sync(this->controlMutex);
			this->sem.wait(sync);
		}

		try{
			jderobot::pointCloudDataPtr localCloud=this->prx->getCloudData();
			this->controlMutex.lock();
	        this->newData=true;
			this->data.resize(localCloud->p.size());
			std::copy( localCloud->p.begin(), localCloud->p.end(), this->data.begin() );
			this->controlMutex.unlock();
			this->semBlock.broadcast();
		}
		catch(...){
			jderobot::Logger::getInstance()->warning(prefix +"error during request (connection error)");
			usleep(50000);

		}




		int process = this->cycle - (IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds());

		if (process > (int)cycle ){
			jderobot::Logger::getInstance()->warning(prefix + ": pointCloud adquisition timeout-");
		}
		else{
			int delay = (int)cycle - process;
			if (delay <1 || delay > (int)cycle)
				delay = 1;

			usleep(delay);
		}


		this->refreshRate=(int)(1000000/(IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds()));
		last=IceUtil::Time::now();
		usleep(100);
	}
	this->data.clear();

}