	/**
	 * @brief Compose rotation and translation
	 */
	void updateViewMatrix() override
	{
		Eigen::Vector3f xAxis = rotation_matrix.row(0);
		Eigen::Vector3f yAxis = rotation_matrix.row(1);
		Eigen::Vector3f zAxis = rotation_matrix.row(2);
		
		if( rotation_Z_axis )
		{
			Eigen::AngleAxisf transfRotZ = Eigen::AngleAxisf(rotation_Z_axis, zAxis);
			
			// compute X axis restricted to a rotation around Z axis
			xAxis = transfRotZ * xAxis;
			xAxis.normalize();
			
			// compute Y axis restricted to a rotation around Z axis
			yAxis = transfRotZ * yAxis;
			yAxis.normalize();
			
			rotation_Z_axis = 0.0;
		}
		
		Eigen::AngleAxisf transfRotY = Eigen::AngleAxisf(rotation_Y_axis, yAxis);
		
		// compute X axis restricted to a rotation around Y axis
		Eigen::Vector3f rotX = transfRotY * xAxis;
		rotX.normalize();

		Eigen::AngleAxisf transfRotX = Eigen::AngleAxisf(rotation_X_axis, rotX);
		
		// rotate Z axis around Y axis, then rotate new Z axis around X new axis
		Eigen::Vector3f rotZ = transfRotY * zAxis;
		rotZ = transfRotX * rotZ;
		rotZ.normalize();

		// rotate Y axis around X new axis
		Eigen::Vector3f rotY = transfRotX * yAxis;
		rotY.normalize();

		rotation_matrix.row(0) = rotX;
		rotation_matrix.row(1) = rotY;
		rotation_matrix.row(2) = rotZ;
		
		resetViewMatrix();
		view_matrix.rotate (rotation_matrix);
		view_matrix.translate (translation_vector);
		
		rotation_X_axis = 0.0;
		rotation_Y_axis = 0.0;
	}