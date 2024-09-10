void PR2EihMapping::publish_positions_to_logger(const StdVectorJ& J) {
	for(const VectorJ& j : J) {
		Vector3d position = arm_sim->fk(j).block<3,1>(0,3);
		std::stringstream ss;
		ss << "gripper position " << position.transpose();
		publish_to_logger(ss.str());
	}
}