void CAI_Stalker::update_throw_params		()
{
	if (m_throw_actual) {
		if (m_computed_object_position.similar(Position())) {
			if (m_computed_object_direction.similar(Direction())) {
				VERIFY		(_valid(m_throw_force));
				return;
			}
		}
	}

	m_throw_actual			= true;
	m_computed_object_position	= Position();
	m_computed_object_direction	= Direction();

	m_throw_position		= eye_matrix.c;

	// computing velocity with minimum magnitude
	Fvector					velocity;
	velocity.sub			(m_throw_target,m_throw_position);
	float					time = ThrowMinVelTime(velocity,ph_world->Gravity());
	TransferenceToThrowVel	(velocity,time,ph_world->Gravity());
	m_throw_force			= velocity.magnitude();
	m_throw_direction		= velocity.normalize();
	VERIFY					(_valid(m_throw_force));
}