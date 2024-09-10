double calculateFrameTransitionPenalty(const btTransform &current_frame, const btTransform &prev_frame, 
	const btVector3 &gravity_direction, const btScalar &horizontal_weight, const btScalar &rotation_weight)
{
	btTransform transition = prev_frame.inverse() * current_frame;
	btScalar vertical_move = transition.getOrigin().dot(gravity_direction);
	btScalar horizontal_move = sqrt(transition.getOrigin().length2() - vertical_move * vertical_move);

	btScalar translation = (vertical_move + horizontal_move*horizontal_weight)/SCALING;
	btScalar rotation = transition.getRotation().getAngle();

	// use spring model for frame transition
	btScalar trans_force = 0.5 * translation * translation;
	btScalar rot_force = 0.5 * rotation_weight * rotation * rotation;
	// std::cerr << exp(-10000*trans_force) << ", " << exp(-10*rot_force) << std::endl;
	return exp(-10000*trans_force)*exp(-10*rot_force);
}