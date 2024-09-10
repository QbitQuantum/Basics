void robot_mapper::update_map(bool with_intrinsics) {

	rm_localization::UpdateMap update_map_msg;
	update_map_msg.request.idx.resize(map->frames.size());
	update_map_msg.request.transform.resize(map->frames.size());

	if (with_intrinsics) {

		Eigen::Vector3f intrinsics = map->frames[0]->get_intrinsics();

		/*
		 sensor_msgs::SetCameraInfo s;
		 s.request.camera_info.width = map->frames[0]->get_i(0).cols;
		 s.request.camera_info.height = map->frames[0]->get_i(0).rows;

		 // No distortion
		 s.request.camera_info.D.resize(5, 0.0);
		 s.request.camera_info.distortion_model = sensor_msgs::distortion_models::PLUMB_BOB;

		 // Simple camera matrix: square pixels (fx = fy), principal point at center
		 s.request.camera_info.K.assign(0.0);
		 s.request.camera_info.K[0] = s.request.camera_info.K[4] = intrinsics[0];
		 s.request.camera_info.K[2] = intrinsics[1];
		 s.request.camera_info.K[5] = intrinsics[2];
		 s.request.camera_info.K[8] = 1.0;

		 // No separate rectified image plane, so R = I
		 s.request.camera_info.R.assign(0.0);
		 s.request.camera_info.R[0] = s.request.camera_info.R[4] = s.request.camera_info.R[8] = 1.0;

		 // Then P=K(I|0) = (K|0)
		 s.request.camera_info.P.assign(0.0);
		 s.request.camera_info.P[0] = s.request.camera_info.P[5] = s.request.camera_info.K[0]; // fx, fy
		 s.request.camera_info.P[2] = s.request.camera_info.K[2]; // cx
		 s.request.camera_info.P[6] = s.request.camera_info.K[5]; // cy
		 s.request.camera_info.P[10] = 1.0;

		 set_camera_info_service.call(s);
		 */

		update_map_msg.request.intrinsics[0] = intrinsics[0];
		update_map_msg.request.intrinsics[1] = intrinsics[1];
		update_map_msg.request.intrinsics[2] = intrinsics[2];

	} else {
		update_map_msg.request.intrinsics = { {0,0,0}};
	}

	for (size_t i = 0; i < map->frames.size(); i++) {
		update_map_msg.request.idx[i] = map->idx[i];

		Sophus::SE3f position = map->frames[i]->get_pos();

		update_map_msg.request.transform[i].unit_quaternion[0] =
				position.unit_quaternion().coeffs()[0];
		update_map_msg.request.transform[i].unit_quaternion[1] =
				position.unit_quaternion().coeffs()[1];
		update_map_msg.request.transform[i].unit_quaternion[2] =
				position.unit_quaternion().coeffs()[2];
		update_map_msg.request.transform[i].unit_quaternion[3] =
				position.unit_quaternion().coeffs()[3];

		update_map_msg.request.transform[i].position[0] =
				position.translation()[0];
		update_map_msg.request.transform[i].position[1] =
				position.translation()[1];
		update_map_msg.request.transform[i].position[2] =
				position.translation()[2];

	}

	update_map_service.call(update_map_msg);

}