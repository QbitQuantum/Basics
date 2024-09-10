geometry_msgs::Quaternion calc_quaternion_average( std::vector<geometry_msgs::Pose> pose_vector ){
	
	Eigen::Matrix4f averaging_matrix;
	Eigen::Vector4f quaternion;
	
	averaging_matrix.setZero();
	for( unsigned int sample_ii=0; sample_ii<pose_vector.size(); sample_ii++){
		quaternion(0) = pose_vector[sample_ii].orientation.x;
		quaternion(1) = pose_vector[sample_ii].orientation.y;
		quaternion(2) = pose_vector[sample_ii].orientation.z;
		quaternion(3) = pose_vector[sample_ii].orientation.w;
		averaging_matrix =  averaging_matrix + quaternion*quaternion.transpose();
	  }// for all samples
	 
	 Eigen::EigenSolver<Eigen::Matrix4f> ev_solver;
	 ev_solver.compute( averaging_matrix);
	 Eigen::Vector4cf eigen_values = ev_solver.eigenvalues();
	 float max_ev=eigen_values(0).real();
	 unsigned int max_ii = 0;
	 for( unsigned int ev_ii=1; ev_ii<4; ev_ii++){
		 if( eigen_values(ev_ii).real()>max_ev ){
			 max_ev = eigen_values(ev_ii).real();
			 max_ii=ev_ii;
		 }
	 }
	 
	 Eigen::Vector4f eigen_vector = ev_solver.eigenvectors().col(max_ii).real();
	 eigen_vector.normalize();
	  
	 geometry_msgs::Quaternion quaternion_msg;
	 quaternion_msg.x = eigen_vector(0);
	 quaternion_msg.y = eigen_vector(1);
	 quaternion_msg.z = eigen_vector(2);
	 quaternion_msg.w = eigen_vector(3);
	 return quaternion_msg;
	 
}