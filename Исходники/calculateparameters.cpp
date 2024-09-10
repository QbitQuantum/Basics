//Function for calculating Rotation Matrix
Mat rotation_matrix(double theta)
{
	/*
	 * Calculating rotation matrix
	 */
	// VUP matrix Points opposite of Gravity
	Mat vup = Mat::zeros(1, 3, CV_32F);
	vup.at<float>(1) = 1;
	//	cout << "VUP: "<< vup << endl;

	// Look-At Point ..... Where the camera is pointing (VPN)
	Mat look_at_point = Mat::zeros(1, 3, CV_32F);
	look_at_point.at<float>(1) = -1;
	look_at_point.at<float>(2) = -1;
	//	cout << "Look-At Point: "<<look_at_point<<endl;
	look_at_point = look_at_point / norm(look_at_point, NORM_L2);
	//	cout << "Normalized Look-At point (n): "<< look_at_point<<endl;


	// The u_axis vector
	Mat u_axis = vup.cross(look_at_point);
	//	cout << "U axis: "<< u_axis<<endl;
	u_axis = u_axis / norm(u_axis, NORM_L2);
	//	cout << "Normalized U axis: "<< u_axis<<endl;

	// The v_axis vector
	Mat v_axis = look_at_point.cross(u_axis);
	//	cout << "V_axis (should be normalized): "<<v_axis<<endl<<endl;

	/*
	 * Rotation Matrix for the camera to get the new axis
	 */
	Mat rotationMatrix;
	rotationMatrix.push_back(u_axis);
	rotationMatrix.push_back(v_axis);
	rotationMatrix.push_back(look_at_point);
	//	cout << "Rotation matrix: "<<endl<< rotationMatrix<<endl<<endl;

	/*
	 * Converting the Rotation Matrix into a Homogeneous Rotation Matrix
	 */
	Mat homogeneousRotationMatrix; //= Mat::eye(4,3, CV_32F);
	homogeneousRotationMatrix.push_back(u_axis);
	homogeneousRotationMatrix.push_back(v_axis);
	homogeneousRotationMatrix.push_back(look_at_point);

	Mat justarow = Mat::zeros(1, 3, CV_32F);
	homogeneousRotationMatrix.push_back(justarow);

	Mat justacolumn = Mat::zeros(4, 1, CV_32F);
	justacolumn.at<float>(3,0) = 1;

	hconcat(homogeneousRotationMatrix, justacolumn, homogeneousRotationMatrix);
	//	cout << "Homogeneous Rotation matrix:"<<endl<<homogeneousRotationMatrix<<endl<<endl;
	return homogeneousRotationMatrix;
}