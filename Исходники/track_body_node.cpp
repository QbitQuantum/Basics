// computes the optimal rigid body transformation given a set of points
void PoseTracker::computeOptimalRigidTransformation(Eigen::MatrixXd startP, Eigen::MatrixXd finalP)
{	
	Eigen::Matrix4d transf;
	
	if (startP.rows()!=finalP.rows())
	{	
		ROS_ERROR("We need that the rows be the same at the beggining");
		exit(1);
	}

	Eigen::RowVector3d centroid_startP = Eigen::RowVector3d::Zero(); 
	Eigen::RowVector3d centroid_finalP = Eigen::RowVector3d::Zero(); //= mean(B);
	Eigen::Matrix3d H = Eigen::Matrix3d::Zero();

	//calculate the mean
	for (int i=0;i<startP.rows();i++)
	{	
		centroid_startP = centroid_startP+startP.row(i);
		centroid_finalP = centroid_finalP+finalP.row(i);
	}
	
	centroid_startP = centroid_startP/startP.rows();
	centroid_finalP = centroid_finalP/startP.rows();

	for (int i=0;i<startP.rows();i++)
		H = H + (startP.row(i)-centroid_startP).transpose()*(finalP.row(i)-centroid_finalP);

   	Eigen::JacobiSVD<Eigen::MatrixXd> svd(H, Eigen::ComputeFullU | Eigen::ComputeFullV);
   
    Eigen::MatrixXd U = svd.matrixU();
   	Eigen::MatrixXd V = svd.matrixV();
  
    if (V.determinant()<0)
   		V.col(2)=-V.col(2)*(-1);

	Eigen::MatrixXd R = V*U.transpose();

	Eigen::Matrix4d C_A = Eigen::Matrix4d::Identity();
	Eigen::Matrix4d C_B = Eigen::Matrix4d::Identity();
	Eigen::Matrix4d R_new = Eigen::Matrix4d::Identity();
			
	C_A.block<3,1>(0,3) = -centroid_startP.transpose();
	R_new.block<3,3>(0,0) = R;
	
	C_B.block<3,1>(0,3) = centroid_finalP.transpose();


	transf = C_B * R_new * C_A;

	Eigen::Quaterniond mat_rot(transf.block<3,3>(0,0));

	Eigen::Vector3d trasl = transf.block<3,1>(0,3).transpose();

	transfParameters_ << trasl(0), trasl(1), trasl(2), mat_rot.x(), mat_rot.y(), mat_rot.z(), mat_rot.w();

}