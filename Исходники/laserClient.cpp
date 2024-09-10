void laserClient::run(){

	IceUtil::Time last;

	last=IceUtil::Time::now();
	while (!(_done)){
		if (pauseStatus){
			IceUtil::Mutex::Lock sync(this->controlMutex);
			this->sem.wait(sync);
		}

		try{
			jderobot::LaserDataPtr localLaser=this->prx->getLaserData();

			this->controlMutex.lock();
			this->data.resize(localLaser->distanceData.size());
			std::copy( localLaser->distanceData.begin(), localLaser->distanceData.end(), this->data.begin() );

			this->controlMutex.unlock();
		}
		catch(...){
			jderobot::Logger::getInstance()->warning(prefix +"error during request (connection error)");
			usleep(5000);

		}


		if ((IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds()) > this->cycle ){
			jderobot::Logger::getInstance()->warning(prefix + ": pointCloud adquisition timeout-");
		}
		else{
			usleep(this->cycle - (IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds()));
		}
		this->refreshRate=(int)(1000000/(IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds()));
		last=IceUtil::Time::now();
	}
}