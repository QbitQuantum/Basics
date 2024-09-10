bool BodyPairSW::setup(float p_step) {

	//cannot collide
	if ((A->get_layer_mask()&B->get_layer_mask())==0 || A->has_exception(B->get_self()) || B->has_exception(A->get_self()) || (A->get_mode()<=PhysicsServer::BODY_MODE_KINEMATIC && B->get_mode()<=PhysicsServer::BODY_MODE_KINEMATIC && A->get_max_contacts_reported()==0 && B->get_max_contacts_reported()==0)) {
		collided=false;
		return false;
	}

	offset_B = B->get_transform().get_origin() - A->get_transform().get_origin();

	validate_contacts();

	Vector3 offset_A = A->get_transform().get_origin();
	Transform xform_Au = Transform(A->get_transform().basis,Vector3());
	Transform xform_A = xform_Au * A->get_shape_transform(shape_A);

	Transform xform_Bu = B->get_transform();
	xform_Bu.origin-=offset_A;
	Transform xform_B = xform_Bu * B->get_shape_transform(shape_B);

	ShapeSW *shape_A_ptr=A->get_shape(shape_A);
	ShapeSW *shape_B_ptr=B->get_shape(shape_B);

	bool collided = CollisionSolverSW::solve_static(shape_A_ptr,xform_A,shape_B_ptr,xform_B,_contact_added_callback,this,&sep_axis);
	this->collided=collided;


	if (!collided) {

		//test ccd (currently just a raycast)

		if (A->is_continuous_collision_detection_enabled() && A->get_mode()>PhysicsServer::BODY_MODE_KINEMATIC && B->get_mode()<=PhysicsServer::BODY_MODE_KINEMATIC) {
			_test_ccd(p_step,A,shape_A,xform_A,B,shape_B,xform_B);
		}

		if (B->is_continuous_collision_detection_enabled() && B->get_mode()>PhysicsServer::BODY_MODE_KINEMATIC && A->get_mode()<=PhysicsServer::BODY_MODE_KINEMATIC) {
			_test_ccd(p_step,B,shape_B,xform_B,A,shape_A,xform_A);
		}

		return false;
	}



	real_t max_penetration = space->get_contact_max_allowed_penetration();

	float bias = 0.3f;

	if (shape_A_ptr->get_custom_bias() || shape_B_ptr->get_custom_bias()) {

		if (shape_A_ptr->get_custom_bias()==0)
			bias=shape_B_ptr->get_custom_bias();
		else if (shape_B_ptr->get_custom_bias()==0)
			bias=shape_A_ptr->get_custom_bias();
		else
			bias=(shape_B_ptr->get_custom_bias()+shape_A_ptr->get_custom_bias())*0.5;
	}



	real_t inv_dt = 1.0/p_step;

	for(int i=0;i<contact_count;i++) {

		Contact &c = contacts[i];
		c.active=false;

		Vector3 global_A = xform_Au.xform(c.local_A);
		Vector3 global_B = xform_Bu.xform(c.local_B);


		real_t depth = c.normal.dot(global_A - global_B);

		if (depth<=0) {
			c.active=false;
			continue;
		}

		c.active=true;

#ifdef DEBUG_ENABLED


		if (space->is_debugging_contacts()) {
			space->add_debug_contact(global_A+offset_A);
			space->add_debug_contact(global_B+offset_A);
		}
#endif


		int gather_A = A->can_report_contacts();
		int gather_B = B->can_report_contacts();

		c.rA = global_A;
		c.rB = global_B-offset_B;

		// contact query reporting...
#if 0
		if (A->get_body_type() == PhysicsServer::BODY_CHARACTER)
			static_cast<CharacterBodySW*>(A)->report_character_contact( global_A, global_B, B );
		if (B->get_body_type() == PhysicsServer::BODY_CHARACTER)
			static_cast<CharacterBodySW*>(B)->report_character_contact( global_B, global_A, A );
		if (A->has_contact_query())
			A->report_contact( global_A, global_B, B );
		if (B->has_contact_query())
			B->report_contact( global_B, global_A, A );
#endif

		if (A->can_report_contacts()) {
			Vector3 crB = A->get_angular_velocity().cross( c.rA ) + A->get_linear_velocity();
			A->add_contact(global_A,-c.normal,depth,shape_A,global_B,shape_B,B->get_instance_id(),B->get_self(),crB);
		}

		if (B->can_report_contacts()) {
			Vector3 crA = A->get_angular_velocity().cross( c.rB ) + A->get_linear_velocity();
			B->add_contact(global_B,c.normal,depth,shape_B,global_A,shape_A,A->get_instance_id(),A->get_self(),crA);
		}

		if (A->is_shape_set_as_trigger(shape_A) || B->is_shape_set_as_trigger(shape_B) || (A->get_mode()<=PhysicsServer::BODY_MODE_KINEMATIC && B->get_mode()<=PhysicsServer::BODY_MODE_KINEMATIC)) {
			c.active=false;
			collided=false;
			continue;

		}


		c.active=true;

		// Precompute normal mass, tangent mass, and bias.
		Vector3 inertia_A = A->get_inv_inertia_tensor().xform( c.rA.cross( c.normal ) );
		Vector3 inertia_B = B->get_inv_inertia_tensor().xform( c.rB.cross( c.normal ) );
		real_t kNormal = A->get_inv_mass() + B->get_inv_mass();
		kNormal += c.normal.dot( inertia_A.cross(c.rA ) ) + c.normal.dot( inertia_B.cross( c.rB ));
		c.mass_normal = 1.0f / kNormal;

#if 1
		c.bias = -bias * inv_dt * MIN(0.0f, -depth + max_penetration);

#else
		if (depth > max_penetration) {
			c.bias = (depth - max_penetration) * (1.0/(p_step*(1.0/RELAXATION_TIMESTEPS)));
		} else {
			float approach = -0.1f * (depth - max_penetration) / (CMP_EPSILON + max_penetration);
			approach = CLAMP( approach, CMP_EPSILON, 1.0 );
			c.bias = approach * (depth - max_penetration) * (1.0/p_step);
		}
#endif
		c.depth=depth;

		Vector3 j_vec = c.normal * c.acc_normal_impulse + c.acc_tangent_impulse;
		A->apply_impulse( c.rA, -j_vec );
		B->apply_impulse( c.rB, j_vec );
		c.acc_bias_impulse=0;
		Vector3 jb_vec = c.normal * c.acc_bias_impulse;
		A->apply_bias_impulse( c.rA, -jb_vec );
		B->apply_bias_impulse( c.rB, jb_vec );

		c.bounce = MAX(A->get_bounce(),B->get_bounce());
		if (c.bounce) {

			Vector3 crA = A->get_angular_velocity().cross( c.rA );
			Vector3 crB = B->get_angular_velocity().cross( c.rB );
			Vector3 dv = B->get_linear_velocity() + crB - A->get_linear_velocity() - crA;
			//normal impule
			c.bounce = c.bounce * dv.dot(c.normal);
		}


	}

	return true;
}