void EstimationNode::publishTf(TooN::SE3<> trans, ros::Time stamp, int seq, std::string system)
{
	trans = trans.inverse();

	tf::Matrix3x3 m;
	m[0][0] = trans.get_rotation().get_matrix()(0,0);
	m[0][1] = trans.get_rotation().get_matrix()(0,1);
	m[0][2] = trans.get_rotation().get_matrix()(0,2);
	m[1][0] = trans.get_rotation().get_matrix()(1,0);
	m[1][1] = trans.get_rotation().get_matrix()(1,1);
	m[1][2] = trans.get_rotation().get_matrix()(1,2);
	m[2][0] = trans.get_rotation().get_matrix()(2,0);
	m[2][1] = trans.get_rotation().get_matrix()(2,1);
	m[2][2] = trans.get_rotation().get_matrix()(2,2);

	tf::Vector3 v;
	v[0] = trans.get_translation()[0];
	v[1] = trans.get_translation()[1];
	v[2] = trans.get_translation()[2];


	tf::Transform tr = tf::Transform(m,v);
	tf::StampedTransform t = tf::StampedTransform(tr,stamp,"map",system);
	tf_broadcaster.sendTransform(t);



	if(logfilePTAMRaw != NULL)
	{
		pthread_mutex_lock(&(logPTAMRaw_CS));
		// log:
		// - filterPosePrePTAM estimated for videoFrameTimestamp-delayVideo.
		// - PTAMResulttransformed estimated for videoFrameTimestamp-delayVideo. (using imu only for last step)
		// - predictedPoseSpeed estimated for lastNfoTimestamp+filter->delayControl	(actually predicting)
		// - predictedPoseSpeedATLASTNFO estimated for lastNfoTimestamp	(using imu only)
		if(logfilePTAMRaw != NULL)
			(*(logfilePTAMRaw)) << seq << " " << stamp << " " << tr.getOrigin().x() << " " << tr.getOrigin().y() << " " << tr.getOrigin().z() << " " <<
			tr.getRotation().x() << " " << tr.getRotation().y() << " " << tr.getRotation().z() << " " << tr.getRotation().w() << std::endl;

		pthread_mutex_unlock(&(logPTAMRaw_CS));
	}

}