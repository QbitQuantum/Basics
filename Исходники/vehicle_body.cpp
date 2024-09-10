//bilateral constraint between two dynamic objects
void VehicleBody::_resolve_single_bilateral(PhysicsDirectBodyState *s, const Vector3 &pos1,
		PhysicsBody *body2, const Vector3 &pos2, const Vector3 &normal, real_t &impulse, const real_t p_rollInfluence) {

	real_t normalLenSqr = normal.length_squared();
	//ERR_FAIL_COND( normalLenSqr < real_t(1.1));

	if (normalLenSqr > real_t(1.1)) {
		impulse = real_t(0.);
		return;
	}

	Vector3 rel_pos1 = pos1 - s->get_transform().origin;
	Vector3 rel_pos2;
	if (body2)
		rel_pos2 = pos2 - body2->get_global_transform().origin;
	//this jacobian entry could be re-used for all iterations

	Vector3 vel1 = s->get_linear_velocity() + (s->get_angular_velocity()).cross(rel_pos1); // * mPos);
	Vector3 vel2;

	if (body2)
		vel2 = body2->get_linear_velocity() + body2->get_angular_velocity().cross(rel_pos2);

	Vector3 vel = vel1 - vel2;

	Basis b2trans;
	float b2invmass = 0;
	Vector3 b2lv;
	Vector3 b2av;
	Vector3 b2invinertia; //todo

	if (body2) {
		b2trans = body2->get_global_transform().basis.transposed();
		b2invmass = body2->get_inverse_mass();
		b2lv = body2->get_linear_velocity();
		b2av = body2->get_angular_velocity();
	}

	btVehicleJacobianEntry jac(s->get_transform().basis.transposed(),
			b2trans,
			rel_pos1,
			rel_pos2,
			normal,
			s->get_inverse_inertia_tensor().get_main_diagonal(),
			1.0 / mass,
			b2invinertia,
			b2invmass);

	// FIXME: rel_vel assignment here is overwritten by the following assignment.
	// What seemes to be intended in the next next assignment is: rel_vel = normal.dot(rel_vel);
	// Investigate why.
	real_t rel_vel = jac.getRelativeVelocity(
			s->get_linear_velocity(),
			s->get_transform().basis.transposed().xform(s->get_angular_velocity()),
			b2lv,
			b2trans.xform(b2av));

	rel_vel = normal.dot(vel);

	// !BAS! We had this set to 0.4, in bullet its 0.2
	real_t contactDamping = real_t(0.2);

	if (p_rollInfluence > 0.0) {
		// !BAS! But seeing we apply this frame by frame, makes more sense to me to make this time based
		// keeping in mind our anti roll factor if it is set
		contactDamping = s->get_step() / p_rollInfluence;
	}

#define ONLY_USE_LINEAR_MASS
#ifdef ONLY_USE_LINEAR_MASS
	real_t massTerm = real_t(1.) / ((1.0 / mass) + b2invmass);
	impulse = -contactDamping * rel_vel * massTerm;
#else
	real_t velocityImpulse = -contactDamping * rel_vel * jacDiagABInv;
	impulse = velocityImpulse;
#endif
}