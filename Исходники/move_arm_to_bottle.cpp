BottlePosition findBottlePose(moveit::planning_interface::MoveGroup &group) {
	BottlePosition result;
	vector<Pose> arm_poses = computeArmPosesForDetection();
	vector<BottlePosition> measurements;

	for (vector<Pose>::iterator pose = arm_poses.begin();
			pose != arm_poses.end(); pose++) {
		if (!moveTo(group, *pose)) {
			throw std::runtime_error(
					"Error in determining bottle pose: The arm could not move to the given pose.");
		}
		stabilisation_duration.sleep();

		BottlePosition bottle_position;
		bool found_bottle = getBottlePositionFromTf(bottle_position);
		if (found_bottle) {
			measurements.push_back(bottle_position);

			ROS_INFO("Found bottle at:");
			printPose(measurements.back().bottlePose);
			ROS_INFO("And cap at:");
			printPose(measurements.back().bottleCapPose);
		} else {
			ROS_WARN("Measurement is ignored");
		}
	}
	if (measurements.size() == 0) {
		ROS_ERROR("The bottle was not found from any pose. The program will shut down!");
		exit(-1);
	}
	result = computeBottlePoseFromMeasurements(measurements);

	ROS_INFO("Average pose:");
	printPose(result.bottlePose);
	ROS_INFO("Average cap pose:");
	printPose(result.bottleCapPose);

	return result;
}