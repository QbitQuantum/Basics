void Person::update(int cx, int cy, tf::Transform transform, Time time)
{
	double dt = time.sec - last_update_time_.sec;
	Eigen::Matrix<double, 3, 4> tf_matrix;
	
	//Copy rotation matrix
	tf::Matrix3x3 rotation = transform.getBasis();
	for(int i=0; i < 3; i++)
	{
		tf::Vector3 row = rotation.getRow(i);
		tf_matrix(i,0) = row.x();	
		tf_matrix(i,1) = row.y(); 	
		tf_matrix(i,2) = row.z(); 	
	}

	//Copy translation matrix
	tf::Vector3 translation = transform.getOrigin();

	tf_matrix(0,3) = translation.x();	
	tf_matrix(1,3) = translation.y();	
	tf_matrix(2,3) = translation.z();	

	kf_->predict(dt);	
	kf_->update(cx, cy, tf_matrix, time);	
	last_update_time_ = time;

	life_time_ = 5;
	return;
}