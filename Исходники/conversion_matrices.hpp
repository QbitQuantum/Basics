      Eigen::Matrix3d get()
      {
	Eigen::Matrix3d interim = worker.get();
	Eigen::Matrix3d retval = interim.transpose();
	return retval;
      }