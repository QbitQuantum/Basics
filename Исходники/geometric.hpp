	Edge steerWithControl(const State &start, const std::vector<double> controls, double dt) const {
		/* Be careful about the order these are being passed in */
		fcl::Vec3f translation(controls[0], controls[1], controls[2]);
		fcl::Quaternion3f rotation(controls[3], controls[4], controls[5], controls[6]);
		rotation = math::normalize(rotation);

		State end = doSteps(start, translation, rotation, dt);

		return Edge(start, end, translation, rotation, dt);
	}