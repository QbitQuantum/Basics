void Pose3dIceClient::run(){
	JdeRobotTypes::Pose3d pose3d;

	IceUtil::Time last;

	last=IceUtil::Time::now();
	while (this->on){
		if (pauseStatus){
			IceUtil::Mutex::Lock sync(this->controlMutex);
			this->sem.wait(sync);
		}

		try{
			jderobot::Pose3DDataPtr pose3ddata = this->prx->getPose3DData();

			pose3d.x = pose3ddata->x;
			pose3d.y = pose3ddata->y;
			pose3d.z = pose3ddata->z;
			pose3d.q[0] = pose3ddata->q0;
			pose3d.q[1] = pose3ddata->q1;
			pose3d.q[2] = pose3ddata->q2;
			pose3d.q[3] = pose3ddata->q3;
			pose3d.yaw = this->quat2Yaw(pose3d.q);
			pose3d.pitch = this->quat2Pitch(pose3d.q);
			pose3d.roll = this->quat2Roll(pose3d.q);



			this->controlMutex.lock();
			this->pose = pose3d;
			this->controlMutex.unlock();
		}
		catch(...){
			std::cerr << prefix +"error during request (connection error)" << std::endl;
			usleep(5000);

		}


		if ((IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds()) <= this->cycle ){
			usleep(this->cycle - (IceUtil::Time::now().toMicroSeconds() - last.toMicroSeconds()));
		}
		last=IceUtil::Time::now();
	}
}