carmen_6d_point 
get_carmen_pose6D_from_matrix(Matrix visual_odometry_transformation_matrix)
{
//	// See: http://www.ros.org/wiki/tf
	tf::Transform visual_odometry_pose;
	tf::Transform carmen_pose;
	carmen_6d_point carmen_pose_6d;

	// convert the visual odometry output matrix to the tf::Transform type.
	visual_odometry_pose = convert_matrix_to_tf_transform(visual_odometry_transformation_matrix);

	// compute the current visual odometry pose with respect to the carmen coordinate system
	carmen_pose = g_car_to_visual_odometry_transform * visual_odometry_pose * g_car_to_visual_odometry_transform.inverse();

	double yaw, pitch, roll;
	tf::Matrix3x3(carmen_pose.getRotation()).getRPY(roll, pitch, yaw);

	carmen_pose_6d.x = carmen_pose.getOrigin().x();
	carmen_pose_6d.y = carmen_pose.getOrigin().y();
	carmen_pose_6d.z = carmen_pose.getOrigin().z();

	carmen_pose_6d.yaw = yaw;
	carmen_pose_6d.pitch = pitch;
	carmen_pose_6d.roll = roll;

	 return carmen_pose_6d;
}